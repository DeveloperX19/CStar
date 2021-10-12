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






 *		===================================================================================================================>
 */

#ifndef CSTARLIBRARY_SETUP
// Make sure to create the "csrlib.h" setup-file somewhere in your project
// and use		#include "csrlib.h"
// instead of	#include "csrfwdecl.h"
static_assert(false, "#include csrlib.h");

#define CSR_ISOSTD 11
#define CSR_SCHEDULER_TIME 14
#define CSR_IS_RELEASE 0
#define CSR_RESOLVE_TODO 0
#define CSR_RESOLVE_WARN 0
#define CSR_USE_UTILITY 1

#else

#ifndef CSR_ISOSTD
// Make sure to #define CSR_ISOSTD according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_ISOSTD 11
#endif
#ifndef CSR_SCHEDULER_TIME
// Make sure to #define CSR_SCHEDULER_TIME according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_SCHEDULER_TIME 14
#endif
#ifndef CSR_IS_RELEASE
// Make sure to #define CSR_IS_RELEASE according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_IS_RELEASE 0
#endif
#ifndef CSR_RESOLVE_TODO
// Make sure to #define CSR_RESOLVE_TODO according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_RESOLVE_TODO 0
#endif
#ifndef CSR_RESOLVE_WARN
// Make sure to #define CSR_RESOLVE_WARN according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_RESOLVE_WARN 0
#endif
#ifndef CSR_USE_UTILITY
// Make sure to #define CSR_USE_UTILITY according to your project
// inside "csrlib.h"
// Are you including an uptodate version of csrlib.h ?
static_assert(false, "incorrect csrlib.h");
#define CSR_USE_UTILITY 1
#endif

#endif



#include <cstddef>
#include <bitset>
#include <type_traits>
#include <thread>
#include <chrono>
#include <ostream>


#if CSR_ISOSTD >= 14
#define csrctex constexpr
#else
#define csrctex
#endif

#if CSR_ISOSTD >= 17
#define csrndc(x) [[nodiscard]]
#define csrifcx(arg) if constexpr(arg)
#else
#define csrndc(x)
#define csrifcx(arg) if
#endif

#if CSR_ISOSTD >= 20
#undef csrndc
#define csrndc(x) [[nodiscard(x)]]
#endif

#if CSR_IS_RELEASE
#define CSR_RESOLVE_TODO 1
#define CSR_RESOLVE_WARN 1
#endif


#if CSR_USE_UTILITY

#define TODO static_assert(!CSR_RESOLVE_TODO,"Unresolved TODO-Item!")
#define static_warnif(cond) static_assert(!(cond) || !CSR_RESOLVE_WARN,"Unresolved static warning!")

#define range(var, len) for(std::size_t var = 0; var < (len); var++)

#if !CSR_IS_RELEASE
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
			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool equal(BASE a, BASE b) noexcept;
			
			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool not_equal(BASE a, BASE b) noexcept;

			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool greater(BASE a, BASE b) noexcept;

			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool less(BASE a, BASE b) noexcept;

			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool greater_equal(BASE a, BASE b) noexcept;

			// #include "csrtfloat.h"
			template <typename BASE = float, uint16_t nUnitAbsTol = 100, uint16_t nUnitRelTol = nUnitAbsTol, bool ignoreIEC559 = false, typename>
			bool less_equal(BASE a, BASE b) noexcept;
		}
	}

	namespace data
	{
		// #include "csrmask.h"
		template <typename baseType, typename = typename std::enable_if<
			std::is_enum<baseType>::value &&
			!std::is_convertible<baseType, typename std::underlying_type<baseType>::type>::value &&
			!std::is_same<typename std::underlying_type<baseType>::type, bool>::value
			, void>::type> class mask;
		
	}

	namespace util
	{
		namespace enumc
		{
			// #include "csruitl.h"
			template <typename enumT, typename>
			inline constexpr enumT operator| (const enumT& a, const enumT& b);

			// #include "csruitl.h"
			template <typename enumT, typename>
			inline constexpr enumT operator& (const enumT& a, const enumT& b);

			// #include "csruitl.h"
			template <typename enumT, typename>
			inline constexpr enumT operator^ (const enumT& a, const enumT& b);

			// #include "csruitl.h"
			template <typename enumT, typename>
			inline constexpr enumT operator~ (const enumT& a);
		}

		// #include "csrtimer.h"
		template <typename timeScale = csr::args::TTS::ms, typename = typename std::enable_if<
			std::is_same<timeScale, std::nano>::value ||
			std::is_same<timeScale, std::micro>::value ||
			std::is_same<timeScale, std::milli>::value ||
			std::is_same<timeScale, std::ratio<1>>::value ||
			std::is_same<timeScale, std::ratio<60, 1>>::value ||
			std::is_same<timeScale, std::ratio<3600, 1>>::value
			, void>::type> 
		class Timer;

		namespace cstr
		{
			// #include "csrcstr.h"
			inline std::size_t length(const char* str) noexcept;
			
			// #include "csrcstr.h"
			inline std::size_t length(const char* str, std::size_t maxCnt) noexcept;

			// #include "csrcstr.h"
			inline void copy(char*& dest, const char* source) noexcept;

			// #include "csrcstr.h"
			inline void copy(char*& dest, const char* source, const std::size_t maxCnt) noexcept;

			// #include "csrcstr.h"
			inline bool equal(const char* str1, const char* str2) noexcept;

			// #include "csrcstr.h"
			inline bool prefix(const char* pre, const char* str) noexcept;

			// #include "csrcstr.h"
			inline bool suffix(const char* suf, const char* str) noexcept;

			// #include "csrcstr.h"
			template<typename IntType = int, typename>
			inline IntType toInt(const char* str) noexcept;

			// #include "csrcstr.h"
			inline unsigned int split(const char* str, char**& subStrs, char delim = ' ') noexcept;

			// #include "csrcstr.h"
			inline unsigned int distance(const char* str1, const char* str2) noexcept;

			// #include "csrcstr.h"
			inline char** alignL(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen = 0) noexcept;

			// #include "csrcstr.h"
			inline char** alignR(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen = 0) noexcept;

			// #include "csrcstr.h"
			inline char** alignC(const char* strs[], const std::size_t& numStrs, const std::size_t& targetLen = 0) noexcept;

			// #include "csrcstr.h"
			inline char* blocktext(const char* strs[], const std::size_t& numStrs, std::size_t targetLen) noexcept;
		}
		
		// #include "csrprompt.h"
		class CmdArgs;
		
		// #include "csrprompt.h"
		class CmdCenter;
	}
}

namespace cstar {}

#endif