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
 * @file Colour.h
 * @brief Colour object.
 */

#ifndef __CBL_COLOUR_H_
#define __CBL_COLOUR_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Functions.h"

namespace cbl
{
	//! Colour structure.
	class CBL_API Colour
	{
	/***** Static Public Methods *****/
	public:
		static const Colour WHITE;
		static const Colour BLACK;
		static const Colour RED;
		static const Colour GREEN;
		static const Colour BLUE;
		static const Colour YELLOW;
		static const Colour MAGENTA;
		static const Colour TEAL;

	/***** Public Members *****/
	public:
		cbl::Real	R;	//!< Red.
		cbl::Real	G;	//!< Green.
		cbl::Real	B;	//!< Blue.
		cbl::Real	A;	//!< Alpha.
		
	/***** Properties *****/
	public:
		cbl::Uint32 GetRGBA( void ) const;
		cbl::Uint8 GetR( void ) const;
		cbl::Uint8 GetG( void ) const;
		cbl::Uint8 GetB( void ) const;
		cbl::Uint8 GetA( void ) const;

	/***** Public Methods *****/
	public:
		explicit Colour( cbl::Real t = 1.0f );
		explicit Colour( cbl::Real r, cbl::Real g, cbl::Real b, cbl::Real a = 1.0f );
		explicit Colour( cbl::Uint32 rgba );
		~Colour();
		//! Access values by the index operator.
		cbl::Real & operator [] ( const size_t index );
		//! Access values by the index operator.
		const cbl::Real operator [] ( const size_t index ) const;
		//! Check if colours are equal.
		const bool operator == ( const Colour & rhs ) const;
		//! Multiply colours.
		const Colour operator * ( const Colour & rhs ) const;
		//! Multiply colours.
		Colour & operator *= ( const Colour & rhs );
		//! Scale colours.
		const Colour operator * ( cbl::Real scale ) const;
		//! Scale colours.
		Colour& operator *= ( cbl::Real scale );
		//! Add colours.
		const Colour operator + ( const Colour& rhs ) const;
		//! Add colours.
		Colour& operator += ( const Colour& rhs );
		//! Subtract colours.
		const Colour operator - ( const Colour& rhs ) const;
		//! Subtract colours.
		Colour& operator -= ( const Colour& rhs );
	};

	/***** Inline Methods *****/
	inline cbl::Uint32 Colour::GetRGBA( void ) const { return ( GetR() << 24 ) + ( GetG() << 16 ) + ( GetB() << 8 ) + GetA(); }
	inline cbl::Uint8 Colour::GetR( void ) const { return R < 0.0f ? 0 : R > 1.0f ? 255 : cbl::Uint8( R * 255.0f ); }
	inline cbl::Uint8 Colour::GetG( void ) const { return G < 0.0f ? 0 : G > 1.0f ? 255 : cbl::Uint8( G * 255.0f ); }
	inline cbl::Uint8 Colour::GetB( void ) const { return B < 0.0f ? 0 : B > 1.0f ? 255 : cbl::Uint8( B * 255.0f ); }
	inline cbl::Uint8 Colour::GetA( void ) const { return A < 0.0f ? 0 : A > 1.0f ? 255 : cbl::Uint8( A * 255.0f ); }
	
	inline cbl::Real & Colour::operator [] ( const size_t index ) { CBL_ASSERT( index < 4, "Accessing beyond index bounds." ); return *( &R + index ); }
	inline const cbl::Real Colour::operator [] ( const size_t index ) const { CBL_ASSERT( index < 4, "Accessing beyond index bounds." ); return *( &R + index ); }
	inline const bool Colour::operator == ( const Colour & rhs ) const { return ( rhs.R == R ) && ( rhs.G == G ) && ( rhs.B == B ) && ( rhs.A == A ); }
	inline const Colour Colour::operator * ( const Colour & rhs ) const { return Colour( R * rhs.R, G * rhs.G, B * rhs.B, A * rhs.A ); } 
	inline Colour & Colour::operator *= ( const Colour & rhs ) { R *= rhs.R; G *= rhs.G; B *= rhs.B; A *= rhs.A; return *this; }
	inline const Colour Colour::operator * ( cbl::Real scale ) const { return Colour( R * scale, G * scale, B * scale, A * scale ); } 
	inline Colour& Colour::operator *= ( cbl::Real scale ) { R *= scale; G *= scale; B *= scale; A *= scale; return *this; }
	inline const Colour Colour::operator + ( const Colour& rhs ) const { return Colour( R + rhs.R, G + rhs.G, B + rhs.B, A + rhs.A ); } 
	inline Colour& Colour::operator += ( const Colour& rhs ) { R += rhs.R; G += rhs.G; B += rhs.B; A += rhs.A; return *this; }
	inline const Colour Colour::operator - ( const Colour& rhs ) const { return Colour( R + rhs.R, G + rhs.G, B + rhs.B, A + rhs.A ); } 
	inline Colour& Colour::operator -= ( const Colour& rhs ) { R -= rhs.R; G -= rhs.G; B -= rhs.B; A -= rhs.A; return *this; }
}

CBL_TYPE( cbl::Colour, Colour );

#endif // __CBL_COLOUR_H_
