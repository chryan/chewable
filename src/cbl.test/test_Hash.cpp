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
 * @file test_Hash.cpp
 * @brief Unit testing for hash class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/Hash.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class HashFixture : public ::testing::Test
{
protected:

	void SetUp()
	{
		testHashName = "TestHashName";
		testHash = Hash( "TestHashName" );
	}

	String testHashName;
	Hash testHash;
};

TEST_F( HashFixture, Hash_GenerateHash )
{
	Hash newHash( testHashName.c_str() );
	Hash wrongHash( "Wrong hash!" );

	ASSERT_EQ( testHash.GetHash(), newHash.GetHash() );
	ASSERT_EQ( testHash.GetHash(), Hash::Generate( testHashName.c_str() ) );
	ASSERT_NE( testHash.GetHash(), wrongHash.GetHash() );
	ASSERT_NE( testHash.GetHash(), 0 );
}

TEST( HashFixtureNameTest, Hash_NameTest )
{
	for( size_t i = 0; i < 5; ++i ) {
		cbl::Ostringstream o;
		o << "TestString" << i;

		cbl::Hash hash = cbl::Hash(o.str().c_str());
		ASSERT_STREQ( hash.GetText().c_str(), o.str().c_str() );
	}
}