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
 * @file test_Mutex.cpp
 * @brief Unit testing for mutex class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Thread/Mutex.h>
#include <cbl/Thread/Thread.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

Mutex mtx;

void mutexThread( void * args )
{
	mtx.Lock();

	int & num = *( reinterpret_cast< int * >( args ) );
	int tmp = num + 1;
	Thread::Yield();
	num = tmp;

	mtx.Unlock();
}

void mutexScopedThread( void * args )
{
	Mutex::ScopedLock lock( mtx );

	int & num = *( reinterpret_cast< int * >( args ) );
	int tmp = num + 1;
	Thread::Yield();
	num = tmp;
}

const Uint32 totalThreads = 100;

TEST( MutexFixture, Mutex_LockTest )
{
	int mutexNumber = 0;
	Thread newThread[totalThreads];

	for( int i = 0; i < totalThreads; ++i )
	{
		newThread[i].Start( mutexThread, &mutexNumber );
	}

	while( 1 )
	{
		bool finished = true;
		for( int i = 0; i < totalThreads; ++i )
		{
			if( !newThread[i].TryJoin(0) )
			{
				finished = false;
				break;
			}
		}

		if( finished )
			break;
	}

	ASSERT_EQ( mutexNumber, totalThreads );
}

TEST( MutexFixture, Mutex_ScopedLockTest )
{
	int mutexNumber = 0;
	Thread newThread[totalThreads];

	for( int i = 0; i < totalThreads; ++i )
	{
		newThread[i].Start( mutexScopedThread, &mutexNumber );
	}

	while( 1 )
	{
		bool finished = true;
		for( int i = 0; i < totalThreads; ++i )
		{
			if( !newThread[i].TryJoin(0) )
			{
				finished = false;
				break;
			}
		}

		if( finished )
			break;
	}

	ASSERT_EQ( mutexNumber, totalThreads );
}