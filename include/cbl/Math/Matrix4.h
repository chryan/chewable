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
 * @file Matrix4.h
 * @brief 4x4 matrix utility class.
 */

#ifndef __CBL_MATRIX4_H_
#define __CBL_MATRIX4_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Vector3.h"
#include "cbl/Math/Vector4.h"

namespace cbl
{
	//! @brief 4x4 matrix class.
	//! Matrix values are stored in a column-major order.
	class CBL_API Matrix4
	{
	/***** Static Public Members *****/
	public:
		static const Matrix4	ZERO;		//!< Zero matrix.
		static const Matrix4	IDENTITY;	//!< Identity matrix.

	/***** Public Members *****/
	public:
		//! Matrix values union
		union {
			Real M[4][4];
			Real _M[16];
			Real* _pM;
		};
		
	/***** Public Methods *****/
	public:
		//! Constructor. Sets all values to 0.
		Matrix4();
		//! Constructor.
		//! @param	arr		Matrix array values.
        explicit Matrix4( const Real arr[4][4] );
		//! Copy constructor.
        Matrix4( const Matrix4 & rhs );
		//! Constructor for each individual values. [col][row]
		Matrix4( Real m00, Real m10, Real m20, Real m30,
			Real m01, Real m11, Real m21, Real m31,
			Real m02, Real m12, Real m22, Real m32,
			Real m03, Real m13, Real m23, Real m33 );
		//! Get matrix row pointer.
		//! @param	col		Column number.
		//! @return			Pointer to col array.
        Real * operator [] ( size_t col );
		//! Get matrix row pointer.
		//! @param	col		Column number.
		//! @return			Pointer to col array.
        const Real * operator [] ( size_t col ) const;
		//! Assignment operator.
        Matrix4 & operator = ( const Matrix4 & rhs );
		//! Comparison operator. Checks if matrices are the same.
		//! @param	rhs		Right hand side.
		//! @return			Same?
        bool operator == ( const Matrix4 & rhs ) const;
		//! Inequality operator. Checks if matrices are not the same.
		//! @param	rhs		Right hand side.
		//! @return			Not the same?
        bool operator != ( const Matrix4 & rhs ) const;
		//! Matrix concatenation operator.
		//! @param	rhs		Right hand side.
		//! @return			New concatenated matrix.
		Matrix4 operator * ( const Matrix4 & rhs ) const;
		//! Matrix concatenation operator.
		//! @param	rhs		Right hand side vector.
		//! @return			New transformed vector.
		Vector3r operator * ( const Vector3r & rhs ) const;
		//! Matrix concatenation operator.
		//! @param	rhs		Right hand side vector.
		//! @return			New transformed vector.
		Vector4r operator * ( const Vector4r & rhs ) const;
		//! Matrix scalar operator.
		//! @param	rhs		Right hand side scalar.
		//! @return			New scaled matrix.
		Matrix4 operator * ( const cbl::Real scalar ) const;
		//! Matrix concatenation.
		//! @param	rhs		Right hand side matrix.
		Matrix4 & operator *= ( const cbl::Matrix4 & rhs );
		//! Matrix concatenation.
		//! @param	rhs		Right hand side scalar.
		Matrix4 & operator *= ( const cbl::Real scalar );
		//! Matrix addition operator.
		//! @param	rhs		Right hand side.
		//! @return			New matrix with added values.
		Matrix4 operator + ( const Matrix4 & rhs ) const;
		//! Matrix subtraction operator.
		//! @param	rhs		Right hand side.
		//! @return			New matrix with subtracted values.
		Matrix4 operator - ( const Matrix4 & rhs ) const;
		//! Swap values with another matrix.
		//! @param	rhs		Right hand side.
		void Swap( Matrix4 & rhs );
		//! Matrix concatenation.
		//! @param	rhs		Right hand side.
		//! @return			New concatenated matrix.
		Matrix4 Concatenate( const Matrix4 & rhs ) const;
		//! Matrix transpose.
		//! @return			Matrix transpose.
		Matrix4 Transpose( void ) const;
		//! Get a vector3 from a matrix row.
		//! i.e. M[0][index], M[1][index], M[2][index]
		//! @param	index	Matrix row index.
		//! @return			Vector3 row.
		cbl::Vector3f GetRow3( cbl::Uint32 index ) const;
		//! Get a vector3 from a matrix column.
		//! i.e. M[index][0], M[index][1], M[index][2]
		//! @param	index	Matrix column index.
		//! @return			Vector3 column.
		cbl::Vector3f GetColumn3( cbl::Uint32 index ) const;
		//! Get a vector4 from a matrix row.
		//! i.e. M[0][index], M[1][index], M[2][index], M[3][index]
		//! @param	index	Matrix row index.
		//! @return			Vector3 row.
		cbl::Vector4f GetRow4( cbl::Uint32 index ) const;
		//! Get a vector4 from a matrix column.
		//! i.e. M[index][0], M[index][1], M[index][2], M[index][3]
		//! @param	index	Matrix column index.
		//! @return			Vector3 column.
		cbl::Vector4f GetColumn4( cbl::Uint32 index ) const;
		//! Get the inverse of this matrix.
		//! @return			Matrix inverse.
		Matrix4 Inverse( void ) const;

	/***** Static Public Methods *****/
	public:
		//! Translation matrix.
		//! @param	v	Translation vector.
		static Matrix4 Translation( const Vector3r & v );
		//! Translation matrix.
		//! @param	x	X scale.
		//! @param	x	Y scale.
		//! @param	x	Z scale.
		static Matrix4 Translation( Real x, Real y, Real z );
		//! Scaling matrix.
		//! @param	v	Scale vector.
		static Matrix4 Scaling( const Vector3r & v );
		//! Scaling matrix.
		//! @param	x	X scale.
		//! @param	x	Y scale.
		//! @param	x	Z scale.
		static Matrix4 Scaling( Real x, Real y, Real z );
		//! Rotation matrix about X axis.
		//! @param	r	Rotation angle.
		static Matrix4 RotationX( Real r );
		//! Rotation matrix about Y axis.
		//! @param	r	Rotation angle.
		static Matrix4 RotationY( Real r );
		//! Rotation matrix about Z axis.
		//! @param	r	Rotation angle.
		static Matrix4 RotationZ( Real r );
		//! Rotation matrix about arbitrary axis.
		//! @param	v	Arbitrary axis.
		//! @param	r	Rotation angle.
		static Matrix4 Rotation( const Vector3r & v, Real r );
	};
}

#include "Matrix4.inl"

CBL_TYPE( cbl::Matrix4, Matrix4 );

#endif // __CBL_MATRIX4_H_
