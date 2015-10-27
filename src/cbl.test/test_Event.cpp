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
 * @file test_Event.cpp
 * @brief Unit testing for events.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/Event.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

typedef Event< void( int x, int y ) > TestEvent;

//! Event test fixture.
class EventTestFixture : public ::testing::Test
{
protected:

	//! Test listener class.
	class TestListener
	{
	public:
		void OnEvent( int x, int y )
		{
			ASSERT_TRUE( x == TestX );
			ASSERT_TRUE( y == TestY );
		}
	};

	//! Setup fixture with static data for checking.
	void SetUp()
	{
	}

	//! Static member function (behaves just like a regular function)
	static void TestFunction( int x, int y )
	{
		ASSERT_TRUE( x == EventTestFixture::TestX );
		ASSERT_TRUE( y == EventTestFixture::TestY );
	}

protected:

	TestListener		listener;
	TestEvent			evt;

	static const int TestX		= 10;
	static const int TestY		= 5;
};

TEST_F( EventTestFixture, Event_ObjectTest )
{
	printf( "%d", sizeof( evt ) );
	evt.Register( TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(&listener) );
	evt.Raise( 10, 5 );
	evt.Unregister( TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(&listener) );
	evt.Raise( 10, 5 );

	evt += TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(&listener);
	evt.Raise( 10, 5 );
	evt -= TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(&listener);
	evt.Raise( 10, 5 );
}

TEST_F( EventTestFixture, Event_FunctionTest )
{
	evt.Register( TestEvent::DelegateType::FromFunction< &EventTestFixture::TestFunction >() );
	evt.Raise( 10, 5 );
	evt.Unregister( TestEvent::DelegateType::FromFunction< &EventTestFixture::TestFunction >() );
	evt.Raise( 10, 5 );
	
	evt += TestEvent::DelegateType::FromFunction< &EventTestFixture::TestFunction >();
	evt.Raise( 10, 5 );
	evt -= TestEvent::DelegateType::FromFunction< &EventTestFixture::TestFunction >();
	evt.Raise( 10, 5 );
}


//! Event unregistration fixture.
//! This is to test when a listener unregisters itself when the event is called.
class EventUnregisterFixture : public ::testing::Test
{
protected:

	//! Test listener class.
	class TestListener
	{
	public:
		TestListener() 
		: testEvent( NULL ), tX( 0 ), tY( 0 )
		{
		}

		void OnEvent( int x, int y )
		{
			ASSERT_TRUE( testEvent != NULL );
			tX += x;
			tY += y;
			*testEvent -= TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(this);
		}

		TestEvent*	testEvent;
		int			tX;
		int			tY;
	};

	class TestListenerOther
	{
	public:
		TestListenerOther() 
			: unreg( NULL ), testEvent( NULL ), tX( 0 ), tY( 0 )
		{
		}

		void OnEvent( int x, int y )
		{
			ASSERT_TRUE( testEvent != NULL );
			tX += x;
			tY += y;
			*testEvent -= TestEvent::Method<CBL_E_METHOD(TestListenerOther,OnEvent)>(this);
			if( unreg )
				*testEvent -= TestEvent::Method<CBL_E_METHOD(TestListenerOther,OnEvent)>(unreg);
		}

		TestListenerOther* unreg;
		TestEvent*	testEvent;
		int			tX;
		int			tY;
	};

	//! Setup fixture with static data for checking.
	void SetUp()
	{
		listener.testEvent = &evt;

		ol1.unreg = &ol2;
		ol1.testEvent = &evt;
		ol2.testEvent = &evt;
	}

protected:

	TestListener		listener;
	TestListenerOther	ol1, ol2;
	TestEvent			evt;
};

TEST_F( EventUnregisterFixture, EventCurrentUnregister )
{
	evt += TestEvent::Method<CBL_E_METHOD(TestListener,OnEvent)>(&listener);
	evt.Raise( 10, 5 );
	evt.Raise( 10, 5 );

	ASSERT_EQ( listener.tX, 10 );
	ASSERT_EQ( listener.tY, 5 );

	evt += TestEvent::Method<CBL_E_METHOD(TestListenerOther,OnEvent)>(&ol1);
	evt += TestEvent::Method<CBL_E_METHOD(TestListenerOther,OnEvent)>(&ol2);
	evt.Raise( 10, 5 );
	evt.Raise( 10, 5 );

	ASSERT_EQ( ol1.tX, 10 );
	ASSERT_EQ( ol1.tY, 5 );
	ASSERT_EQ( ol2.tX, 0 );
	ASSERT_EQ( ol2.tY, 0 );
}
