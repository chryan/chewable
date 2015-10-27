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
 * @file test_Delegate.cpp
 * @brief Unit testing for (member) function delegates.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Util/Delegate.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

void TestVoidFunc() { printf( "Void Function" ); }
std::string TestDelegateFunc1( int t ) { printf( "Test function 1 called %i\n", t ); return "Function1"; }
std::string TestDelegateFunc2( int t1, int t2 ) { printf( "Test function 2 called %i %i\n", t1, t2 ); return "Function2"; }
std::string TestDelegateFunc3( int t1, int t2, int t3 ) { printf( "Test function 3 called %i %i %i\n", t1, t2, t3 ); return "Function3"; }

class TestObj
{
public:
	std::string operator()(const int & t)
	{
		printf( "TestObj %i\n", t );
		return "TestObj1";
	}
};

class TestObj2 :
	public TestObj
{
public:
	TestObj2( const Char * str )
		: String( str )
	{
	}
	
public:
	std::string OnEvent( int t1, int t2 )
	{
		printf( "%s %i %i\n", String.c_str(), t1, t2 );
		return String;
	}
	
private:
	std::string String;
};

typedef Delegate< void() > Delegate0P;
typedef Delegate< std::string ( int ) > Delegate1P;
typedef Delegate< std::string ( int,int ) > Delegate2P;
typedef Delegate< std::string ( int,int,int ) > Delegate3P;

TEST( DelegateTestFixture, Delegate_Test )
{	
	TestObj2 obj1( "OBJECT1" );
	TestObj2 obj2( "OBJECT2" );
	
	Delegate0P dg0 = Delegate0P::FromFunction<&TestVoidFunc>();
	Delegate1P dg1 = Delegate1P::FromFunction<&TestDelegateFunc1>();
	Delegate2P dg2 = Delegate2P::FromFunction<&TestDelegateFunc2>();
	Delegate3P dg3 = Delegate3P::FromFunction<&TestDelegateFunc3>();
	Delegate2P dg4 = Delegate2P::FromMethod< TestObj2, &TestObj2::OnEvent >(&obj1);
	Delegate2P dg5 = Delegate2P::FromMethod< TestObj2, &TestObj2::OnEvent >(&obj2);
	Delegate2P dg6 = Delegate2P::FromMethod< TestObj2, &TestObj2::OnEvent >(&obj1);
	Delegate3P dg7 = Delegate3P::FromFunction<&TestDelegateFunc3>();
	
	int t1 = 1, t2 = 2, t3 = 3;
	ASSERT_EQ( dg1( t1 ), "Function1" );
	ASSERT_EQ( dg2( t1, t2 ), "Function2" );
	ASSERT_EQ( dg3( t1, t2, t3 ), "Function3" );
	ASSERT_EQ( dg4( t1, t2 ), "OBJECT1" );
	ASSERT_EQ( dg5( t1, t2 ), "OBJECT2" );
	ASSERT_EQ( dg6( t1, t2 ), "OBJECT1" );
	
	ASSERT_EQ( dg4, dg6 );
	ASSERT_EQ( dg3, dg7 );
}
