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
 * @file Vector2.h
 * @brief 2D vector utility class.
 */

#ifndef __CBL_VECTOR2_H_
#define __CBL_VECTOR2_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! @brief 2D vector class.
	//! @tparam	T	Vector data type.
	template< typename T >
	class Vector2
	{
	/***** Static Constants *****/
	public:
		static const Vector2	ZERO;		//!< Zero vector.
		static const Vector2	ONE;		//!< (1,1) vector.
		static const Vector2	N_ONE;		//!< (-1,-1) vector.
		static const Vector2	UNIT_X;		//!< X unit vector.
		static const Vector2	UNIT_Y;		//!< Y unit vector.
		static const Vector2	UNIT_NX;	//!< -X unit vector.
		static const Vector2	UNIT_NY;	//!< -Y unit vector.
		
	/***** Public Members *****/
	public:
		T			X;	//!< Vector2 X value.
		T			Y;	//!< Vector2 Y value.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		Vector2();
		//! Explicit constructor.
		//! @param	t		Fills X and Y with t.
		explicit Vector2( const T t );
		//! Contructor.
		//! @param	coords	Coordinates in {X, Y} format.
		explicit Vector2( const T coords[2] );
		//! Copy contructor.
		//! @param	rhs		Right-hand side.
		Vector2( const Vector2 & rhs );
		//! Contructor.
		//! @param	x		X value.
		//! @param	y		Y value.
		Vector2( T x, T y );
		//! Const index operator.
		//! @param	index	0 for X, 1 for Y.
		const T operator [] ( const size_t index ) const;
		//! Index operator.
		//! @param	index	0 for X, 1 for Y.
		T & operator [] ( const size_t index );
		//! Addition operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector2 containing added  values.
		const Vector2 operator + ( const Vector2 & rhs ) const;
		//! Subtraction operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector2 containing subtracted values.
		const Vector2 operator - ( const Vector2 & rhs ) const;
		//! Unary negation operator.
		//! @return			New Vector2 containing negative values.
		const Vector2 operator - ( void ) const;
		//! Product (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector2 containing scaled values.
		const Vector2 operator * ( const Real scale ) const;
		//! Division (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector2 containing scaled values.
		const Vector2 operator / ( const Real scale ) const;
		//! Product operator.
		//! Multiplies each corresponding value { X*X, Y*Y }.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector2.
		const Vector2 operator * ( const Vector2 & rhs ) const;
		//! Assignment operator.
		//! @param	rhs		Right-hand side.
		Vector2 & operator = ( const Vector2 & rhs );
		//! Increment assignment operator.
		//! @param	rhs		Right-hand side.
		Vector2 & operator += ( const Vector2 & rhs );
		//! Decrement assignment operator.
		//! @param	rhs		Right-hand side.
		Vector2 & operator -= ( const Vector2 & rhs );
		//! Product (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector2 & operator *= ( const Real scale );
		//! Division (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector2 & operator /= ( const Real scale );
		//! Equality operator.
		//! Compares if corresponding values are equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator == ( const Vector2 & rhs ) const;
		//! Inequality operator.
		//! Compares if corresponding values are not equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator != ( const Vector2 & rhs ) const;
		//! Swap values with another vector.
		//! @param	rhs		Other vector.
		void Swap( Vector2 & rhs );
		//! Set X and Y values.
		//! @param	x		X value.
		//! @param	y		Y value.
		void Set( T x, T y );
		//! Normalise vector ( Length() == 1.0f )
		//! NOTE: Only defined for floating point type vectors.
		void Normalise( void );
		//! Get a new normalised vector.
		//! NOTE: Only defined for floating point type vectors.
		const Vector2 GetNormalised( void ) const;
		//! Get vector length.
		//! @return			Vector length.
		const Real GetLength( void ) const;
		//! Get vector squared length.
		//! @return			Vector squared length.
		const Real GetSquaredLength( void ) const;
		//! Get distance between two vectors.
		//! @return			Distance.
		const Real GetDistance( const Vector2 & rhs ) const;
		//! Get sqaured distance between two vectors.
		//! @return			Squared distance.
		const Real GetSquaredDistance( const Vector2 & rhs ) const;
		//! Get dot product of two vectors.
		//! @return			Dot product.
		const Real GetDotProduct( const Vector2 & rhs ) const;
		//! Get cross product of two vectors.
		//! @return			Cross product.
		const Real GetCrossProduct( const Vector2 & rhs ) const;
		//! Vector3 type conversion operator.
		//! Used to convert vectors to different internal types.
		template< typename O >
		operator Vector2<O> () const;
	};

	//! Vector2 float type.
	typedef Vector2<Float32>		Vector2f;
	//! Vector2 double type.
	typedef Vector2<Float64>		Vector2d;
	//! Vector2 real type.
	typedef Vector2<Real>			Vector2r;
	//! Vector2 integer type.
	typedef Vector2<Int32>			Vector2i;

	/***** Helper Functions *****/
	//! Formats and prints the vector values to an output stream.
	//! @param	stream		Output stream.
	//! @param	vector		Vector to print.
	//! @return				Output stream reference.
	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector2<T> & vector );
}

/***** Template specialisation methods *****/
template<>
CBL_API void cbl::Vector2<cbl::Float32>::Normalise( void );

template<>
CBL_API const cbl::Vector2<cbl::Float32> cbl::Vector2<cbl::Float32>::GetNormalised( void ) const;

template<>
CBL_API void cbl::Vector2<cbl::Float64>::Normalise( void );

template<>
CBL_API const cbl::Vector2<cbl::Float64> cbl::Vector2<cbl::Float64>::GetNormalised( void ) const;

#include "Vector2.inl"

CBL_TYPE( Vector2i, Vector2i );
CBL_TYPE( Vector2f, Vector2f );
CBL_TYPE( Vector2d, Vector2d );

#endif // __CBL_VECTOR2_H_
