#ifndef CSTARLIBRARY_MASK
#define CSTARLIBRARY_MASK
#include "csrlib.h"

#include <ostream>

namespace csr
{
	namespace data
	{
		template<typename baseType> class mask<baseType>;
		template<typename baseType> std::ostream& operator<<(std::ostream& os, const mask<baseType>& m);

		///Simple Bitmask for enums that can be used for 
		///easy bit-manipulation and comparisons
		///baseType - the enum that should be used as the underlying type of the mask
		template<typename baseType>
		class mask<baseType>
		{
		private:
			typename std::underlying_type<baseType>::type flags;
		public:
			///all bits are reset in default constructor
			explicit constexpr mask(const baseType& mask = (baseType)0) : flags{ (typename std::underlying_type<baseType>::type)mask } {}
			///Cast to enum
			template <typename T, typename std::enable_if <
				std::is_enum<T>::value &&
				!std::is_same<typename std::underlying_type<T>::type, bool>::value
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

			void fill() noexcept;
			void flush() noexcept;
			void flip() noexcept;
			void set(const baseType& affected) noexcept;
			void reset(const baseType& affected) noexcept;
			void toggle(const baseType& affected) noexcept;

			csrndc("useless call of function: bool hasAny(typename)")
			inline constexpr bool hasAny(const baseType& other) const noexcept;
			csrndc("useless call of function: bool hasAll(typename)")
			inline constexpr bool hasAll(const baseType& other) const noexcept;
			csrndc("useless call of function: int count()")
			inline constexpr int count() const noexcept;

			csrndc("useless call of function: int capacity()")
			inline static constexpr int capacity() noexcept;
			
			friend std::ostream& operator<< <>(std::ostream& os, const mask<baseType>& m);
		};

		///sets all bits
		template<typename baseType>
		inline void mask<baseType>::fill() noexcept
		{
			flags = ~0;
		}
		///resets all bits
		template<typename baseType>
		inline void mask<baseType>::flush() noexcept
		{
			flags = 0;
		}
		///flips all bits individually
		template<typename baseType>
		inline void mask<baseType>::flip() noexcept
		{
			flags = ~flags;
		}
		///sets all bits that are set in affected
		template<typename baseType>
		inline void mask<baseType>::set(const baseType& affected) noexcept
		{
			flags |= (typename std::underlying_type<baseType>::type)affected;
		}
		///resets all bits that are set in affected
		template<typename baseType>
		inline void mask<baseType>::reset(const baseType& affected) noexcept
		{
			flags &= ~(typename std::underlying_type<baseType>::type)affected;
		}
		///flips all bits that are set in affected individually
		template<typename baseType>
		inline void mask<baseType>::toggle(const baseType& affected) noexcept
		{
			flags ^= (typename std::underlying_type<baseType>::type)affected;
		}
		///returns true if this mask has any of the bits set, that the other mask has set.
		///if either this or the other mask are clear, hasAny always returns false.
		template<typename baseType>
		inline constexpr bool mask<baseType>::hasAny(const baseType& other) const noexcept
		{
			return flags & (typename std::underlying_type<baseType>::type)other;
		}
		///returns true if this mask has all of the bits set, that the other mask has set.
		///if this mask has all bits set, hasAll always returns true.
		template<typename baseType>
		inline constexpr bool mask<baseType>::hasAll(const baseType& other) const noexcept
		{
			return (typename std::underlying_type<baseType>::type)other == (flags & (typename std::underlying_type<baseType>::type)other);
		}
		///returns the number of bits that are set in this mask
		template<typename baseType>
		inline constexpr int mask<baseType>::count() const noexcept
		{
			return ((std::bitset<sizeof(baseType) * 8>)flags).count();
		}
		///returns the number of bits in this mask
		template<typename baseType>
		inline constexpr int mask<baseType>::capacity() noexcept
		{
			return sizeof(baseType) * 8;
		}

		template<typename baseType>
		std::ostream& operator<<(std::ostream& os, const mask<baseType>& m)
		{
			os << "[mask: 0b" << std::bitset<sizeof(baseType) * 8>(m.flags) << "; " << (unsigned long long)m.flags << "]";
			return os;
		}
	}
}


#endif