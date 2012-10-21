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
#include <cbl/Util/SharedPtr.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class DummyClass
{
public:
	DummyClass() : Number( 0 ) {}
	Int32 Number;
};

class InheritedDummy : public DummyClass
{
};

TEST( SharedPtrFixture, SharedPtr_CountTest )
{
	SharedPtr<DummyClass> dummyPtr( new DummyClass );
	++dummyPtr->Number;

	ASSERT_EQ( dummyPtr.Count(), 1 );
	ASSERT_EQ( dummyPtr->Number, 1 );

	{
		SharedPtr<DummyClass> dummyPtr2 = dummyPtr;
		++dummyPtr2->Number;
		ASSERT_EQ( dummyPtr->Number, 2 );
		ASSERT_EQ( dummyPtr2->Number, 2 );
		ASSERT_EQ( dummyPtr.Count(), 2 );
		ASSERT_EQ( dummyPtr2.Count(), 2 );
	}
	
	++dummyPtr->Number;
	ASSERT_EQ( dummyPtr->Number, 3 );
	ASSERT_EQ( dummyPtr.Count(), 1 );
	
	SharedPtr<DummyClass> diffObjPtr( new DummyClass );
	ASSERT_EQ( diffObjPtr->Number, 0 );
	ASSERT_EQ( diffObjPtr.Count(), 1 );

	diffObjPtr = dummyPtr;
	ASSERT_EQ( diffObjPtr.Count(), 2 );
	ASSERT_EQ( diffObjPtr->Number, 3 );
}

TEST( SharedPtrFixture, SharedPtr_NullTest )
{
	SharedPtr<int> nullPtr;
	{
		SharedPtr<int> nullPtr2( nullPtr );
	}
	ASSERT_FALSE( nullPtr );

	ASSERT_TRUE( nullPtr.Get() == NULL );
	nullPtr.Reset( new Int32(24) );
	ASSERT_EQ( *nullPtr, 24 );
}

TEST( SharedPtrFixture, SharedPtrOstreamTest )
{
	SharedPtr<int> intPtr( new int );
	*intPtr = 10;
	std::ostringstream output;
	output << intPtr;
	ASSERT_EQ( output.str(), "10" );
}


TEST( SharedPtrFixture, SharedPtr_InheritedClassTest )
{
	// Base -> Inherited
	{
		SharedPtr<DummyClass> basePtr( new InheritedDummy() );
		SharedPtr<DummyClass> dummyPtr;

		ASSERT_EQ( basePtr.Count(), 1 );
		dummyPtr = basePtr;
		ASSERT_EQ( basePtr.Count(), 2 );
		ASSERT_EQ( dummyPtr.Count(), 2 );
		dummyPtr.Reset( basePtr );

		dummyPtr.Reset( new InheritedDummy() );
		ASSERT_EQ( dummyPtr.Count(), 1 );
		ASSERT_EQ( basePtr.Count(), 1 );
		dummyPtr->Number	= 2;
		basePtr->Number		= 3;
		ASSERT_EQ( dummyPtr->Number, 2 );
		ASSERT_EQ( basePtr->Number, 3 );

		SharedPtr<InheritedDummy> inPtr( new InheritedDummy() );
		basePtr.Reset( inPtr );
		ASSERT_EQ( basePtr.Count(), 2 );
		ASSERT_EQ( inPtr.Count(), 2 );
	}

	// Inherited -> Base
	{
		SharedPtr<InheritedDummy> inhPtr( new InheritedDummy() );
		ASSERT_EQ( inhPtr.Count(), 1 );
		inhPtr->Number = 50;
		{
			SharedPtr<DummyClass> basePtr( inhPtr );
			ASSERT_EQ( basePtr->Number, 50 );
			ASSERT_EQ( basePtr.Count(), 2 );
			ASSERT_EQ( inhPtr.Count(), 2 );
		}
	}
}