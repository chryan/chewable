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
 * @file Stopwatch.cpp
 * @brief Utility class to keep track of system time.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// External Dependencies //
#include <windows.h>

// Chewable Headers //
#include "cbl/Util/Stopwatch.h"

using namespace cbl;

Stopwatch::Stopwatch()
: mLap( 0 )
, mStart( 0 )
, mElapsed( 0 )
, mStarted( false )
{
}

Stopwatch::~Stopwatch()
{
}

void Stopwatch::Start( void )
{
	mStart = GetInternalTicks();
	mLap = mStart;
	mStarted = true;
}

void Stopwatch::Stop( void )
{
	mElapsed += GetInternalTicks() - mStart;
	mStarted = false;
}

void Stopwatch::Reset( void )
{
	mStart = 0;
	mElapsed = 0;
	mLap = 0;
	mStarted = false;
}
