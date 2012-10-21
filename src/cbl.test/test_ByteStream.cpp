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
 * @file test_ByteStream.cpp
 * @brief Unit testing for the integral type byte conversion class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/ByteStream.h>
#include <cbl/Debug/Assert.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( ByteStreamFixture, ByteStream_Test )
{
	Uint16	uint16Val	= 15;
	Uint32	uint32Val	= 24125;
	Real	realVal		= 10.0f;

	Uint16	uint16Val_o	= 0;
	Uint32	uint32Val_o	= 0;
	Real	realVal_o	= 0.0f;

	ByteStream stream;
	stream << uint16Val << realVal << uint32Val;

	ByteStream copied = stream;
	stream = stream; // Test self assignment.
	ASSERT_TRUE( strcmp( stream.GetBytes(), copied.GetBytes() ) == 0 );

	stream >> uint16Val_o >> realVal_o >> uint32Val_o;

	ASSERT_EQ( uint16Val, uint16Val_o );
	ASSERT_EQ( realVal, realVal_o );
	ASSERT_EQ( uint32Val, uint32Val_o );

	Uchar charVal = 1,
		charVal_o = 0;

	for( int i = 0; i < 100000; ++i )
	{
		++charVal;
		++uint16Val;
		realVal += 2.2f;
		++uint32Val;

		stream << charVal;
		stream >> charVal_o;

		stream << uint16Val;
		stream >> uint16Val_o;

		stream << realVal;
		stream >> realVal_o;

		stream << uint32Val;
		stream >> uint32Val_o;

		ASSERT_EQ( uint16Val, uint16Val_o );
		ASSERT_EQ( realVal, realVal_o );
		ASSERT_EQ( uint32Val, uint32Val_o );
	}
}

TEST( ByteStreamFixture, ByteStream_CompressionTest )
{
	Char buffer1[4096] = { 0 };
	Char buffer2[20] = { 0 };
	Char outBuffer[50] = { 0 };

	memset( buffer1, 1, 4096 );
	memset( buffer2, 2, 20 );
	memset( outBuffer, 0, 50 );

	ByteStream stream( buffer1, 4096 );
	stream.Read( outBuffer, 50 );
	ASSERT_EQ( stream.GetBytes()[0], 1 );

	ASSERT_EQ( stream.GetSize(), 4046 );
	stream.Write( buffer2, 20 );

	ASSERT_EQ( stream.GetSize(), 4066 );
	ASSERT_EQ( stream.GetBytes()[4045], 1 );
	ASSERT_EQ( stream.GetBytes()[4046], 2 );
	ASSERT_EQ( stream.GetBytes()[4047], 2 );

	ASSERT_EQ( stream.Find( 3 ), -1 );
	ASSERT_EQ( stream.Find( 1 ), 0 );
	ASSERT_EQ( stream.Find( 2 ), 4046 );
}

TEST( ByteStreamFixture, ByteStream_StringTest )
{
	const Char* outstr = "Testing123";
	String read;

	ByteStream bs;
	bs << outstr;
	bs >> read;

	ASSERT_STREQ( outstr, read.c_str() );
	ASSERT_EQ( read.length(), ::strlen( outstr ) );
}
