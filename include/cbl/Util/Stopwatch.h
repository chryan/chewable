/* This source file is part of the Chewable Framework.
 * For the latest info, please visit http://chewable.googlecode.com/
 *
 * Copyright (c) 2009-2012 Ryan Chew
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *    http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * @file Stopwatch.h
 * @brief Utility class to keep track of system time.
 */

#ifndef __CBL_STOPWATCH_H_
#define __CBL_STOPWATCH_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/TimeSpan.h"
#include "cbl/Math/Functions.h"

namespace cbl
{
	//! @brief Stopwatch utility class used to measure time.
	class CBL_API Stopwatch
	{
	/***** Properties *****/
	public:
		//! Get stopwatch started flag.
		GETTER_AUTO( bool, Started );

		//! @brief Returns the total elapsed time since the stopwatch started.
		//! 
		//! The stopwatch will return the current total elapsed time since it started
		//! If the stopwatch is stopped, it will return the last recorded elapsed time from
		//! start to stop.
		//! @return
		//! 	Stopwatch's elapsed time since it started.
		const TimeSpan GetElapsedTime( void ) const;

		//! @brief Returns time since last lap was recorded.
		//! 
		//! Lap times are only recorded if the stopwatch has started.
		//! @return
		//! 	Decimal time since last lap, or 0.0 if stopwatch is not started.
		const TimeSpan GetLapTime( void ) const;

	/***** Static Methods *****/
	public:
		//! Get system ticks.
		//! @return		Current system ticks.
		static const Int64 GetSystemTicks( void );
		//! Get the system frequency.
		static const Int64 GetSystemFrequency( void );
		//! Get system's internal ticks (without the frequency division).
		static const Int64 GetInternalTicks( void );
	
	/***** Public Methods *****/
	public:
		//! Default constructor.
		Stopwatch();
		//! Destructor.
		~Stopwatch();
		//! Start stopwatch.
		void Start( void );
		//! Stop stopwatch.
		void Stop( void );
		//! Reset stopwatch.
		void Reset( void );

	/***** Private Members *****/
	private:
		mutable Int64	mLap;		//!< Lap total time in internal ticks.
		Int64			mStart;	//!< Stopwatch start time in internal ticks.
		Int64			mElapsed;	//!< Elapsed time since stopwatch started in internal ticks.
		bool			mStarted;		//!< Stopwatch started flag.
	};

	inline const TimeSpan Stopwatch::GetElapsedTime( void ) const {
		Int64 returnTicks = mStarted ? 
			GetInternalTicks() - mStart : mElapsed;
		return TimeSpan( ( returnTicks * TimeSpan::TicksPerSecond ) / GetSystemFrequency() );
	}

	inline const TimeSpan Stopwatch::GetLapTime( void ) const {
		if( !mStarted ) return TimeSpan::Zero;
		Int64 ticks = GetInternalTicks() - mLap;
		mLap += ticks;
		return TimeSpan( ( ticks * TimeSpan::TicksPerSecond ) / GetSystemFrequency() );
	}
}

#endif // __CBL_STOPWATCH_H_
