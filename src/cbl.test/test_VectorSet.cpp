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
 * @file test_VectorSet.cpp
 * @brief Unit testing for the fastmap.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Util/VectorSet.h>
#include <cbl/Util/Hash.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

typedef VectorSet<Int32>	VectorSetTest;

//! Event test fixture.
class VectorSetTestFixture : public ::testing::Test
{
protected:
	VectorSetTestFixture()
	: mVectorSetTest(1024) {
	}

	void SetUp()
	{
		for( Int32 i = 0; i < TestSize; ++i ) {
			mVectorSetTest.insert( i );
		}
	}

protected:
	VectorSetTest		mVectorSetTest;
	static const cbl::Uint32 TestSize = 1000;
};

TEST_F( VectorSetTestFixture, InsertTest )
{
	ASSERT_EQ( mVectorSetTest.size(), TestSize );
}

TEST_F( VectorSetTestFixture, EraseTest )
{
	cbl::Uint32 size = mVectorSetTest.size() - 100;
	for( Int32 i = 0; i < 100; ++i ) {
		mVectorSetTest.erase( i );
	}

	ASSERT_EQ( mVectorSetTest.size(), size );

	size -= 100;
	for( Uint32 i = 0; i < 100; ++i ) {
		mVectorSetTest.erase( mVectorSetTest.begin() );
	}

	ASSERT_EQ( mVectorSetTest.size(), size );
}

TEST_F( VectorSetTestFixture, ModificationTest )
{
	for( VectorSetTest::iterator it = mVectorSetTest.begin(); it != mVectorSetTest.end(); ++it ) {
		*it = 0;
	}
	for( VectorSetTest::iterator it = mVectorSetTest.begin(); it != mVectorSetTest.end(); ++it ) {
		ASSERT_EQ( *it, 0 );
	}

	for( Int32 i = 0; i < cbl::Int32( mVectorSetTest.size() ); ++i ) {
		mVectorSetTest[i] = i;
	}
	for( Int32 i = 0; i < cbl::Int32( mVectorSetTest.size() ); ++i ) {
		ASSERT_EQ( mVectorSetTest[i], i );
	}
}

TEST_F( VectorSetTestFixture, FindTest )
{
	for( Int32 i = 0; i < cbl::Int32( mVectorSetTest.size() ); ++i ) {
		VectorSetTest::iterator findit = mVectorSetTest.find( i );
		ASSERT_TRUE( findit != mVectorSetTest.end() );
		ASSERT_EQ( mVectorSetTest[i], i );
	}
}

TEST_F( VectorSetTestFixture, UniquenessTest )
{
	for( Int32 i = 0; i < cbl::Int32( mVectorSetTest.size() ); ++i ) {
		bool test = mVectorSetTest.insert( i );
		ASSERT_FALSE( test );
	}

	ASSERT_EQ( mVectorSetTest.size(), TestSize );
}

TEST_F( VectorSetTestFixture, SortedTest )
{
	cbl::Int32 v = -1;
	for( VectorSetTest::iterator it = mVectorSetTest.begin(); it != mVectorSetTest.end(); ++it ) {
		ASSERT_TRUE( v < *it );
		v = *it;
	}

	v = -1;
	for( cbl::Uint32 i = 0; i < mVectorSetTest.size(); ++i ) {
		ASSERT_TRUE( v < mVectorSetTest[i] );
		v = mVectorSetTest[i];
	}
}
