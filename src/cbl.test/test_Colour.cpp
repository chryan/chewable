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
 * @file test_Colour.cpp
 * @brief Unit testing for the colour class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/Colour.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

TEST( ColourFixture, ColourUintToFloat_Test )
{
	cbl::Uint32 rgba = 0x256788A1;
	cbl::Uint8 r = 0x25;
	cbl::Uint8 g = 0x67;
	cbl::Uint8 b = 0x88;
	cbl::Uint8 a = 0xA1;

	Colour testColour( rgba );
	ASSERT_EQ( testColour.GetR(), r );
	ASSERT_EQ( testColour.GetG(), g );
	ASSERT_EQ( testColour.GetB(), b );
	ASSERT_EQ( testColour.GetA(), a );

	ASSERT_EQ( testColour.GetR(), 37 );
	ASSERT_EQ( testColour.GetG(), 103 );
	ASSERT_EQ( testColour.GetB(), 136 );
	ASSERT_EQ( testColour.GetA(), 161 );

	ASSERT_NEAR( testColour.R, 37.0f / 255.0f, 0.0001f );
	ASSERT_NEAR( testColour.G, 103.0f / 255.0f, 0.0001f );
	ASSERT_NEAR( testColour.B, 136.0f / 255.0f, 0.0001f );
	ASSERT_NEAR( testColour.A, 161.0f / 255.0f, 0.0001f );
}

TEST( ColourFixture, ColourFloatToUint_Test )
{
	Colour testColour( 0.25f, 0.5f, 0.75f, 0.8f );
	
	ASSERT_EQ( testColour.R, 0.25f );
	ASSERT_EQ( testColour.G, 0.5f );
	ASSERT_EQ( testColour.B, 0.75f );
	ASSERT_EQ( testColour.A, 0.8f );

	ASSERT_EQ( testColour[0], 0.25f );
	ASSERT_EQ( testColour[1], 0.5f );
	ASSERT_EQ( testColour[2], 0.75f );
	ASSERT_EQ( testColour[3], 0.8f );

	ASSERT_EQ( testColour.GetR(), 63 );
	ASSERT_EQ( testColour.GetG(), 127 );
	ASSERT_EQ( testColour.GetB(), 191 );
	ASSERT_EQ( testColour.GetA(), 204 );
	
	ASSERT_EQ( testColour.GetRGBA(), 0x3F7FBFCC );
}
