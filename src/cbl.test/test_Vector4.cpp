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
 * @file test_Vector4.cpp
 * @brief Unit testing for 3D Vector class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Math/Vector4.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( Vector4fTest, Vector4f_Operations )
{
	const Real tolerance = 0.00001f;

	// Assert ZERO values.
	ASSERT_EQ( Vector4f::ZERO.X, 0.0f );
	ASSERT_EQ( Vector4f::ZERO.Y, 0.0f );
	ASSERT_EQ( Vector4f::ZERO.Z, 0.0f );
	ASSERT_EQ( Vector4f::ZERO.W, 0.0f );

	Vector4f vecTest( 3.0f, 4.0f, 5.0f, 6.0f );
	
	ASSERT_EQ( vecTest.X, vecTest[0] );
	ASSERT_EQ( vecTest.Y, vecTest[1] );
	ASSERT_EQ( vecTest.Z, vecTest[2] );
	ASSERT_EQ( vecTest.W, vecTest[3] );
	
	// Dot product test.
	Vector4f dotProd( 25.0f, 10.0f, 4.76f, 9.513f );
	Vector4f dotProd2( 1.0f, 13.5f, 6.13f, 3.21f );

	ASSERT_NEAR( dotProd.GetDotProduct( dotProd2 ), 25.0f + 135.0f + 4.76f * 6.13f + 9.513f * 3.21f, tolerance );

	// Vector operations test.
	Vector4f vec1( 3.0f, 12.5f, 8.12f, 1.5f );
	Vector4f vec2( 5.76f, 1.15f, 4.79f, 0.19f );
	Vector4f compTest( vec1 );

	ASSERT_TRUE( vec1 == compTest );
	ASSERT_TRUE( vec2 != compTest );

	Vector4f addResult = vec1 + vec2;
	ASSERT_NEAR( addResult.X, 8.76f, tolerance );
	ASSERT_NEAR( addResult.Y, 13.65f, tolerance );
	ASSERT_NEAR( addResult.Z, 12.91f, tolerance );
	ASSERT_NEAR( addResult.W, 1.69f, tolerance );

	Vector4f minusResult = vec1 - vec2;
	ASSERT_NEAR( minusResult.X, -2.76f, tolerance );
	ASSERT_NEAR( minusResult.Y, 11.35f, tolerance );
	ASSERT_NEAR( minusResult.Z, 3.33f, tolerance );
	ASSERT_NEAR( minusResult.W, 1.31f, tolerance );

	Vector4f scaleResult = vec1 * 2.5123f;
	ASSERT_NEAR( scaleResult.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.Y, 12.5f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.Z, 8.12f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.W, 1.5f * 2.5123f, tolerance );

	Vector4f divResult = vec1 / 0.9128f;
	ASSERT_NEAR( divResult.X, 3.0f / 0.9128f, tolerance );
	ASSERT_NEAR( divResult.Y, 12.5f / 0.9128f, tolerance );
	ASSERT_NEAR( divResult.Z, 8.12f / 0.9128f, tolerance );
	ASSERT_NEAR( divResult.W, 1.5f / 0.9128f, tolerance );
	
	Vector4f negativeResult = -vec1;
	ASSERT_NEAR( negativeResult.X, -3.0f, tolerance );
	ASSERT_NEAR( negativeResult.Y, -12.5f, tolerance );
	ASSERT_NEAR( negativeResult.Z, -8.12f, tolerance );
	ASSERT_NEAR( negativeResult.W, -1.5f, tolerance );

	vec1 += vec2;
	ASSERT_NEAR( vec1.X, 8.76f, tolerance );
	ASSERT_NEAR( vec1.Y, 13.65f, tolerance );
	ASSERT_NEAR( vec1.Z, 12.91f, tolerance );
	ASSERT_NEAR( vec1.W, 1.69f, tolerance );
	
	vec1 -= vec2;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f, tolerance );
	ASSERT_NEAR( vec1.W, 1.5f, tolerance );

	vec1 *= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.W, 1.5f * 2.5123f, tolerance );

	vec1 /= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f, tolerance );
	ASSERT_NEAR( vec1.W, 1.5f, tolerance );
	
	//! Swap test
	vec1.Swap( vec2 );
	ASSERT_TRUE( vec1.X == 5.76f && vec1.Y == 1.15f && vec1.Z == 4.79f && vec1.W == 0.19f );
	ASSERT_TRUE( vec2.X == 3.0f && vec2.Y == 12.5f && vec2.Z == 8.12f && vec2.W == 1.5f );
}