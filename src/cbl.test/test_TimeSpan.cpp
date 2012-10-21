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
 * @file test_TimeSpan.cpp
 * @brief Unit testing for time span structures.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/TimeSpan.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

const Float64 tolerance = 0.001;

TEST( TimeSpanFixture, TimeSpan_AccuracyTest )
{
    TimeSpan timeSpan( 1111, 2222, 3333, 4444, 5555 );

	ASSERT_NEAR( timeSpan.TotalDays(), 1205.94941614583, tolerance );
	ASSERT_NEAR( timeSpan.TotalHours(), 28942.7859875, tolerance );
	ASSERT_NEAR( timeSpan.TotalMinutes(), 1736567.15925, tolerance );
	ASSERT_NEAR( timeSpan.TotalSeconds(), 104194029.555, tolerance );
	ASSERT_NEAR( timeSpan.TotalMilliseconds(), 104194029555.0, tolerance );
	ASSERT_EQ( timeSpan.Days(), 1205 );
	ASSERT_EQ( timeSpan.Hours(), 22 );
	ASSERT_EQ( timeSpan.Minutes(), 47 );
	ASSERT_EQ( timeSpan.Seconds(), 9 );
	ASSERT_EQ( timeSpan.Milliseconds(), 555 );
	ASSERT_EQ( timeSpan.ToString(), "1205.22:47:09.555" );
}

TEST( TimeSpanFixture2, TimeSpan_FromTest )
{
	TimeSpan timeSpan = TimeSpan::FromDays( 20.84745602 );

	ASSERT_NEAR( timeSpan.TotalDays(), 20.8474560185185, tolerance );
	ASSERT_NEAR( timeSpan.TotalHours(), 500.338944444444, tolerance );
	ASSERT_NEAR( timeSpan.TotalMinutes(), 30020.3366666667, tolerance );
	ASSERT_NEAR( timeSpan.TotalSeconds(), 1801220.2, tolerance );
	ASSERT_NEAR( timeSpan.TotalMilliseconds(), 1801220200.12800002098083496, tolerance );
	ASSERT_EQ( timeSpan.Days(), 20 );
	ASSERT_EQ( timeSpan.Hours(), 20 );
	ASSERT_EQ( timeSpan.Minutes(), 20 );
	ASSERT_EQ( timeSpan.Seconds(), 20 );
	ASSERT_EQ( timeSpan.Milliseconds(), 200 );
	ASSERT_EQ( timeSpan.ToString(), "20.20:20:20.200" );
}
