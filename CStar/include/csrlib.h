#ifndef CSTARLIBRARY
#define CSTARLIBRARY
/*
MIT License

Copyright (c) 2021 DeveloperX19

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.






 * C* Library, 2021
 * Version 0.0.1
 * Project Link: https://github.com/DeveloperX19/CStar
 * Documentation: https://github.com/DeveloperX19/CStar/wiki






 *		=========================================>	Individual Setup Macros	===============================================>
 */



#define CSR_ISOSTD 17
#define CSR_SCHEDULER_TIME 14

#define CSR_UTILITY 1
#define CSR_DEBUG 1
#define CSR_TODO 0




/*
 *		===================================================================================================================>
 */

#include <bitset>
#include <type_traits>
#include <thread>
#include <chrono>



#if CSR_ISOSTD >= 17
#define csrndc(x) [[nodiscard(x)]]
#else
#define csrndc(x)
#endif




#if CSR_UTILITY

#define TODO static_assert(!CSR_TODO,"Unresolved TODO-Item!")

#define range(var, len) for(size_t var = 0; var < (len); var++)

#if CSR_DEBUG
#define dlog(var) std::cout << std::endl << "DLog - " << __FILE__ << " | " << __LINE__ << ":  " << #var << " = " << (var) << std::endl
#else
#define dlog(var) 
#endif

#endif





/*
 *		=========================================>	 Forward Declarations	===============================================>
 */



 /*
  *	Official C-Star library
  *	This library contains data structures, functions and other tools for c++ projects.
  */
namespace csr
{

	namespace args
	{

		//[Data Structures General]
		namespace DSG
		{
			enum : unsigned
			{
				STATIC = 0,
				DYNAMIC = 1,
			};
		}
		//[Binary Search Tree]
		namespace BST
		{
			enum : unsigned
			{
				//Recommended for Read-Heavy Data
				AVL = 2,
				//Recommended for Write-Heavy Data
				RB = 3,
				//Recommended for Cache-Heavy Data
				SPLAY = 4,
				//Recommended for General & Big Data
				//small cache: splay [supported by FIFO with requeue] + AVL [for big data] (evtl.) RB after [n] layers
				HYBRID = 5
			};
		}
		//[Timer Time Scale]
		namespace TTS
		{
			using hour = std::ratio<3600, 1>;
			using min = std::ratio<60, 1>;
			using sec = std::ratio<1>;
			using ms = std::milli;
			using us = std::micro;
			using ns = std::nano;
		}
	}

	namespace math
	{
		namespace tfloat
		{
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool equal(BASE a, BASE b) noexcept;
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool not_equal(BASE a, BASE b) noexcept;
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool greater(BASE a, BASE b) noexcept;
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool less(BASE a, BASE b) noexcept;
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool greater_equal(BASE a, BASE b) noexcept;
			//#include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool less_equal(BASE a, BASE b) noexcept;
		}
	}

	namespace data
	{
		//#include "csrmask.h"
		template <typename baseType, typename = typename std::enable_if< \
			std::is_enum<baseType>::value&& \
			!std::is_convertible<baseType, std::underlying_type_t<baseType>>::value&& \
			!std::is_same<std::underlying_type_t<baseType>, bool>::value \
			, baseType>::type> struct mask;

	}

	namespace util
	{
		namespace enumc
		{
			template <typename enumT, typename>
			inline constexpr enumT operator| (const enumT& a, const enumT& b);
			template <typename enumT, typename>
			inline constexpr enumT operator& (const enumT& a, const enumT& b);
			template <typename enumT, typename>
			inline constexpr enumT operator^ (const enumT& a, const enumT& b);
			template <typename enumT, typename>
			inline constexpr enumT operator~ (const enumT& a);
		}
	}
		
	namespace tool
	{
		//#include "csrtimer.h"
		template <typename timeScale = csr::args::TTS::ms, typename = typename std::enable_if< \
			std::is_same<timeScale, std::nano>::value || \
			std::is_same<timeScale, std::micro>::value || \
			std::is_same<timeScale, std::milli>::value || \
			std::is_same<timeScale, std::ratio<1>>::value || \
			std::is_same<timeScale, std::ratio<60, 1>>::value || \
			std::is_same<timeScale, std::ratio<3600, 1>>::value \
			, bool>::type> class Timer;
	}
}



/*
 *		=========================================>	    C-Star Helpers		===============================================>
 */


/*
 *	This namespace contains functions and structs reserved for the implementation of the csrlib.h include.
 *	It is strongly discouraged to use these manually.
 */
namespace csr_details
{

}


#endif