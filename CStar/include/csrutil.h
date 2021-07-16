#ifndef CSTARLIBRARY_UTIL
#define CSTARLIBRARY_UTIL
#include "csrlib.h"

namespace csr
{
	namespace util
	{
		///operator overloads for scoped enums
		namespace enumc
		{
			///operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
			inline constexpr enumT operator| (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a | (typename std::underlying_type<enumT>::type)b);
			}
			///operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
			inline constexpr enumT operator& (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a & (typename std::underlying_type<enumT>::type)b);
			}
			///operator overload for scoped enums
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<typename std::underlying_type<enumT>::type, bool>::value, bool>::type = 0>
			inline constexpr enumT operator^ (const enumT& a, const enumT& b)
			{
				return (enumT)((typename std::underlying_type<enumT>::type)a ^ (typename std::underlying_type<enumT>::type)b);
			}
			///operator overload for scoped enums
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


#endif