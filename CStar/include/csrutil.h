#ifndef CSTARLIBRARY_UTIL
#define CSTARLIBRARY_UTIL
	#ifndef CSTARLIBRARY
	static_assert(false, "#include 'csrlib.h'");
	#else

namespace csr
{
	namespace util
	{
		namespace enumc
		{
			/// Operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
				inline constexpr enumT operator| (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a | (typename std::underlying_type<enumT>::type)b);
			}
			/// Operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
				inline constexpr enumT operator& (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a & (typename std::underlying_type<enumT>::type)b);
			}
			/// Operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
				inline constexpr enumT operator^ (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a ^ (typename std::underlying_type<enumT>::type)b);
			}
			/// Operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
				inline constexpr enumT operator~ (const enumT& a)
			{
				return (enumT)(~(typename std::underlying_type<enumT>::type)a);
			}
		}
	}
}

namespace cstar
{
	namespace enumc
	{
		using csr::util::enumc::operator|;
		using csr::util::enumc::operator&;
		using csr::util::enumc::operator^;
		using csr::util::enumc::operator~;
	}
}

	#endif
#endif