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
 * @file TimeSpan.h
 * @brief TimeSpan structure to hold time information.
 */

#ifndef __CBL_TIMESPAN_H_
#define __CBL_TIMESPAN_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Functions.h"
#include "cbl/Util/String.h"

namespace cbl
{
	//! @brief TimeSpan structure to hold time/ticks information. Modeled after C# version.
	//! While the C# TimeSpan uses Ticks as its smallest time unit, Chewable's TimeSpan uses Milliseconds instead.
	//! 
	//! @see http://msdn.microsoft.com/en-us/library/system.timespan_members.aspx
	class CBL_API TimeSpan
	{
	/***** Static Constants *****/
	public:
		static const Int64		TicksPerDay;			//!< Number of ticks per day.
		static const Int64		TicksPerHour;			//!< Number of ticks per hour.
		static const Int64		TicksPerMinute;			//!< Number of ticks per minute.
		static const Int64		TicksPerSecond;			//!< Number of ticks per second.
		static const Int64		TicksPerMillisecond;	//!< Number of ticks per minute.

		static const TimeSpan	MaxValue;				//!< Maximum TimeSpan value.
		static const TimeSpan	MinValue;				//!< Minimum TimeSpan value.
		static const TimeSpan	Zero;					//!< Zero TimeSpan value.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		TimeSpan( Int64 ticks = 0 );
		//! Constructor.
		//! @param	hrs		Whole hours.
		//! @param	mins	Whole mins.
		//! @param	secs	Whole secs.
		TimeSpan( Int32 hrs, Int32 mins, Int32 secs );
		//! Constructor.
		//! @param	days	Whole days.
		//! @param	hrs		Whole hours.
		//! @param	mins	Whole mins.
		//! @param	secs	Whole secs.
		TimeSpan( Int32 days, Int32 hrs, Int32 mins, Int32 secs );
		//! Constructor.
		//! @param	days	Whole days.
		//! @param	hrs		Whole hours.
		//! @param	mins	Whole mins.
		//! @param	secs	Whole secs.
		TimeSpan( Int32 days, Int32 hrs, Int32 mins, Int32 secs, Int32 msecs );
		//! Returns a new TimeSpan object with the absolute value of 
		//! the calling TimeSpan object.
		//! @return			New TimeSpan object.
		const TimeSpan Duration( void );

		//! Get number of whole days.
		const Int64 Days( void ) const;
		//! Get number of whole hours.
		const Int64 Hours( void ) const;
		//! Get number of whole milliseconds.
		const Int64 Milliseconds( void ) const;
		//! Get number of whole minutes.
		const Int64 Minutes( void ) const;
		//! Get number of whole seconds.
		const Int64 Seconds( void ) const;
		//! Get number of ticks.
		const Int64 Ticks( void ) const;

		//! Get number of fractional days.
		const TimeReal TotalDays( void ) const;
		//! Get number of fractional hours.
		const TimeReal TotalHours( void ) const;
		//! Get number of fractional milliseconds.
		const TimeReal TotalMilliseconds( void ) const;
		//! Get number of fractional minutes.
		const TimeReal TotalMinutes( void ) const;
		//! Get number of fractional seconds.
		const TimeReal TotalSeconds( void ) const;
		//! Convert the TimeSpan to a formatted time string.
		const String ToString( void ) const;

	/***** Static Methods *****/
	public:
		//! Get a TimeSpan from the number of days. Accurate to nearest millisecond.
		static const TimeSpan FromDays( TimeReal days );
		//! Get a TimeSpan from the number of hours. Accurate to nearest millisecond.
		static const TimeSpan FromHours( TimeReal hours );
		//! Get a TimeSpan from the number of milliseconds.
		static const TimeSpan FromMilliseconds( TimeReal msecs );
		//! Get a TimeSpan from the number of minutes. Accurate to nearest millisecond.
		static const TimeSpan FromMinutes( TimeReal mins );
		//! Get a TimeSpan from the number of seconds. Accurate to nearest millisecond.
		static const TimeSpan FromSeconds( TimeReal secs );
		//! Get the system time in the format [hh:mm:ss].
		static const String GetSystemTime( void );

	/***** Operators *****/
	public:
		//! Negation operator.
		const TimeSpan operator - ( void ) const;
		//! Addition operator.
		const TimeSpan operator + ( const TimeSpan & rhs ) const;
		//! Subtraction operator.
		const TimeSpan operator - ( const TimeSpan & rhs ) const;
		//! Scaling operator.
		const TimeSpan operator * ( Real scale ) const;
		//! Equivalence operator.
		const bool operator == ( const TimeSpan & rhs ) const;
		//! Inequivalence operator.
		const bool operator != ( const TimeSpan & rhs ) const;
		//! Less than operator.
		const bool operator > ( const TimeSpan & rhs ) const;
		//! Less than or equal operator.
		const bool operator >= ( const TimeSpan & rhs ) const;
		//! Greater than operator.
		const bool operator < ( const TimeSpan & rhs ) const;
		//! Greater than or equal operator.
		const bool operator <= ( const TimeSpan & rhs ) const;
		//! Increment and assignment operator.
		TimeSpan & operator += ( const TimeSpan & rhs );
		//! Decrement and assignment operator.
		TimeSpan & operator -= ( const TimeSpan & rhs );
		//! Scaling and assignment operator.
		TimeSpan & operator *= ( Real scale );

	/***** Private Methods *****/
	private:
		void ResetTotals( void );

