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
 * @file test_Vector2f.cpp
 * @brief Unit testing for 2D Vector class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Math/Vector2.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( Vector2fTest, Vector2f_Operations )
{
	const Real tolerance = 0.00001f;

	// Assert ZERO values.
	ASSERT_EQ( Vector2f::ZERO.X, 0.0f );
	ASSERT_EQ( Vector2f::ZERO.Y, 0.0f );

	// Assert UNIT_X values.
	ASSERT_EQ( Vector2f::UNIT_X.X, 1.0f );
	ASSERT_EQ( Vector2f::UNIT_X.Y, 0.0f );
	
	// Assert UNIT_Y values.
	ASSERT_EQ( Vector2f::UNIT_Y.X, 0.0f );
	ASSERT_EQ( Vector2f::UNIT_Y.Y, 1.0f );

	Vector2f vecTest( 3.0f, 4.0f );
	
	ASSERT_EQ( vecTest.X, vecTest[0] );
	ASSERT_EQ( vecTest.Y, vecTest[1] );

	// Length test.
	ASSERT_NEAR( vecTest.GetSquaredLength(), 25.0f, tolerance );
	ASSERT_NEAR( vecTest.GetLength(), 5.0f, tolerance );

	// Normalise test.
	ASSERT_NEAR( vecTest.GetNormalised().GetLength(), 1.0f, tolerance );
	
	vecTest.Normalise();
	ASSERT_NEAR( vecTest.GetLength(), 1.0f, tolerance );

	// Distance test.
	Vector2f dist1( 10.0f, 16.0f );
	Vector2f dist2( 13.0f, 12.0f );

	ASSERT_NEAR( dist1.GetSquaredDistance( dist2 ), 25.0f, tolerance );
	ASSERT_NEAR( dist1.GetDistance( dist2 ), 5.0f, tolerance );
	
	// Dot product test.
	Vector2f dotProd( 25.0f, 10.0f );
	Vector2f dotProd2( 1.0f, 13.5f );

	ASSERT_NEAR( dotProd.GetDotProduct( dotProd2 ), 25.0f + 135.0f, tolerance );
	
	// Cross product test.
	Vector2f crossProd( 15.0f, 12.0f );
	Vector2f crossProd2( 51.0f, 17.1f );

	ASSERT_NEAR( crossProd.GetCrossProduct( crossProd2 ), 15.0f * 17.1f - 12.0f * 51.0f, tolerance );

	// Conversion test.
	Vector2f convertf( 1.1f, 2.4f );
	Vector2i converti( 1, 2 );

	ASSERT_EQ( converti, Vector2i( convertf ) );

	// Vector operations test.
	Vector2f vec1( 3.0f, 12.5f );
	Vector2f vec2( 5.76f, 1.15f );
	Vector2f compTest( vec1 );

	ASSERT_TRUE( vec1 == compTest );
	ASSERT_TRUE( vec2 != compTest );

	Vector2f addResult = vec1 + vec2;
	ASSERT_NEAR( addResult.X, 8.76f, tolerance );
	ASSERT_NEAR( addResult.Y, 13.65f, tolerance );

	Vector2f minusResult = vec1 - vec2;
	ASSERT_NEAR( minusResult.X, -2.76f, tolerance );
	ASSERT_NEAR( minusResult.Y, 11.35f, tolerance );

	Vector2f scaleResult = vec1 * 2.5123f;
	ASSERT_NEAR( scaleResult.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( scaleResult.Y, 12.5f * 2.5123f, tolerance );

	Vector2f divResult = vec1 / 2.5123f;
	ASSERT_NEAR( divResult.X, 3.0f / 2.5123f, tolerance );
	ASSERT_NEAR( divResult.Y, 12.5f / 2.5123f, tolerance );
	
	Vector2f negativeResult = -vec1;
	ASSERT_NEAR( negativeResult.X, -3.0f, tolerance );
	ASSERT_NEAR( negativeResult.Y, -12.5f, tolerance );

	vec1 += vec2;
	ASSERT_NEAR( vec1.X, 8.76f, tolerance );
	ASSERT_NEAR( vec1.Y, 13.65f, tolerance );
	
	vec1 -= vec2;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );

	vec1 *= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f * 2.5123f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f * 2.5123f, tolerance );

	vec1 /= 2.5123f;
	ASSERT_NEAR( vec1.X, 3.0f, tolerance );
	ASSERT_NEAR( vec1.Y, 12.5f, tolerance );

	//! Swap test.
	vec1.Swap( vec2 );
	ASSERT_TRUE( vec1.X == 5.76f && vec1.Y == 1.15f );
	ASSERT_TRUE( vec2.X == 3.0f && vec2.Y == 12.5f );
}