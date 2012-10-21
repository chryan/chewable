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
 * @file test_Thread.cpp
 * @brief Unit testing for thread class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Thread/Thread.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

int threadNumber = 10;
int threadData = 12938;

class ThreadObject : public Runnable
{
public:
	virtual void Run()
	{
		Thread::Sleep( 0.5f );
		threadNumber += 10;
	}
};

void ThreadFunction( void * args )
{
	int * num = reinterpret_cast< int * >( args );
	ASSERT_EQ( *num, threadNumber );
	ASSERT_EQ( num, &threadNumber );

	int * dat = Thread::GetCurrent()->Data.Find< int >( "int" );
	ASSERT_EQ( *dat, threadData );

	*num += 20;
}

void ThreadFunction2( void * args )
{
	int * num = reinterpret_cast< int * >( args );
	ASSERT_EQ( *num, threadNumber );
	ASSERT_EQ( num, &threadNumber );

	int * dat = Thread::GetCurrent()->Data.Find< int >( "int" );
	ASSERT_EQ( *dat, threadData );

	// 0.5 seconds should be enough of a wait.
	Thread::Sleep( 0.5f );
	*num += 20;
}

TEST( ThreadFixture, Thread_Test )
{
	Thread newThread;
	ThreadObject obj;

	newThread.Data.Add( "int", &threadData );

	newThread.Start( &ThreadFunction, &threadNumber );
	newThread.Join();
	ASSERT_EQ( threadNumber, 30 );

	newThread.Start( &ThreadFunction2, &threadNumber );
	ASSERT_EQ( threadNumber, 30 );
	newThread.Join();
	ASSERT_EQ( threadNumber, 50 );

	newThread.Start( obj );
	ASSERT_EQ( threadNumber, 50 );
	newThread.Join();
	ASSERT_EQ( threadNumber, 60 );
}
