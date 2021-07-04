#ifndef CSTARLIBRARY_TFLOAT
#define CSTARLIBRARY_TFLOAT
#include "csrlib.h"

#include <cstdint>
#include <limits>

namespace csr
{
	namespace math
	{
		namespace tfloat
		{
			///returns true if a and b are similar enough.
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitAbsTol > 0) && (nUnitAbsTol == nUnitRelTol), bool>::type = 0>
			bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();

				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == std::numeric_limits<BASE>::infinity()) return false;
				return diff <= tolerance * std::max(std::max((BASE)1.0, std::abs(a)), std::abs(b));
			}
			///returns true if a and b are similar enough.
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitAbsTol != nUnitRelTol) && (nUnitAbsTol > 0) && (nUnitRelTol > 0), bool>::type = 0>
			bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE absoluteTolerance = nUnitAbsTol * std::numeric_limits<BASE>::epsilon();
				constexpr BASE relativeTolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();

				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == std::numeric_limits<BASE>::infinity()) return false;
				return diff <= std::max(absoluteTolerance, relativeTolerance * std::max(std::abs(a), std::abs(b)));
			}
			///returns true if a and b are similar enough.
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol > 0) && (nUnitAbsTol == 0), bool>::type = 0>
			bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitRelTol * std::numeric_limits<BASE>::epsilon();

				if (a == b) return true;
				BASE diff = std::abs(a - b);
				if (diff == std::numeric_limits<BASE>::infinity()) return false;
				return diff <= tolerance * std::max(std::abs(a), std::abs(b));
			}
			///returns true if a and b are similar enough.
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol == 0) && (nUnitAbsTol > 0), bool>::type = 0>
			bool equal(BASE a, BASE b) noexcept
			{
				constexpr BASE tolerance = nUnitAbsTol * std::numeric_limits<BASE>::epsilon();

				if (a == b) return true;
				return std::abs(a - b) <= tolerance;
			}

			///returns true if a and b are different enough.
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
			inline bool not_equal(BASE a, BASE b)
			{
				return !equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			///returns true if (a > b) and (a and b are different enough).
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
			inline bool greater(BASE a, BASE b)
			{
				return (a > b) && not_equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			///returns true if (a < b) and (a and b are different enough).
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
			inline bool less(BASE a, BASE b)
			{
				return (a < b) && not_equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			///returns true if (a > b) or (a and b are similar enough).
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
			inline bool greater_equal(BASE a, BASE b)
			{
				return (a > b) || equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
			///returns true if (a < b) or (a and b are similar enough).
			///BASE - the type of a and b
			///nUnitAbsTol - number of units of absolute tolerance to check similarity with
			///nUnitRelTol - number of units of relative tolerance to check similarity with
			///ignoreIEC559 - this funtion was designed to work with the IEC669 standard. if you have a different standard,
			///set this to true to use this function anyways
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename std::enable_if<
				std::is_floating_point<BASE>::value && (std::numeric_limits<BASE>::is_iec559 || ignoreIEC559)
				&& (nUnitAbsTol <= 10000) && (nUnitRelTol <= 10000) && (nUnitAbsTol + nUnitRelTol > 0), bool>::type = 0>
			inline bool less_equal(BASE a, BASE b)
			{
				return (a < b) || equal<BASE, nUnitAbsTol, nUnitRelTol, ignoreIEC559>(a, b);
			}
		}
	}
}


#endif