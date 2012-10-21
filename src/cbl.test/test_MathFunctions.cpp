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
 * @file test_MathFunctions.cpp
 * @brief Unit testing for math functions.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Math/Functions.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( MathFunctions, Accuracy )
{
	Float64 val1		= 12.41;
	Float64 val2		= 8.79;
	Float64 tolerance	= 0.001;
	
	ASSERT_NEAR( Math::Sqrt<Float64>( val1 ), 3.522782990761707, tolerance );
	ASSERT_NEAR( Math::Sqrt<Float64>( val2 ), 2.964793416074719, tolerance );
	ASSERT_NEAR( Math::Ceil<Float64>( val1 ), 13.0, tolerance );
	ASSERT_NEAR( Math::Ceil<Float64>( val2 ), 9.0, tolerance );
	ASSERT_NEAR( Math::Floor<Float64>( val1 ), 12.0, tolerance );
	ASSERT_NEAR( Math::Floor<Float64>( val2 ), 8.0, tolerance );
	ASSERT_NEAR( Math::Min<Float64>( val1, val2 ), 8.79, tolerance );
	ASSERT_NEAR( Math::Max<Float64>( val1, val2 ), 12.41, tolerance );
	ASSERT_NEAR( Math::Round<Float64>( val1 ), 12.0, tolerance );
	ASSERT_NEAR( Math::Round<Float64>( val2 ), 9.0, tolerance );
	ASSERT_NEAR( Math::Power<Float64>( 2.0, 5 ), 32.0, tolerance );
	ASSERT_EQ( Math::GeometricSum<Int32>( 4, 3 ), 85 );
	ASSERT_EQ( Math::GeometricSum<Int32>( 4.0, 3.0f ), 85 );
	ASSERT_EQ( Math::GeometricSum<Int32>( 4.0f, 3.0 ), 85 );
	ASSERT_EQ( Math::GeometricSum<Int32>( 4, 3.0f ), 85 );
	ASSERT_EQ( Math::GeometricSum<Int32>( 4.0f, 3 ), 85 );
	ASSERT_EQ( Math::ClosestPower2<Uint32>( 5 ), 8 );
	ASSERT_EQ( Math::ClosestPower2<Uint32>( 19762 ), 32768 );
	ASSERT_EQ( Math::ClosestPower2<Uint32>( 7816523 ), 8388608 );
	
	ASSERT_NEAR( Math::Clamp<Float64>( val1, val2, 1.0 ), val2, tolerance );
	ASSERT_NEAR( Math::Clamp<Float64>( val1, val2, 1238.0 ), val1, tolerance );
	ASSERT_NEAR( Math::Clamp<Float64>( val1, val2, 9.01 ), 9.01, tolerance );
}
