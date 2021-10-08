#ifndef CSTARLIBRARY_CSTR
#define CSTARLIBRARY_CSTR
	#ifndef CSTARLIBRARY
	static_assert(false, "#include 'csrlib.h'");
	#else


namespace csr
{
	namespace util
	{
		/// Returns the size of the string, not including the null-terminator
		inline std::size_t cstrlen(const char* str) noexcept
		{
			std::size_t len = 0;
			while (str[len++] != '\0');
			return len - 1;
		}

		/// Returns the size of the string, not including the null-terminator
		/// or maxCnt if the string is longer than that
		inline std::size_t cstrnlen(const char* str, std::size_t maxCnt) noexcept
		{
			std::size_t len = 0;
			while (str[len++] != '\0' && len < maxCnt);
			return len - 1;
		}

		/// Copies source into dest, including null-terminator,
		/// calls new[] if dest is 0
		inline void cstrcpy(char*& dest, const char* source) noexcept
		{
			if (!dest)
			{
				std::size_t len = cstrlen(source) + 1;
				dest = new char[len];
				for (std::size_t i = 0; i < len; i++)
					dest[i] = source[i];
				return;
			}
			else
			{
				std::size_t i = 0;
				while (source[i] != '\0')
					dest[i] = source[i], i++;
				dest[i] = '\0';
				return;
			}
		}

		/// Copies source into dest, including null-terminator,
		/// calls new[] if dest is 0
		/// maxCnt : maximum number of characters to copy, not including null-terminator
		inline void cstrncpy(char*& dest, const char* source, const std::size_t maxCnt) noexcept
		{
			if (!dest)
			{
				std::size_t len = cstrnlen(source, maxCnt) + 1;
				dest = new char[len];
				for (std::size_t i = 0; i < len; i++)
					dest[i] = source[i];
				dest[len - 1] = '\0';
				return;
			}
			else
			{
				std::size_t i = 0;
				while (i < maxCnt && source[i] != '\0')
					dest[i] = source[i], i++;
				dest[i - 1] = '\0';
				return;
			}
		}

		/// Returns true if str1 is exactly equal to str2
		inline bool cstreq(const char* str1, const char* str2) noexcept
		{
			for (std::size_t i = 0;; i++)
			{
				if (str1[i] != str2[i]) return false;
				if (str1[i] == '\0') break;
			}
			return true;
		}

		/// Returns true if str starts with pre
		inline bool cstrprfx(const char* pre, const char* str) noexcept
		{
			for (std::size_t i = 0; pre[i] != '\0'; i++)
			{
				if (pre[i] != str[i]) return false;
			}
			return true;
		}

		/// Returns true if str ends with suf
		inline bool cstrsufx(const char* suf, const char* str) noexcept
		{
			std::size_t strL = cstrlen(str);
			std::size_t sufL = cstrlen(suf);
			if (strL < sufL) return false;
			for (std::size_t i = 0; i <= sufL; i++)
			{
				if (suf[sufL - i] != str[strL - i]) return false;
			}
			return true;
		}

		/// Converts str to an Integral type from right to left for as long as possible
		template<typename IntType>
		inline typename std::enable_if<std::is_integral<IntType>::value, IntType>::type cstrint(const char* str) noexcept
		{
			IntType mul = 1;
			IntType result = 0;
			std::size_t len = cstrlen(str) - 1;
			for (;; len--)
			{
				if (str[len] >= '0' && str[len] <= '9')
				{
					IntType ccint = (IntType)str[len] - '0';
					result += ccint * mul;
					mul *= 10;
				}
				else if (std::is_signed<IntType>::value && str[len] == '-')
				{
					result *= -1;
					break;
				}
				else break;

				if (len == 0) break;
			}
			return result;
		}

