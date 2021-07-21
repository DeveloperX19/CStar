#ifndef CSTARLIBRARY_CSTR
#define CSTARLIBRARY_CSTR
#include "csrlib.h"


#include <type_traits>
#include <algorithm>
#include <utility>
#include <stack>


/// - size of the string, not including the null-terminator
size_t cstrlen(const char* str) noexcept
{
	size_t len = 0;
	while (str[len++] != '\0');
	return len - 1;
}

/// - size of the string, not including the null-terminator
/// or maxCnt if the string is longer than that
size_t cstrnlen(const char* str, size_t maxCnt) noexcept
{
	size_t len = 0;
	while (str[len++] != '\0' && len < maxCnt);
	return len - 1;
}

/// - copies source into dest, including null-terminator
/// - calls new[] if dest is 0
void cstrcpy(char*& dest, const char* source) noexcept
{
	if (!dest)
	{
		size_t len = cstrlen(source) + 1;
		dest = new char[len];
		for (size_t i = 0; i < len; i++)
			dest[i] = source[i];
		return;
	}
	else
	{
		size_t i = 0;
		while (source[i] != '\0')
			dest[i] = source[i], i++;
		return;
	}
}

/// - copies source into dest, including null-terminator
/// - maxCnt : maximum number of characters to copy, not including null-terminator
/// - calls new[] if dest is 0
void cstrncpy(char*& dest, const char* source, const size_t maxCnt) noexcept
{
	if (!dest)
	{
		size_t len = cstrnlen(source, maxCnt) + 1;
		dest = new char[len];
		for (size_t i = 0; i < len; i++)
			dest[i] = source[i];
		dest[len - 1] = '\0';
		return;
	}
	else
	{
		size_t i = 0;
		while (source[i] != '\0' && i < maxCnt)
			dest[i] = source[i], i++;
		dest[i - 1] = '\0';
		return;
	}
}

/// true if str1 is exactly equal to str2
bool cstreq(const char* str1, const char* str2) noexcept
{
	for (size_t i = 0;; i++)
	{
		if (str1[i] != str2[i]) return false;
		if (str1[i] == '\0') break;
	}
	return true;
}

/// true if str starts with pre
bool cstrprfx(const char* pre, const char* str) noexcept
{
	for (size_t i = 0; pre[i] != '\0'; i++)
	{
		if (pre[i] != str[i]) return false;
	}
	return true;
}

/// true if str ends with suf
bool cstrsufx(const char* suf, const char* str) noexcept
{
	size_t strL = cstrlen(str);
	size_t sufL = cstrlen(suf);
	if (strL < sufL) return false;
	for (size_t i = 0; i <= sufL; i++)
	{
		if (suf[sufL - i] != str[strL - i]) return false;
	}
	return true;
}

/// converts str to an Integral type.
/// converts the str from right to left for as long as possible
template<typename IntType = int>
typename std::enable_if<std::is_integral<IntType>::value, IntType>::type
cstrint(const char* str) noexcept
{
	IntType mul = 1;
	IntType result = 0;
	size_t len = cstrlen(str) - 1;
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

/// make subStrs an array of strings, splitting str at every occurrence of the delimiter
/// returns the number of items in subStrs
unsigned int cstrsplit(const char* str, char**& subStrs, char delim = ' ') noexcept
{
	unsigned int cnt = 1;
	bool wasDelim = true;
	for (size_t i = 0; str[i] != '\0'; i++)
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

	size_t lastIndex = 0;
	size_t c = 0;
	wasDelim = true;
	for (size_t i = 0; c < cnt; i++)
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

/// Levenshtein-Distance:
/// returns minimal count of 'incorrect' characters
/// O(n^2) space & time; uses memoization
/// not suited for extremely long strings (1000's of characters)
/// !!! only set parameters str1 and str2 !!!
/// Examples:
///		cstrdiff("abcde","abcXde") => 1
///		cstrdiff("abcde","abXde") => 1
///		cstrdiff("abcde","abde") => 1
///		cstrdiff("abcde","abdce") => 2
///		cstrdiff("aaaaa","bbb") => 5
///		cstrdiff("aaaaa","bbbbbb") => 6
unsigned int cstrdiff(const char* str1, const char* str2, unsigned int i = 0, unsigned int j = 0,
	unsigned int** vals = nullptr, bool** vms = nullptr, const unsigned int str1l = 0, const unsigned int str2l = 0) noexcept
{
	if (!vals)
	{
		if (str2l != 0 || str1l != 0 || vms || i != 0 || j != 0) return (unsigned)-1;
		unsigned int l1 = (unsigned int)cstrlen(str1) + 1;
		unsigned int l2 = (unsigned int)cstrlen(str2) + 1;
		vals = new unsigned int* [l1];
		for (unsigned int k = 0; k < l1; k++)
			vals[k] = new unsigned int[l2];
		vms = new bool* [l1];
		for (unsigned int k = 0; k < l1; k++)
		{
			vms[k] = new bool[l2];
			for (unsigned int r = 0; r < l2; r++)
				vms[k][r] = false;
		}
		unsigned int result = cstrdiff(str1, str2, 0, 0, vals, vms, l1 - 1, l2 - 1);
		for (unsigned int k = 0; k < l1; k++)
		{
			delete[] vals[k];
			delete[] vms[k];
		}
		delete[] vals;
		delete[] vms;
		return result;
	}

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

	unsigned int v1 = (vms[i + 1][j + 1]) ? vals[i + 1][j + 1] : cstrdiff(str1, str2, i + 1, j + 1, vals, vms, str1l, str2l);
	unsigned int v2 = (vms[i][j + 1]) ? vals[i][j + 1] : cstrdiff(str1, str2, i, j + 1, vals, vms, str1l, str2l);
	unsigned int v3 = (vms[i + 1][j]) ? vals[i + 1][j] : cstrdiff(str1, str2, i + 1, j, vals, vms, str1l, str2l);
	return vals[i_][j_] = 1 + std::min(std::min(v1, v2), v3);
}

#endif