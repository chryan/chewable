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
 * @file test_Matrix4.cpp
 * @brief Unit testing for 4x4 matrix class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Math/Matrix4.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

float pi = 3.1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679f;

TEST( Matrix4, Construction )
{
	static const Real r[4][4] = {
		{ 1.0f, 0.0f, 1.0f, -1.0f },
		{ 1.0f, 1.0f, -1.0f, 0.0f },
		{ 0.0f, 1.0f, 1.0f, -1.0f },
		{ 0.0f, 0.0f, -1.0f, 1.0f }
	};
	Matrix4 m( r );

	ASSERT_TRUE( m[0][0] == 1.0f && m[0][1] == 0.0f && m[0][2] == 1.0f && m[0][3] == -1.0f );
	ASSERT_TRUE( m[1][0] == 1.0f && m[1][1] == 1.0f && m[1][2] == -1.0f && m[1][3] == 0.0f );
	ASSERT_TRUE( m[2][0] == 0.0f && m[2][1] == 1.0f && m[2][2] == 1.0f && m[2][3] == -1.0f );
	ASSERT_TRUE( m[3][0] == 0.0f && m[3][1] == 0.0f && m[3][2] == -1.0f && m[3][3] == 1.0f );
}

TEST( Matrix4, Indentity )
{
	Matrix4 identity = Matrix4::IDENTITY;
	for( size_t i = 0; i < 4; ++i ) {
		for( size_t j = 0; j < 4; ++j ) {
			if( i == j )
				ASSERT_TRUE( identity[i][j] == 1.0f );
			else
				ASSERT_TRUE( identity[i][j] == 0.0f );
		}
	}
}

TEST( Matrix4, Translation )
{
	Vector3f vec( 5.0f, 2.0f, 1.0f );
	vec = Matrix4::Translation( -1.5f, 0.75f, 0.13f ) * vec;
	ASSERT_NEAR( vec.X, 3.5f, FLT_EPSILON );
	ASSERT_NEAR( vec.Y, 2.75f, FLT_EPSILON );
	ASSERT_NEAR( vec.Z, 1.13f, FLT_EPSILON );
}

TEST( Matrix4, Scaling )
{
	Vector3f vec( 0.8f, 1.5f, -0.6f );
	vec = Matrix4::Scaling( 2.0f, 1.5f, 0.5f ) * vec;
	ASSERT_NEAR( vec.X, 1.6f, FLT_EPSILON );
	ASSERT_NEAR( vec.Y, 2.25f, FLT_EPSILON );
	ASSERT_NEAR( vec.Z, -0.3f, FLT_EPSILON );
}

TEST( Matrix4, Rotations )
{
	Vector3f rvec;

	// X-axis rotation
	rvec.Set( 0.0f, 5.0f, 0.0f );
	rvec = Matrix4::RotationX( pi ) * rvec;
	ASSERT_NEAR( rvec.Y, -5.0f, FLT_EPSILON );
	
	// Y-axis rotation
	rvec.Set( 0.0f, 0.0f, 3.0f );
	rvec = Matrix4::RotationY( pi ) * rvec;
	ASSERT_NEAR( rvec.Z, -3.0f, FLT_EPSILON );
	
	// Z-axis rotation
	rvec.Set( 2.0f, 0.0f, 0.0f );
	rvec = Matrix4::RotationZ( pi ) * rvec;
	ASSERT_NEAR( rvec.X, -2.0f, FLT_EPSILON );
	
	rvec.Set( 0.0f, 0.0f, 5.0f );
	Vector3f axis( 1.0f, 0.0f, 1.0f );
	rvec = Matrix4::Rotation( axis, pi ) * rvec;
	ASSERT_NEAR( rvec.X, 5.0f, 0.0001f );
	ASSERT_NEAR( rvec.Z, 0.0f, 0.0001f );
	rvec = Matrix4::Rotation( axis, -pi ) * rvec;
	ASSERT_NEAR( rvec.X, 0.0f, 0.0001f );
	ASSERT_NEAR( rvec.Z, 5.0f, 0.0001f );
}
