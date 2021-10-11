#ifndef CSTARLIBRARY_TFLOAT
#define CSTARLIBRARY_TFLOAT
	#ifndef CSTARLIBRARY
	static_assert(false, "#include 'csrlib.h'");
	#else

#include <cstdint>
#include <limits>

namespace csr
{
	namespace math
	{
		namespace tfloat
		{
			/// Returns true if a and b are similar enough.
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitAbsTol > 0) && (nUnitAbsTol == nUnitRelTol), bool>::type = 0>
				inline bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();
				constexpr BASE infinity = std::numeric_limits<BASE>::infinity();
				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == infinity) return false;
				return diff <= tolerance * std::max(std::max((BASE)1.0, std::abs(a)), std::abs(b));
			}
			/// Returns true if a and b are similar enough.
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitAbsTol != nUnitRelTol) && (nUnitAbsTol > 0) && (nUnitRelTol > 0), bool>::type = 0>
				inline bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE absoluteTolerance = nUnitAbsTol * std::numeric_limits<BASE>::epsilon();
				constexpr BASE relativeTolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();
				constexpr BASE infinity = std::numeric_limits<BASE>::infinity();

				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == infinity) return false;
				return diff <= std::max(absoluteTolerance, relativeTolerance * std::max(std::abs(a), std::abs(b)));
			}
			/// Returns true if a and b are similar enough.
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol > 0) && (nUnitAbsTol == 0), bool>::type = 0>
				inline bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();
				constexpr BASE infinity = std::numeric_limits<BASE>::infinity();

				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == infinity) return false;
				return diff <= tolerance * std::max(std::abs(a), std::abs(b));
			}
			/// Returns true if a and b are similar enough.
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol == 0) && (nUnitAbsTol > 0), bool>::type = 0>
				inline bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitAbsTol * std::numeric_limits<BASE>::epsilon();

				if (a == b) return true;
				return std::abs(a - b) <= tolerance;
			}

			/// Returns true if a and b are different enough.
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
				inline bool not_equal(BASE a, BASE b) noexcept
			{
				return !equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			/// Returns true if (a > b) and (a and b are different enough).
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
				inline bool greater(BASE a, BASE b) noexcept
			{
				return (a > b) && not_equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			/// Returns true if (a < b) and (a and b are different enough).
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
				inline bool less(BASE a, BASE b) noexcept
			{
				return (a < b) && not_equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			/// Returns true if (a > b) or (a and b are similar enough).
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
				inline bool greater_equal(BASE a, BASE b) noexcept
			{
				return (a > b) || equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			/// Returns true if (a < b) or (a and b are similar enough).
			/// BASE - the type of a and b
			/// nUnitAbsTol - number of units of absolute tolerance to check similarity with
			/// nUnitRelTol - number of units of relative tolerance to check similarity with
			/// ignoreIEC559 - this funtion was designed to work with the IEC559 standard. if you have a different standard,
			/// set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
				inline bool less_equal(BASE a, BASE b) noexcept
			{
				return (a < b) || equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
		}
	}
}

namespace cstar
{
	namespace tfloat
	{
		using csr::math::tfloat::equal;
		using csr::math::tfloat::not_equal;
		using csr::math::tfloat::greater;
		using csr::math::tfloat::less;
		using csr::math::tfloat::greater_equal;
		using csr::math::tfloat::less_equal;
	}
}

	#endif
#endif