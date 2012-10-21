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
 * @file test_Vector3.cpp
 * @brief Unit testing for 3D Vector class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Math/Vector3.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( Vector3fTest, Vector3f_Operations )
{
	const Real tolerance = 0.00001f;

	// Assert ZERO values.
	ASSERT_EQ( Vector3f::ZERO.X, 0.0f );
	ASSERT_EQ( Vector3f::ZERO.Y, 0.0f );
	ASSERT_EQ( Vector3f::ZERO.Z, 0.0f );

	// Assert UNIT_X values.
	ASSERT_EQ( Vector3f::UNIT_X.X, 1.0f );
	ASSERT_EQ( Vector3f::UNIT_X.Y, 0.0f );
	ASSERT_EQ( Vector3f::UNIT_X.Z, 0.0f );
	
	// Assert UNIT_Y values.
	ASSERT_EQ( Vector3f::UNIT_Y.X, 0.0f );
	ASSERT_EQ( Vector3f::UNIT_Y.Y, 1.0f );
	ASSERT_EQ( Vector3f::UNIT_Y.Z, 0.0f );
	
	// Assert UNIT_Z values.
	ASSERT_EQ( Vector3f::UNIT_Z.X, 0.0f );
	ASSERT_EQ( Vector3f::UNIT_Z.Y, 0.0f );
	ASSERT_EQ( Vector3f::UNIT_Z.Z, 1.0f );

	Vector3f vecTest( 3.0f, 4.0f, 5.0f );
	
	ASSERT_EQ( vecTest.X, vecTest[0] );
	ASSERT_EQ( vecTest.Y, vecTest[1] );
	ASSERT_EQ( vecTest.Z, vecTest[2] );

	// Length test.
	ASSERT_NEAR( vecTest.GetSquaredLength(), 50.0f, tolerance );
	ASSERT_NEAR( vecTest.GetLength(), sqrt( 50.0f ), tolerance );

	// Normalise test.
	ASSERT_NEAR( vecTest.GetNormalised().GetLength(), 1.0f, tolerance );
	
	vecTest.Normalise();
	ASSERT_NEAR( vecTest.GetLength(), 1.0f, tolerance );

	// Distance test.
	Vector3f dist1( 10.0f, 16.0f, 13.0f );
	Vector3f dist2( 13.0f, 12.0f, 8.0f );

	ASSERT_NEAR( dist1.GetSquaredDistance( dist2 ), 50.0f, tolerance );
	ASSERT_NEAR( dist1.GetDistance( dist2 ), sqrt( 50.0f ), tolerance );
	
	// Dot product test.
	Vector3f dotProd( 25.0f, 10.0f, 4.76f );
	Vector3f dotProd2( 1.0f, 13.5f, 6.13f );

	ASSERT_NEAR( dotProd.GetDotProduct( dotProd2 ), 25.0f + 135.0f + 4.76f * 6.13f, tolerance );
	
	// Cross product test.
	Vector3f crossProd( 15.0f, 12.0f, 5.17f );
	Vector3f crossProd2( 51.0f, 17.1f, 9.12f );
	Vector3f crossResult = crossProd.GetCrossProduct( crossProd2 );

	ASSERT_NEAR( crossResult.X, 12.0f * 9.12f - 5.17f * 17.1f, tolerance );
	ASSERT_NEAR( crossResult.Y, 5.17f * 51.0f - 15.0f * 9.12f, tolerance );
	ASSERT_NEAR( crossResult.Z, 15.0f * 17.1f - 12.0f * 51.0f, tolerance );

	// Vector operations test.
	Vector3f vec1( 3.0f, 12.5f, 8.12f );
	Vector3f vec2( 5.76f, 1.15f, 4.79f );
	Vector3f compTest( vec1 );

	ASSERT_TRUE( vec1 == compTest );
	ASSERT_TRUE( vec2 != compTest );

	Vector3f addResult = vec1 + vec2;
	ASSERT_NEAR( addResult.X, 8.76f, tolerance );
	ASSERT_NEAR( addResult.Y, 13.65f, tolerance );
	ASSERT_NEAR( addResult.Z, 12.91f, tolerance );

	Vector3f minusResult = vec1 - vec2;
	ASSERT_NEAR( minusResult.X, -2.76f, tolerance );
	ASSERT_NEAR( minusResult.Y, 11.35f, tolerance );
	ASSERT_NEAR( minusResult.Z, 3.33f, tolerance );

	Vector3f scaleResult = vec1 * 2.5123f;
	ASSERT_NEAR( scaleResult.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.Y, 12.5f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.Z, 8.12f * 2.5123f, tolerance );

	Vector3f divResult = vec1 / 0.9128f;
	ASSERT_NEAR( divResult.X, 3.0f / 0.9128f, tolerance );
	ASSERT_NEAR( divResult.Y, 12.5f / 0.9128f, tolerance );
	ASSERT_NEAR( divResult.Z, 8.12f / 0.9128f, tolerance );
	
	Vector3f negativeResult = -vec1;
	ASSERT_NEAR( negativeResult.X, -3.0f, tolerance );
	ASSERT_NEAR( negativeResult.Y, -12.5f, tolerance );
	ASSERT_NEAR( negativeResult.Z, -8.12f, tolerance );

	vec1 += vec2;
	ASSERT_NEAR( vec1.X, 8.76f, tolerance );
	ASSERT_NEAR( vec1.Y, 13.65f, tolerance );
	ASSERT_NEAR( vec1.Z, 12.91f, tolerance );
	
	vec1 -= vec2;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f, tolerance );

	vec1 *= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f * 2.5123f, tolerance );

	vec1 /= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );
	ASSERT_NEAR( vec1.Z, 8.12f, tolerance );

	//! Swap test.
	vec1.Swap( vec2 );
	ASSERT_TRUE( vec1.X == 5.76f && vec1.Y == 1.15f && vec1.Z == 4.79f );
	ASSERT_TRUE( vec2.X == 3.0f && vec2.Y == 12.5f && vec2.Z == 8.12f);
}