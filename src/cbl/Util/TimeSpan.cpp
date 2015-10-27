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
 * @file TimeSpan.cpp
 * @brief TimeSpan structure definition.
 */

// Chewable Headers //
#include "cbl/Util/TimeSpan.h"

// Precompiled Headers //
#include "cbl/StdAfx.h"

#include <ctime>

using namespace cbl;

const Int64		TimeSpan::TicksPerDay			= 864000000000;
const Int64		TimeSpan::TicksPerHour			= 36000000000;
const Int64		TimeSpan::TicksPerMinute		= 600000000;
const Int64		TimeSpan::TicksPerSecond		= 10000000;
const Int64		TimeSpan::TicksPerMillisecond	= 10000;

const TimeSpan	TimeSpan::MaxValue			= TimeSpan( LLONG_MAX );
const TimeSpan	TimeSpan::MinValue			= TimeSpan( LLONG_MIN );
const TimeSpan	TimeSpan::Zero				= TimeSpan( 0 );

TimeSpan::TimeSpan( Int64 ticks )
: mTicks( ticks )
, mTotalDays( TimeReal( mTicks ) / TimeReal( TicksPerDay ) )
, mTotalHours( TimeReal( mTicks ) / TimeReal( TicksPerHour ) )
, mTotalMilliseconds( TimeReal( mTicks ) / TimeReal( TicksPerMillisecond ) )
, mTotalMinutes( TimeReal( mTicks ) / TimeReal( TicksPerMinute ) )
, mTotalSeconds( TimeReal( mTicks ) / TimeReal( TicksPerSecond ) )
{
}

TimeSpan::TimeSpan( Int32 hrs, Int32 mins, Int32 secs )
: mTicks( hrs * TicksPerHour + mins * TicksPerMinute + secs * TicksPerSecond )
, mTotalDays( TimeReal( mTicks ) / TimeReal( TicksPerDay ) )
, mTotalHours( TimeReal( mTicks ) / TimeReal( TicksPerHour ) )
, mTotalMilliseconds( TimeReal( mTicks ) / TimeReal( TicksPerMillisecond ) )
, mTotalMinutes( TimeReal( mTicks ) / TimeReal( TicksPerMinute ) )
, mTotalSeconds( TimeReal( mTicks ) / TimeReal( TicksPerSecond ) )
{
}

TimeSpan::TimeSpan( Int32 days, Int32 hrs, Int32 mins, Int32 secs )
: mTicks( days * TicksPerDay + hrs * TicksPerHour + mins * TicksPerMinute + secs * TicksPerSecond )
, mTotalDays( TimeReal( mTicks ) / TimeReal( TicksPerDay ) )
, mTotalHours( TimeReal( mTicks ) / TimeReal( TicksPerHour ) )
, mTotalMilliseconds( TimeReal( mTicks ) / TimeReal( TicksPerMillisecond ) )
, mTotalMinutes( TimeReal( mTicks ) / TimeReal( TicksPerMinute ) )
, mTotalSeconds( TimeReal( mTicks ) / TimeReal( TicksPerSecond ) )
{
}

TimeSpan::TimeSpan( Int32 days, Int32 hrs, Int32 mins, Int32 secs, Int32 msecs )
: mTicks( days * TicksPerDay + hrs * TicksPerHour + mins * TicksPerMinute + secs * TicksPerSecond + msecs * TicksPerMillisecond )
, mTotalDays( TimeReal( mTicks ) / TimeReal( TicksPerDay ) )
, mTotalHours( TimeReal( mTicks ) / TimeReal( TicksPerHour ) )
, mTotalMilliseconds( TimeReal( mTicks ) / TimeReal( TicksPerMillisecond ) )
, mTotalMinutes( TimeReal( mTicks ) / TimeReal( TicksPerMinute ) )
, mTotalSeconds( TimeReal( mTicks ) / TimeReal( TicksPerSecond ) )
{
}

const String TimeSpan::ToString( void ) const
{
	Uint64 days = Math::Abs< Uint64, Int64 >( Days() );
	Uint64 hrs = Math::Abs< Uint64, Int64 >( Hours() );
	Uint64 mins = Math::Abs< Uint64, Int64 >( Minutes() );
	Uint64 secs = Math::Abs< Uint64, Int64 >( Seconds() );

	Uint64 fraction = Math::Abs< Uint64, Int64 >(
		Math::Abs< Int64 >( mTicks ) -
		days * TicksPerDay -
		hrs * TicksPerHour -
		mins * TicksPerMinute -
		secs * TicksPerSecond
	);

	char timeString[50] = {0};
	char dayString[50] = {0};
	
	if( days > 0 )
		std::sprintf(dayString, "%lld.", days);

	sprintf( timeString, "%s%s%0.2lld:%0.2lld:%0.2lld.%0.3lld", ( mTicks < 0 ? "-" : "" ),
		dayString, hrs, mins, secs, fraction / TicksPerMillisecond );

	return String( timeString );
}

const String TimeSpan::GetSystemTime( void )
{
	char	sysTime[9] = { 0 };
	tm		* timeInfo;

	std::time_t currentTime = std::time(nullptr);
	timeInfo = std::localtime(&currentTime);

	if( timeInfo )
		sprintf( sysTime, "%0.2i:%0.2i:%0.2i", timeInfo->tm_hour, timeInfo->tm_min, timeInfo->tm_sec );

	return String( sysTime );
}

Ostream & operator << ( Ostream & stream, const TimeSpan & rhs )
{
	stream << rhs.ToString(); return stream;
}

const TimeSpan operator / ( const TimeSpan & ts, Int64 val )
{
	return TimeSpan( ts.Ticks() / val );
}
