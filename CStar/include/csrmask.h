#ifndef CSTARLIBRARY_MASK
#define CSTARLIBRARY_MASK
#include "csrlib.h"

namespace csr
{
	namespace data
	{


		//TODO	Kurzbeschreibungen
		template <typename baseType>
		struct mask<baseType, typename std::enable_if<
			std::is_enum<baseType>::value &&
			!std::is_convertible<baseType, std::underlying_type_t<baseType>>::value &&
			!std::is_same<std::underlying_type_t<baseType>, bool>::value
			, baseType>::type>
		{
		private:
			std::underlying_type_t<baseType> flags;
		public:
			explicit inline constexpr mask(const baseType& mask = (baseType)0) noexcept : flags{ (std::underlying_type_t<baseType>)mask } {}

			template <typename T, typename std::enable_if <
				std::is_enum<T>::value &&
				!std::is_same<std::underlying_type_t<T>, bool>::value
				, bool>::type = 0>
			explicit inline constexpr operator T() const noexcept
			{
				return (T)flags;
			}
			template <typename T, typename std::enable_if <
				std::is_integral<T>::value &&
				!std::is_same<T, bool>::value
				, bool>::type = 0>
			explicit inline constexpr operator T() const noexcept
			{
				return (T)flags;
			}


			inline constexpr operator baseType() const noexcept
			{
				return (baseType)flags;
			}



			inline void fill() noexcept
			{
				flags = ~0;
			}
			inline void flush() noexcept
			{
				flags = 0;
			}
			inline void flip() noexcept
			{
				flags = ~flags;
			}

			inline void set(const baseType& affected) noexcept
			{
				flags |= (std::underlying_type_t<baseType>)affected;
			}
			inline void reset(const baseType& affected) noexcept
			{
				flags &= ~(std::underlying_type_t<baseType>)affected;
			}
			inline void toggle(const baseType& affected) noexcept
			{
				flags ^= (std::underlying_type_t<baseType>)affected;
			}

			csrndc("useless call of function: bool hasAny(typename)")
			inline constexpr bool hasAny(const baseType& mask) const noexcept
			{
				return flags & (std::underlying_type_t<baseType>)mask;
			}
			csrndc("useless call of function: bool hasAll(typename)")
			inline constexpr bool hasAll(const baseType& mask) const noexcept
			{
				return (std::underlying_type_t<baseType>)mask == (flags & (std::underlying_type_t<baseType>)mask);
			}
			csrndc("useless call of function: int count()")
			inline constexpr int count() const noexcept
			{
				return ((std::bitset<sizeof(baseType) * 8>)flags).count();
			}

			csrndc("useless call of function: int capacity()")
			inline static constexpr int capacity() noexcept
			{
				return sizeof(baseType) * 8;
			}
		};
	}
}



#endif