		/// Makes subStrs an array of strings, splitting str at every occurrence of the delimiter.
		/// Returns the number of items in subStrs
		inline unsigned int cstrsplit(const char* str, char**& subStrs, char delim) noexcept
		{
			unsigned int cnt = 1;
			bool wasDelim = true;
			for (std::size_t i = 0; str[i] != '\0'; i++)
			{
				if (str[i] == delim && !wasDelim) wasDelim = true, cnt++;
				else if (str[i] != delim && wasDelim) wasDelim = false;
			}
			if (wasDelim) cnt--;

			if (cnt > 0)
				subStrs = new char* [cnt];
			else
			{
				subStrs = nullptr;
				return 0;
			}

			std::size_t lastIndex = 0;
			std::size_t c = 0;
			wasDelim = true;
			for (std::size_t i = 0; c < cnt; i++)
			{
				if (str[i] == delim)
				{
					if (!wasDelim)
					{
						subStrs[c] = nullptr;
						cstrncpy(subStrs[c++], str + lastIndex, i - lastIndex + 1);
						wasDelim = true;
					}
					lastIndex = i + 1;
				}
				else if (str[i] == '\0')
				{
					if (!wasDelim)
					{
						subStrs[c] = nullptr;
						cstrncpy(subStrs[c++], str + lastIndex, i - lastIndex + 1);
					}
					break;
				}
				else if (str[i] != delim && wasDelim) wasDelim = false;
			}
			return cnt;
		}

		inline unsigned int cstrdiff(const char* str1, const char* str2) noexcept;
		/// Helper class for cstrdiff (see below)
		class cstrdiff_H
		{
		private:
			const char *const str1, *const str2;
			unsigned int *const *const vals;
			bool *const *const vms;
			const unsigned int str1l, str2l;
			explicit cstrdiff_H(const char* _str1, const char* _str2, unsigned int** _vals, bool** _vms, const unsigned int _str1l, const unsigned int _str2l)
				: str1{ _str1 }, str2{_str2}, vals{_vals}, vms{_vms}, str1l{_str1l}, str2l{_str2l} {}
			friend inline unsigned int cstrdiff(const char* str1, const char* str2) noexcept;
		public:
			unsigned int operator()(unsigned int i = 0, unsigned int j = 0)
			{
				unsigned int i_ = i;
				unsigned int j_ = j;
				vms[i][j] = true;

				while (str1[i] != '\0' && str2[j] != '\0')
				{
					if (str1[i] != str2[j]) break;
					i++, j++;
				}
				if (str1[i] == '\0')
					return vals[i_][j_] = str2l - j;
				if (str2[j] == '\0')
					return vals[i_][j_] = str1l - i;

				unsigned int v1 = (vms[i + 1][j + 1]) ? vals[i + 1][j + 1] : operator()(i + 1, j + 1);
				unsigned int v2 = (vms[i][j + 1]) ? vals[i][j + 1] : operator()(i, j + 1);
				unsigned int v3 = (vms[i + 1][j]) ? vals[i + 1][j] : operator()(i + 1, j);
				return vals[i_][j_] = 1 + std::min(std::min(v1, v2), v3);
			}
		};

		/// Levenshtein-Distance:
		/// Returns minimal count of 'incorrect' characters
		/// O(n^2) space & time
		/// Not suited for extremely long strings (1000's of characters)
		/// Examples:
		///		cstrdiff("abcde","abcXde") => 1
		///		cstrdiff("abcde","abXde") => 1
		///		cstrdiff("abcde","abde") => 1
		///		cstrdiff("abcde","abdce") => 2
		///		cstrdiff("aaaaa","bbb") => 5
		///		cstrdiff("aaaaa","bbbbbb") => 6
		inline unsigned int cstrdiff(const char* str1, const char* str2) noexcept
		{
			unsigned int l1 = (unsigned int)cstrlen(str1) + 1;
			unsigned int l2 = (unsigned int)cstrlen(str2) + 1;
			unsigned int** vals = new unsigned int* [l1];
			for (unsigned int k = 0; k < l1; k++)
				vals[k] = new unsigned int[l2];
			bool** vms = new bool* [l1];
			for (unsigned int k = 0; k < l1; k++)
			{
				vms[k] = new bool[l2];
				for (unsigned int r = 0; r < l2; r++)
					vms[k][r] = false;
			}
			unsigned int result = cstrdiff_H(str1, str2, vals, vms, l1 - 1, l2 - 1)();
			for (unsigned int k = 0; k < l1; k++)
			{
				delete[] vals[k];
				delete[] vms[k];
			}
			delete[] vals;
			delete[] vms;
			return result;
		}