	/***** Private Members *****/
	private:
		//! Number of ticks.
		//! The smallest unit of time is the tick, which is equal to 100 nanoseconds.
		//! A tick can be negative or positive.
		Int64		mTicks;
		TimeReal	mTotalDays;
		TimeReal	mTotalHours;
		TimeReal	mTotalMilliseconds;
		TimeReal	mTotalMinutes;
		TimeReal	mTotalSeconds;
	};
	
	/***** Inline Methods *****/
	inline const TimeSpan TimeSpan::Duration( void )
		{ return TimeSpan( Math::Abs<Int64>(mTicks) ); }
	inline const Int64 TimeSpan::Days( void ) const
		{ return ( mTicks / TicksPerDay ); }
	inline const Int64 TimeSpan::Hours( void ) const
		{ return ( mTicks / TicksPerHour ) % 24; }
	inline const Int64 TimeSpan::Milliseconds( void ) const
		{ return ( mTicks / TicksPerMillisecond ) % 1000; }
	inline const Int64 TimeSpan::Minutes( void ) const
		{ return ( mTicks / TicksPerMinute ) % 60; }
	inline const Int64 TimeSpan::Seconds( void ) const
		{ return ( mTicks / TicksPerSecond ) % 60; }
	inline const Int64 TimeSpan::Ticks( void ) const
		{ return mTicks; }

	inline const TimeReal TimeSpan::TotalDays( void ) const
		{ return mTotalDays; }
	inline const TimeReal TimeSpan::TotalHours( void ) const
		{ return mTotalHours; }
	inline const TimeReal TimeSpan::TotalMilliseconds( void ) const
		{ return mTotalMilliseconds; }
	inline const TimeReal TimeSpan::TotalMinutes( void ) const
		{ return mTotalMinutes; }
	inline const TimeReal TimeSpan::TotalSeconds( void ) const
		{ return mTotalSeconds; }

	/***** Inline Static Methods *****/
	inline const TimeSpan TimeSpan::FromDays( TimeReal days )
		{ return TimeSpan( Math::Round< Int64 >( days * TicksPerDay ) ); }
	inline const TimeSpan TimeSpan::FromHours( TimeReal hours )
		{ return TimeSpan( Math::Round< Int64 >( hours * TicksPerHour ) ); }
	inline const TimeSpan TimeSpan::FromMilliseconds( TimeReal msecs )
		{ return TimeSpan( Math::Round< Int64 >( msecs * TicksPerMillisecond ) ); }
	inline const TimeSpan TimeSpan::FromMinutes( TimeReal mins )
		{ return TimeSpan( Math::Round< Int64 >( mins * TicksPerMinute ) ); }
	inline const TimeSpan TimeSpan::FromSeconds( TimeReal secs )
		{ return TimeSpan( Math::Round< Int64 >( secs * TicksPerSecond ) ); }

	/***** Inline Operators *****/
	inline const TimeSpan TimeSpan::operator - ( void ) const
		{ return TimeSpan( -mTicks ); }
	inline const TimeSpan TimeSpan::operator + ( const TimeSpan & rhs ) const
		{ return TimeSpan( mTicks + rhs.mTicks ); }
	inline const TimeSpan TimeSpan::operator - ( const TimeSpan & rhs ) const
		{ return TimeSpan( mTicks - rhs.mTicks ); }
	inline const TimeSpan TimeSpan::operator * ( Real scale ) const
		{ return TimeSpan( Int64( mTicks * scale ) ); }
	inline const bool TimeSpan::operator == ( const TimeSpan & rhs ) const
		{ return ( mTicks == rhs.mTicks ); }
	inline const bool TimeSpan::operator != ( const TimeSpan & rhs ) const
		{ return ( mTicks != rhs.mTicks ); }
	inline const bool TimeSpan::operator > ( const TimeSpan & rhs ) const
		{ return ( mTicks > rhs.mTicks ); }
	inline const bool TimeSpan::operator >= ( const TimeSpan & rhs ) const
		{ return ( mTicks >= rhs.mTicks ); }
	inline const bool TimeSpan::operator < ( const TimeSpan & rhs ) const
		{ return ( mTicks < rhs.mTicks ); }
	inline const bool TimeSpan::operator <= ( const TimeSpan & rhs ) const
		{ return ( mTicks <= rhs.mTicks ); }
	inline TimeSpan & TimeSpan::operator += ( const TimeSpan & rhs )
		{ mTicks += rhs.mTicks; ResetTotals(); return *this; }
	inline TimeSpan & TimeSpan::operator -= ( const TimeSpan & rhs )
		{ mTicks -= rhs.mTicks; ResetTotals(); return *this; }
	inline TimeSpan & TimeSpan::operator *= ( Real scale )
		{ mTicks = Int64( mTicks * scale ); ResetTotals(); return *this; }

	inline void TimeSpan::ResetTotals( void ) {
		mTotalDays			= TimeReal(mTicks)/TimeReal(TicksPerDay);
		mTotalHours			= TimeReal(mTicks)/TimeReal(TicksPerHour);
		mTotalMilliseconds	= TimeReal(mTicks)/TimeReal(TicksPerMillisecond);
		mTotalMinutes		= TimeReal(mTicks)/TimeReal(TicksPerMinute);
		mTotalSeconds		= TimeReal(mTicks)/TimeReal(TicksPerSecond);
	}
}

/***** Support Functions *****/
CBL_API cbl::Ostream & operator << ( cbl::Ostream & stream, const cbl::TimeSpan & rhs );
CBL_API const cbl::TimeSpan operator / ( const cbl::TimeSpan & ts, cbl::Int64 val );

#endif // __CBL_TIMESPAN_H_
