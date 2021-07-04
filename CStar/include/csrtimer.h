#ifndef CSTARLIBRARY_TIMER
#define CSTARLIBRARY_TIMER
#include "csrlib.h"

namespace csr
{
	namespace tool
	{
		///Simple Timer with functions for stopwatching & scheduling
		///timeScale - the roughe scale of time wanted (e.g. tts:ms -> milliseconds)
		template<typename timeScale>
		class Timer<timeScale>
		{
			std::chrono::steady_clock::time_point tOld;
			std::chrono::steady_clock::time_point tClock;
			std::chrono::duration<long long, timeScale> tTotal;
			bool active;
		public:
			///Timer is paused in constructor
			Timer() :
				tClock{ std::chrono::steady_clock::time_point::max() },
				tTotal{ std::chrono::duration<long long, timeScale>(0) },
				active{ false } {}
			void reset() noexcept;
			void resume() noexcept;
			void pause() noexcept;
			csrndc("useless call of function: long long getTime()")
			constexpr long long getTime() const noexcept;
			static void wait(unsigned long long t) noexcept;
			void clock() noexcept;
			void clock(unsigned long long t) noexcept;
		};



		
		///Resets and Pauses the Timer 
		template<typename timeScale>
		void Timer<timeScale>::reset() noexcept
		{
			active = false;
			tTotal = std::chrono::duration<long long, timeScale>(0);
		}

		///Resumes the Timer
		template<typename timeScale>
		void Timer<timeScale>::resume() noexcept
		{
			if (!active)
			{
				active = true;
				tOld = std::chrono::steady_clock::now();
			}
		}

		///Pauses the Timer
		template<typename timeScale>
		void Timer<timeScale>::pause() noexcept
		{
			if (active)
			{
				active = false;
				tTotal += std::chrono::duration_cast<std::chrono::duration<long long, timeScale>>(std::chrono::steady_clock::now() - tOld);
			}
		}

		///Returns the (time * timeScale) that the Timer has been active(unpaused) for
		template<typename timeScale>
		constexpr long long Timer<timeScale>::getTime() const noexcept
		{
			if (active)
				return (tTotal + std::chrono::duration_cast<std::chrono::duration<long long, timeScale>>(std::chrono::steady_clock::now() - tOld)).count();
			else
				return (tTotal).count();
		}

		///Stops execution for (t * timeScale) seconds
		template<typename timeScale>
		void Timer<timeScale>::wait(unsigned long long t) noexcept
		{
			std::chrono::steady_clock::time_point tStart = std::chrono::steady_clock::now();
			float ms = (float)t * (float)timeScale::num * 1000.0f / (float)timeScale::den;
			if (ms > 20.0f)
				std::this_thread::sleep_for(std::chrono::duration<unsigned long long, timeScale>(t) - std::chrono::milliseconds(20));
			while (std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tStart).count() < t);
		}

		///Resets the clock
		template<typename timeScale>
		void Timer<timeScale>::clock() noexcept
		{
			tClock = std::chrono::steady_clock::now();
		}
		
		///Stops execution until (t * timeScale) seconds have passed since last call of clock(...)
		///- First call to clock(t) will only reset the clock
		template<typename timeScale>
		void Timer<timeScale>::clock(unsigned long long t) noexcept
		{
			long long dt = std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tClock).count();
			float ms = (float)(t - dt) * (float)timeScale::num * 1000.0f / (float)timeScale::den;
			if (ms > 20)
				std::this_thread::sleep_for(std::chrono::duration<unsigned long long, timeScale>((long long)ms) - std::chrono::milliseconds(20));
			while (std::chrono::duration_cast<std::chrono::duration<unsigned long long, timeScale>>(std::chrono::steady_clock::now() - tClock).count() < t);
			tClock = std::chrono::steady_clock::now();
		}


	}
}


#endif