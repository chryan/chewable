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
 * @file MutexImpl.cpp
 * @brief Windows 32bit mutex implementation.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Thread/Win32/MutexImpl.h"
#include "cbl/Util/Stopwatch.h"

using namespace cbl;

MutexImpl::MutexImpl()
{
	InitializeCriticalSectionAndSpinCount( &mCS, 4000 );
}

MutexImpl::~MutexImpl()
{
	DeleteCriticalSection( &mCS );
}

bool MutexImpl::TryLock_Impl( cbl::Uint32 milliseconds )
{
	const DWORD interval = 5;
	Int64 compare = Int64( milliseconds );

	Stopwatch timer;
	timer.Start();
	do
	{
		if (TryEnterCriticalSection( &mCS ) == TRUE )
			return true;

		::Sleep( interval );
	} while ( timer.GetElapsedTime().Milliseconds() < compare );

	return false;
}