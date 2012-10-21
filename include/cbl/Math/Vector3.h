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
 * @file Vector3.h
 * @brief 3D vector utility class.
 */

#ifndef __CBL_VECTOR3_H_
#define __CBL_VECTOR3_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! @brief 3D vector class.
	template< typename T >
	class Vector3
	{
	/***** Static Public Members *****/
	public:
		static const Vector3	ZERO;		//!< Zero vector.
		static const Vector3	ONE;		//!< (1,1,1) vector.
		static const Vector3	N_ONE;		//!< (-1,-1,-1) vector.
		static const Vector3	UNIT_X;		//!< X unit vector.
		static const Vector3	UNIT_Y;		//!< Y unit vector.
		static const Vector3	UNIT_Z;		//!< Z unit vector.
		static const Vector3	UNIT_NX;	//!< -X unit vector.
		static const Vector3	UNIT_NY;	//!< -Y unit vector.
		static const Vector3	UNIT_NZ;	//!< -Z unit vector.

	/***** Public Members *****/
	public:
		T			X;	//!< Vector3 X value.
		T			Y;	//!< Vector3 Y value.
		T			Z;	//!< Vector3 Z value.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		Vector3();
		//! Explicit constructor.
		//! @param	t		Fills X, Y and Z with t.
		explicit Vector3( const T t );
		//! Contructor.
		//! @param	coords	Coordinates in {X, Y, Z} format.
		explicit Vector3( const T coords[3] );
		//! Copy contructor.
		//! @param	rhs		Right-hand side.
		Vector3( const Vector3 & rhs );
		//! Contructor.
		//! @param	x		X value.
		//! @param	y		Y value.
		//! @param	z		Z value.
		Vector3( const T x, const T y, const T z );
		//! Const index operator.
		//! @param	index	0 for X, 1 for Y, 2 for Z.
		const T operator [] ( const size_t index ) const;
		//! Index operator.
		//! @param	index	0 for X, 1 for Y, 2 for Z.
		T & operator [] ( const size_t index );
		//! Addition operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector3 containing added values.
		const Vector3 operator + ( const Vector3 & rhs ) const;
		//! Subtraction operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector3 containing subtracted values.
		const Vector3 operator - ( const Vector3 & rhs ) const;
		//! Unary negation operator.
		//! @return			New Vector3 containing negative values.
		const Vector3 operator - ( void ) const;
		//! Product (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector3 containing scaled values.
		const Vector3 operator * ( const Real scale ) const;
		//! Division (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector2 containing scaled values.
		const Vector3 operator / ( const Real Scale ) const;
		//! Product operator.
		//! Multiplies each corresponding value { X*X, Y*Y, Z*Z }.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector2.
		const Vector3 operator * ( const Vector3 & rhs ) const;
		//! Assignment operator.
		//! @param	rhs		Right-hand side.
		Vector3 & operator = ( const Vector3 & rhs );
		//! Increment assignment operator.
		//! @param	rhs		Right-hand side.
		Vector3 & operator += ( const Vector3 & rhs );
		//! Decrement assignment operator.
		//! @param	rhs		Right-hand side.
		Vector3 & operator -= ( const Vector3 & rhs );
		//! Product (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector3 & operator *= ( const Real scale );
		//! Division (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector3 & operator /= ( const Real scale );
		//! Equality operator.
		//! Compares if corresponding values are equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator == ( const Vector3 & rhs ) const;
		//! Inequality operator.
		//! Compares if corresponding values are not equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator != ( const Vector3 & rhs ) const;
		//! Swap values with another vector.
		//! @param	rhs		Other vector.
		void Swap( Vector3 & rhs );
		//! Set X and Y values.
		//! @param	x		X value.
		//! @param	y		Y value.
		//! @param	z		Z value.
		void Set( const T x, const T y, const T z );
		//! Normalise vector ( Length() == 1.0f )
		//! NOTE: Only defined for floating point type vectors.
		void Normalise( void );
		//! Get normalised vector from this one.
		//! NOTE: Only defined for floating point type vectors.
		const Vector3 GetNormalised( void ) const;
		//! Get vector length.
		//! @return			Vector length.
		const Real GetLength( void ) const;
		//! Get vector squared length.
		//! @return			Vector squared length.
		const Real GetSquaredLength( void ) const;
		//! Get distance between two vectors.
		//! @return			Distance.
		const Real GetDistance( const Vector3 & rhs ) const;
		//! Get sqaured distance between two vectors.
		//! @return			Squared distance.
		const Real GetSquaredDistance( const Vector3 & rhs ) const;
		//! Get dot product of two vectors.
		//! @return			Dot product.
		const Real GetDotProduct( const Vector3 & rhs ) const;
		//! Get cross product of two vectors.
		//! @return			Cross product.
		const Vector3 GetCrossProduct( const Vector3 & rhs ) const;
		//! Vector3 type conversion operator.
		//! Used to convert vectors to different internal types.
		template< typename O >
		operator Vector3<O> () const;
	};

	//! Vector3 float type.
	typedef Vector3<Float32>		Vector3f;
	//! Vector3 double type.
	typedef Vector3<Float64>		Vector3d;
	//! Vector3 real type.
	typedef Vector3<Real>			Vector3r;

	/***** Helper Functions *****/
	//! Formats and prints the vector values to an output stream.
	//! @param	stream		Output stream.
	//! @param	vector		Vector to print.
	//! @return				Output stream reference.
	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector3<T> & vector );
}

/***** Template specialisation methods *****/
template<>
CBL_API void cbl::Vector3<cbl::Float32>::Normalise( void );

template<>
CBL_API const cbl::Vector3<cbl::Float32> cbl::Vector3<cbl::Float32>::GetNormalised( void ) const;

template<>
CBL_API void cbl::Vector3<cbl::Float64>::Normalise( void );

template<>
CBL_API const cbl::Vector3<cbl::Float64> cbl::Vector3<cbl::Float64>::GetNormalised( void ) const;

#include "Vector3.inl"

CBL_TYPE( cbl::Vector3f, Vector3f );
CBL_TYPE( cbl::Vector3d, Vector3d );

#endif // __CBL_VECTOR3_H_
