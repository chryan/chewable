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
 * @file test_Stopwatch.cpp
 * @brief Unit testing for the stopwatch class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Thread/Thread.h>
#include <cbl/Util/Stopwatch.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class StopwatchFixture : public ::testing::Test
{
protected:

	void SetUp()
	{
		timeTest = 0.25;
		tolerance = 0.1;
	}

	Stopwatch	testStopwatch;
	Float64		timeTest;
	Float64		tolerance;
};

TEST_F( StopwatchFixture, Stopwatch_AccuracyTest )
{
	testStopwatch.Start();
	Thread::Sleep( Real( timeTest ) );
	testStopwatch.Stop();

	Float64 tmp = testStopwatch.GetElapsedTime().TotalSeconds();
	ASSERT_NEAR( tmp, timeTest, tolerance );
}

TEST_F( StopwatchFixture, Stopwatch_LapAccuracyTest )
{
	Float64 lap		= 0.0;
	
	testStopwatch.Start();
	
	Thread::Sleep( Real( timeTest ) );
	lap = testStopwatch.GetLapTime().TotalSeconds();
	ASSERT_NEAR( lap, timeTest, tolerance );
	lap = testStopwatch.GetLapTime().TotalSeconds();

	ASSERT_NEAR( lap, 0.0, tolerance ); // Near 0.
	
	Thread::Sleep( Real( timeTest ) );
	lap = testStopwatch.GetLapTime().TotalSeconds();
	ASSERT_NEAR( lap, timeTest, tolerance );
	
	testStopwatch.Stop();

	Thread::Sleep( 0.1f );

	ASSERT_EQ( testStopwatch.GetLapTime().TotalSeconds(), 0.0 );
}