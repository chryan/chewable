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
 * @file Vector4.h
 * @brief 4D vector utility class.
 */

#ifndef __CBL_VECTOR4_H_
#define __CBL_VECTOR4_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Vector3.h"

namespace cbl
{
	//! @brief 4D vector class.
	template< typename T >
	class Vector4
	{
	/***** Static Public Members *****/
	public:
		static const Vector4	ZERO;		//!< (0,0,0,0) Zero vector.
		static const Vector4	ONE;		//!< (1,1,1,1) vector.
		static const Vector4	N_ONE;		//!< (-1,-1,-1,-1) vector.
		static const Vector4	UNIT_X;		//!< X unit vector.
		static const Vector4	UNIT_Y;		//!< Y unit vector.
		static const Vector4	UNIT_Z;		//!< Z unit vector.
		static const Vector4	UNIT_W;		//!< W unit vector.
		static const Vector4	UNIT_NX;	//!< -X unit vector.
		static const Vector4	UNIT_NY;	//!< -Y unit vector.
		static const Vector4	UNIT_NZ;	//!< -Z unit vector.
		static const Vector4	UNIT_NW;	//!< -W unit vector.

	/***** Public Members *****/
	public:
		T			X;	//!< Vector4 X value.
		T			Y;	//!< Vector4 Y value.
		T			Z;	//!< Vector4 Z value.
		T			W;	//!< Vector4 W value;

	/***** Public Methods *****/
	public:
		//! Default constructor.
		Vector4();
		//! Explicit constructor.
		//! @param	t		Fills X, Y, Z and W with t.
		explicit Vector4( const T t );
		//! Contructor.
		//! @param	coords	Coordinates in {X, Y, Z, W} format.
		explicit Vector4( const T coords[4] );
		//! Copy contructor.
		//! @param	rhs		Right-hand side.
		Vector4( const Vector4 & rhs );
		//! Copy contructor from Vector3.
		//! @param	rhs		Right-hand side.
		Vector4( const Vector3<T> & rhs );
		//! Contructor.
		//! @param	x		X value.
		//! @param	y		Y value.
		//! @param	z		Z value.
		//! @param	w		W value.
		Vector4( const T x, const T y, const T z, const T w );
		//! Const index operator.
		//! @param	index	0 for X, 1 for Y, 2 for Z, 3 for W.
		const T operator [] ( const size_t index ) const;
		//! Index operator.
		//! @param	index	0 for X, 1 for Y, 2 for Z, 3 for W.
		T & operator [] ( const size_t index );
		//! Addition operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector4 containing added values.
		const Vector4 operator + ( const Vector4 & rhs ) const;
		//! Subtraction operator.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector4 containing subtracted values.
		const Vector4 operator - ( const Vector4 & rhs ) const;
		//! Unary negation operator.
		//! @return			New Vector4 containing negative values.
		const Vector4 operator - ( void ) const;
		//! Product (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector4 containing scaled values.
		const Vector4 operator * ( const Real scale ) const;
		//! Division (vector scaling) operator.
		//! @param	scale	Scale factor.
		//! @return			New Vector2 containing scaled values.
		const Vector4 operator / ( const Real Scale ) const;
		//! Product operator.
		//! Multiplies each corresponding value { X*X, Y*Y, Z*Z, W*W }.
		//! @param	rhs		Right-hand side.
		//! @return			New Vector2.
		const Vector4 operator * ( const Vector4 & rhs ) const;
		//! Assignment operator.
		//! @param	rhs		Right-hand side.
		Vector4 & operator = ( const Vector4 & rhs );
		//! Assignment operator to convert Vector3 to Vector4.
		//! @param	rhs		Right-hand side Vector3.
		Vector4 & operator = ( const Vector3<T> & rhs );
		//! Increment assignment operator.
		//! @param	rhs		Right-hand side.
		Vector4 & operator += ( const Vector4 & rhs );
		//! Decrement assignment operator.
		//! @param	rhs		Right-hand side.
		Vector4 & operator -= ( const Vector4 & rhs );
		//! Product (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector4 & operator *= ( const Real scale );
		//! Division (vector scaling) assignment operator.
		//! @param	rhs		Right-hand side.
		Vector4 & operator /= ( const Real scale );
		//! Equality operator.
		//! Compares if corresponding values are equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator == ( const Vector4 & rhs ) const;
		//! Inequality operator.
		//! Compares if corresponding values are not equivalent.
		//! @param	rhs		Right-hand side.
		const bool operator != ( const Vector4 & rhs ) const;
		//! Swap values with another vector.
		//! @param	rhs		Other vector.
		void Swap( Vector4 & rhs );
		//! Set X and Y values.
		//! @param	x		X value.
		//! @param	y		Y value.
		//! @param	z		Z value.
		//! @param	w		W value.
		void Set( const T x, const T y, const T z, const T w );
		//! Get dot product of two vectors.
		//! @return			Dot product.
		const Real GetDotProduct( const Vector4 & rhs ) const;
		//! Vector4 type conversion operator.
		//! Used to convert vectors to different internal types.
		template< typename O >
		operator Vector4<O> () const;

		operator Vector3<T> () const;
	};

	//! Vector4 float type.
	typedef Vector4<Float32>		Vector4f;
	//! Vector4 double type.
	typedef Vector4<Float64>		Vector4d;
	//! Vector4 real type.
	typedef Vector4<Real>			Vector4r;

	/***** Constants Definitions *****/
	template< typename T >
	const typename Vector4<T> Vector4<T>::ZERO		= Vector4<T>( T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::ONE		= Vector4<T>( T(1) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::N_ONE		= Vector4<T>( T(-1) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_X	= Vector4<T>( T(1),T(0),T(0),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_Y	= Vector4<T>( T(0),T(1),T(0),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_Z	= Vector4<T>( T(0),T(0),T(1),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_W	= Vector4<T>( T(0),T(0),T(0),T(1) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_NX	= Vector4<T>( T(-1),T(0),T(0),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_NY	= Vector4<T>( T(0),T(-1),T(0),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_NZ	= Vector4<T>( T(0),T(0),T(-1),T(0) );
	template< typename T >
	const typename Vector4<T> Vector4<T>::UNIT_NW	= Vector4<T>( T(0),T(0),T(0),T(-1) );

	/***** Helper Functions *****/

	//! Formats and prints the vector values to an output stream.
	//! @param	stream		Output stream.
	//! @param	vector		Vector to print.
	//! @return				Output stream reference.
	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector4<T> & vector );
}

#include "Vector4.inl"

CBL_TYPE( Vector4f, Vector4f );
CBL_TYPE( Vector4d, Vector4d );

#endif // __CBL_VECTOR4_H_
