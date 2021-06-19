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
*/

/*
 * C* Library, 2021
 * Version 0.0.1
 * Project Link: https://github.com/DeveloperX19/CStar
 * Documentation: https://github.com/DeveloperX19/CStar/wiki
 */


/*
 *		=========================================>	   User Manual / Doc	===============================================>
 *		=[Documentation: Used Symbols]
 *		=	#	namespace
 *		=	?	keywords, short description
 *		=	o	class / struct
 *		=	%	function
 *		=	+	public field
 *		=[Documentation: Table of Content]
 *		=	1.		# CSR
 *		=	1.0		#	# args
 *		=	1.1		#	# math
 *		=	1.2		#	# math2d
 *		=	1.3		#	# math3d
 *		=	1.4		#	# math4d
 *		=	1.5		#	# data
 *		=	1.6		#	# util
 *		=	1.7		#	# stream
 *		=	1.8		#	# tool
 *		=
 *		=	2.		Setup Macros
 *		=	
 *		=========================================>
 *		=	
 *		=	...TODO...
 *		=	
 *		=	
 *		=	
 *		=	
 *		=	
 *		=	
 *		=	
 *		===================================================================================================================>
 */

/*
 *		=========================================>	Individual Setup Macros	===============================================>
 */



#define CSR_ISOSTD 17

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


	namespace data
	{
		template <typename baseType, typename _ = baseType> struct mask;

	}

	namespace util
	{
		namespace tfloat
		{
			///...
		}
		namespace enumc
		{
			//operator overload for scoped enums
			template <typename enumT, typename>
			inline constexpr enumT operator| (const enumT& a, const enumT& b);
			//operator overload for scoped enums
			template <typename enumT, typename>
			inline constexpr enumT operator& (const enumT& a, const enumT& b);
			//operator overload for scoped enums
			template <typename enumT, typename>
			inline constexpr enumT operator^ (const enumT& a, const enumT& b);
			//operator overload for scoped enums
			template <typename enumT, typename>
			inline constexpr enumT operator~ (const enumT& a);
		}
	}
		
	namespace tool
	{
		template <typename timeScale = csr::args::TTS::ms, typename _ = timeScale> class Timer;
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



/*
 *		=========================================>		 C-Star Body		===============================================>
 */


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

	namespace tool
	{
		///A Simple Timer with functions for stopwatching & scheduling
		///timeScale - the roughe scale of time wanted (e.g. tts:ms -> milliseconds)
		template <typename timeScale>
		class Timer<timeScale, typename std::enable_if<
			std::is_same<timeScale, std::nano>::value ||
			std::is_same<timeScale, std::micro>::value ||
			std::is_same<timeScale, std::milli>::value ||
			std::is_same<timeScale, std::ratio<1>>::value ||
			std::is_same<timeScale, std::ratio<60, 1>>::value ||
			std::is_same<timeScale, std::ratio<3600, 1>>::value
			, timeScale>::type>
		{
			std::chrono::steady_clock::time_point tOld;
			std::chrono::steady_clock::time_point tClock;
			std::chrono::duration<long long, timeScale> tTotal;
			bool active;
		public:
			///Timer is paused in constructor
			Timer() : tClock{ std::chrono::steady_clock::time_point::max() }, tTotal{ std::chrono::duration<long long, timeScale>(0) }, active{ false } {}

			///Resets and Pauses the Timer 
			void reset() noexcept
			{
				active = false;
				tTotal = std::chrono::duration<long long, timeScale>(0);
			}
			///Resumes the Timer
			void resume() noexcept
			{
				if (!active)
				{
					active = true;
					tOld = std::chrono::steady_clock::now();
				}
			}
			///Pauses the Timer
			void pause() noexcept
			{
				if (active)
				{
					active = false;
					tTotal += std::chrono::duration_cast<std::chrono::duration<long long, timeScale>>(std::chrono::steady_clock::now() - tOld);
				}
			}

			///Returns the (time * timeScale) that the Timer has been active(unpaused) for
			csrndc("useless call of function: long long getTime()")
			constexpr long long getTime() const noexcept
			{
				if (active)
					return (tTotal + std::chrono::duration_cast<std::chrono::duration<long long, timeScale>>(std::chrono::steady_clock::now() - tOld)).count();
				else
					return (tTotal).count();
			}

			///Stops execution for (t * timeScale) seconds
			static void wait(unsigned long long t) noexcept
			{
				std::chrono::steady_clock::time_point tStart = std::chrono::steady_clock::now();
				float ms = (float)t * (float)timeScale::num * 1000.0f / (float)timeScale::den;
				if (ms > 20.0f)
					std::this_thread::sleep_for(std::chrono::duration<unsigned long long, timeScale>(t) - std::chrono::milliseconds(20));
				while (std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tStart).count() < t);
			}

			///Resets the clock
			void clock() noexcept
			{
				tClock = std::chrono::steady_clock::now();
			}
			///Stops execution until (t * timeScale) seconds have passed since last call of clock(...)
			///- First call to clock(t) will only reset the clock
			void clock(unsigned long long t) noexcept
			{
				long long dt = std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tClock).count();
				float ms = (float)(t - dt) * (float)timeScale::num * 1000.0f / (float)timeScale::den;
				if (ms > 20)
					std::this_thread::sleep_for(std::chrono::duration<unsigned long long, timeScale>((long long)ms) - std::chrono::milliseconds(20));
				while (std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tClock).count() < t);
				tClock = std::chrono::steady_clock::now();
			}
		};


	}
}







#undef csrndc(x)

#endif