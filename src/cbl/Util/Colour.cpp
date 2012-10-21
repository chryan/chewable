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
 * @file Colour.cpp
 * @brief Colour object.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/util/Colour.h"

using namespace cbl;

const Colour Colour::WHITE		= Colour( 1.0f );
const Colour Colour::BLACK		= Colour( 0.0f, 0.0f, 0.0f, 1.0f );
const Colour Colour::RED		= Colour( 1.0f, 0.0f, 0.0f, 1.0f );
const Colour Colour::GREEN		= Colour( 0.0f, 1.0f, 0.0f, 1.0f );
const Colour Colour::BLUE		= Colour( 0.0f, 0.0f, 1.0f, 1.0f );
const Colour Colour::YELLOW		= Colour( 1.0f, 1.0f, 0.0f, 1.0f );
const Colour Colour::MAGENTA	= Colour( 1.0f, 0.0f, 1.0f, 1.0f );
const Colour Colour::TEAL		= Colour( 0.0f, 1.0f, 1.0f, 1.0f );

Colour::Colour( cbl::Real t )
: R( t )
, G( t )
, B( t )
, A( t )
{
}

Colour::Colour( cbl::Real r, cbl::Real g, cbl::Real b, cbl::Real a )
: R( r )
, G( g )
, B( b )
, A( a )
{
}

Colour::Colour( cbl::Uint32 rgba )
: R( ( ( rgba & 0xFF000000 ) >> 24 ) / 255.0f )
, G( ( ( rgba & 0x00FF0000 ) >> 16 ) / 255.0f )
, B( ( ( rgba & 0x0000FF00 ) >> 8 ) / 255.0f )
, A( ( rgba & 0x000000FF ) / 255.0f )
{
}

Colour::~Colour()
{
}