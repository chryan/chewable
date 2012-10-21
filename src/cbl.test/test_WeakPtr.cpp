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
 * @file test_SharedPtr.cpp
 * @brief Unit testing for shared pointers.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Util/WeakPtr.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class WeakClass
{
public:
	WeakClass() : Number( 0 ) {}
	Int32 Number;
};

class InheritedWeak : public WeakClass
{
};

TEST( WeakPtrFixture, WeakPtr_CountTest )
{
	SharedPtr< WeakClass > ptr( new WeakClass() );

	for( int i = 0; i < 5; ++i )
	{
		WeakPtr< WeakClass > weakPtr( ptr );
		ASSERT_EQ( weakPtr.Count(), 2 );
		ASSERT_EQ( ptr.Count(), 1 );
		ASSERT_TRUE( weakPtr.Lock() );
	}
	
	WeakPtr<WeakClass> weakPtr( ptr );
	WeakPtr<WeakClass> weakPtr2( weakPtr );
	
	ASSERT_EQ( weakPtr.Count(), 3 );
	ASSERT_EQ( ptr.Count(), 1 );
	
	ASSERT_TRUE( weakPtr.Lock() );
	ASSERT_TRUE( weakPtr2.Lock() );
}

TEST( WeakPtrFixture, WeakPtr_ValidityTest )
{
	WeakPtr< WeakClass > weakPtr;
	{
		SharedPtr< InheritedWeak > ptr( new InheritedWeak() );
		weakPtr = ptr;
		ASSERT_TRUE( weakPtr );
		ASSERT_TRUE( weakPtr.Lock() );
	}
	
	ASSERT_FALSE( weakPtr );
	ASSERT_FALSE( weakPtr.Lock() );
}