		/// Left-aligns strs[]
		/// strs[] : array of strings to align
		/// numStrs : size of strs[]
		/// returns : array of aligned strings
		/// targetlen : fills strings to be of length targetLen
		/// Note:	targetLen will be ignored if it is too small.
		inline char** cstralignL(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen) noexcept
		{
			std::size_t* lens = new std::size_t[numStrs];
			std::size_t maxLen = 0;
			for (std::size_t i = 0; i < numStrs; i++)
			{
				lens[i] = cstrlen(strs[i]);
				if (lens[i] > maxLen) maxLen = lens[i];
			}
			if(targetLen > maxLen) maxLen = targetLen;

			char** output = new char* [numStrs];
			for (std::size_t i = 0; i < numStrs; i++)
			{
				output[i] = new char[maxLen + 1];
				cstrcpy(output[i], strs[i]);
				for (std::size_t j = lens[i]; j < maxLen; j++)
					output[i][j] = ' ';
				output[i][maxLen] = '\0';
			}

			delete[] lens;
			return output;
		}

		/// Right-aligns strs[]
		/// strs[] : array of strings to align
		/// numStrs : size of strs[]
		/// returns : array of aligned strings
		/// targetlen : fills strings to be of length targetLen
		/// Note:	targetLen will be ignored if it is too small.
		inline char** cstralignR(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen) noexcept
		{
			std::size_t* lens = new std::size_t[numStrs];
			std::size_t maxLen = 0;
			for (std::size_t i = 0; i < numStrs; i++)
			{
				lens[i] = cstrlen(strs[i]);
				if(lens[i] > maxLen) maxLen = lens[i];
			}
			if(targetLen > maxLen) maxLen = targetLen;

			char** output = new char* [numStrs];
			for (std::size_t i = 0; i < numStrs; i++)
			{
				output[i] = new char[maxLen + 1];
				std::size_t overhead = maxLen - lens[i];
				char* tmp = output[i] + overhead;
				cstrcpy(tmp, strs[i]);
				for (std::size_t j = 0; j < overhead; j++)
					output[i][j] = ' ';
			}

			delete[] lens;
			return output;
		}

		/// Center-aligns strs[]
		/// strs[] : array of strings to align
		/// numStrs : size of strs[]
		/// returns : array of aligned strings
		/// targetlen : fills strings to be of length targetLen
		/// Note:	targetLen will be ignored if it is too small.
		inline char** cstralignC(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen) noexcept
		{
			std::size_t* lens = new std::size_t[numStrs];
			std::size_t maxLen = 0;
			for (std::size_t i = 0; i < numStrs; i++)
			{
				lens[i] = cstrlen(strs[i]);
				if (lens[i] > maxLen) maxLen = lens[i];
			}
			if(targetLen > maxLen) maxLen = targetLen;

			char** output = new char* [numStrs];
			for (std::size_t i = 0; i < numStrs; i++)
			{
				output[i] = new char[maxLen + 1];
				std::size_t overhead = maxLen - lens[i];
				char* tmp = output[i] + overhead / 2;
				cstrcpy(tmp, strs[i]);
				for (std::size_t j = 0; j < overhead / 2; j++)
					output[i][j] = ' ';
				for (std::size_t j = lens[i] + overhead / 2; j < maxLen; j++)
					output[i][j] = ' ';
				output[i][maxLen] = '\0';
			}

			delete[] lens;
			return output;
		}
	
		/// joins strs[] into a blocktext of length targetLen
		/// strs[] : array of strings to align
		/// numStrs : size of strs[]
		/// targetlen : Length of returned string
		/// Note:	Elements of strs[] will always have at least 1 space between them.
		///			targetLen will be ignored if it is too small.
		inline char* cstrblocktext(const char* strs[], const std::size_t& numStrs, std::size_t targetLen) noexcept
		{
			//if (!numStrs) return nullptr;
			std::size_t* lens = new std::size_t[numStrs];
			std::size_t totalLen = 0;
			for (std::size_t i = 0; i < numStrs; i++)
			{
				lens[i] = cstrlen(strs[i]);
				totalLen += lens[i];
			}
			if (targetLen < totalLen + numStrs - 1) targetLen = totalLen + numStrs - 1;

			char* output = new char[targetLen + 1];
			char* output_o = output;
			std::size_t printSpace = (targetLen - totalLen) / (numStrs - 1);
			std::size_t extraSpace = (targetLen - totalLen) % (numStrs - 1);
			for (std::size_t i = 0;;)
			{
				cstrcpy(output_o, strs[i]);
				output_o += lens[i];
				if (++i == numStrs) break;
				for(std::size_t j = 0; j < printSpace + (i <= extraSpace); j++)
				{
					*(output_o++) = ' ';
				}
			}
			output[targetLen] = '\0';
			delete[] lens;
			return output;
		}
	}
}

	#endif
#endif