#ifndef CSTARLIBRARY_UTIL
#define CSTARLIBRARY_UTIL
#include "csrlib.h"

namespace csr
{
	namespace util
	{
		namespace enumc
		{
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<std::underlying_type_t<enumT>, bool>::value, bool>::type = 0>
				inline constexpr enumT operator| (const enumT& a, const enumT& b)
			{
				return (enumT)((std::underlying_type_t<enumT>)a | (std::underlying_type_t<enumT>)b);
			}
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<std::underlying_type_t<enumT>, bool>::value, bool>::type = 0>
				inline constexpr enumT operator& (const enumT& a, const enumT& b)
			{
				return (enumT)((std::underlying_type_t<enumT>)a & (std::underlying_type_t<enumT>)b);
			}
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<std::underlying_type_t<enumT>, bool>::value, bool>::type = 0>
				inline constexpr enumT operator^ (const enumT& a, const enumT& b)
			{
				return (enumT)((std::underlying_type_t<enumT>)a ^ (std::underlying_type_t<enumT>)b);
			}
			template <typename enumT, typename std::enable_if<
				std::is_enum<enumT>::value &&
				!std::is_same<std::underlying_type_t<enumT>, bool>::value, bool>::type = 0>
				inline constexpr enumT operator~ (const enumT& a)
			{
				return (enumT)(~(std::underlying_type_t<enumT>)a);
			}
		}

	}
}



#endif