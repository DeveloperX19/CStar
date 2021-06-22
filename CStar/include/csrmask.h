#ifndef CSTARLIBRARY_MASK
#define CSTARLIBRARY_MASK
#include "csrlib.h"

namespace csr
{
	namespace data
	{


		///Simple Bitmask for enums that can be used for 
		///easy bit-manipulation and comparisons
		///baseType - the enum that should be used as the underlying type of the mask
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
			///all bits are reset in constructor
			explicit inline constexpr mask(const baseType& mask = (baseType)0) noexcept : flags{ (std::underlying_type_t<baseType>)mask } {}

			///Cast to enum
			template <typename T, typename std::enable_if <
				std::is_enum<T>::value &&
				!std::is_same<std::underlying_type_t<T>, bool>::value
				, bool>::type = 0>
			explicit inline constexpr operator T() const noexcept
			{
				return (T)flags;
			}
			///Cast to Integer
			template <typename T, typename std::enable_if <
				std::is_integral<T>::value &&
				!std::is_same<T, bool>::value
				, bool>::type = 0>
			explicit inline constexpr operator T() const noexcept
			{
				return (T)flags;
			}

			///Cast to baseType
			inline constexpr operator baseType() const noexcept
			{
				return (baseType)flags;
			}


			///sets all bits
			inline void fill() noexcept
			{
				flags = ~0;
			}
			///resets all bits
			inline void flush() noexcept
			{
				flags = 0;
			}
			///flips all bits individually
			inline void flip() noexcept
			{
				flags = ~flags;
			}
			///sets all bits that are set in affected
			inline void set(const baseType& affected) noexcept
			{
				flags |= (std::underlying_type_t<baseType>)affected;
			}
			///resets all bits that are set in affected
			inline void reset(const baseType& affected) noexcept
			{
				flags &= ~(std::underlying_type_t<baseType>)affected;
			}
			///flips all bits that are set in affected individually
			inline void toggle(const baseType& affected) noexcept
			{
				flags ^= (std::underlying_type_t<baseType>)affected;
			}

			csrndc("useless call of function: bool hasAny(typename)")
			///returns true if this mask has any of the bits set, that the other mask has set.
			///if either this or the other mask are clear, hasAny always returns false.
			inline constexpr bool hasAny(const baseType& other) const noexcept
			{
				return flags & (std::underlying_type_t<baseType>)other;
			}
			csrndc("useless call of function: bool hasAll(typename)")
			///returns true if this mask has all of the bits set, that the other mask has set.
			///if this mask has all bits set, hasAll always returns true.
			inline constexpr bool hasAll(const baseType& other) const noexcept
			{
				return (std::underlying_type_t<baseType>)other == (flags & (std::underlying_type_t<baseType>)other);
			}
			csrndc("useless call of function: int count()")
			///returns the number of bits that are set in this mask
			inline constexpr int count() const noexcept
			{
				return ((std::bitset<sizeof(baseType) * 8>)flags).count();
			}

			csrndc("useless call of function: int capacity()")
			///returns the number of bits in this mask
			inline static constexpr int capacity() noexcept
			{
				return sizeof(baseType) * 8;
			}
		};
	}
}



#endif