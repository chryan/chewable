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
 * @file Vector2.cpp
 * @brief 2D vector utility class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Math/Vector2.h"

using namespace cbl;

// 32-bit float normalise function.
template<>
void Vector2<Float32>::Normalise( void )
{
	Float32 len = GetLength();
	if( len > FLT_EPSILON ) {
		X /= len;
		Y /= len;
	}
}

// 32-bit float get normalised function.
template<>
const typename Vector2<Float32> Vector2<Float32>::GetNormalised( void ) const
{
	Float32 len = GetLength();
	// Return value optimisation
	return len <= FLT_EPSILON ? Vector2::ZERO : Vector2( X / len, Y / len );
}

/***** Vector2d definitions *****/

// 64-bit float normalise function.
template<>
void Vector2<Float64>::Normalise( void )
{
	Float64 len = GetLength();
	if( len > DBL_EPSILON ) {
		X /= len;
		Y /= len;
	}
}

// 64-bit float get normalised function.
template<>
const typename Vector2<Float64> Vector2<Float64>::GetNormalised( void ) const
{
	Float64 len = Float64( GetLength() );
	// Return value optimisation
	return len <= DBL_EPSILON ? Vector2::ZERO : Vector2( X / len, Y / len );
}
