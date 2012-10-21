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
 * @file Matrix3.h
 * @brief 3x3 matrix utility class.
 */
 
#ifndef __CBL_MATRIX3_H_
#define __CBL_MATRIX3_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Vector2.h"
#include "cbl/Math/Vector3.h"

namespace cbl
{
	//! Matrix3
	class CBL_API Matrix3
	{
	/***** Public Static Members *****/
	public:
		static const Matrix3	ZERO;		//!< Zero matrix.
		static const Matrix3	IDENTITY;	//!< Identity matrix.
		
	/***** Public Members *****/
	public:
		//! Matrix values
		union {
			Real	M[3][3];
			Real	_M[9];
			Real*	_pM;
		};
		
	/***** Public Methods *****/
	public:
		//! Constructor. Sets all values to 0.
		Matrix3();
		//! Constructor.
		//! @param	arr		Matrix array values.
        explicit Matrix3( const Real arr[3][3] );
		//! Copy constructor.
        Matrix3( const Matrix3 & rhs );
		//! Constructor for each individual values. [col][row]
        Matrix3( Real m00, Real m10, Real m20, 
			Real m01, Real m11, Real m21,
			Real m02, Real m12, Real m22 );
		//! Get matrix row pointer.
		//! @param	col		Column number.
		//! @return			Pointer to col array.
		Real * operator [] ( size_t col );
		//! Get matrix row pointer.
		//! @param	col		Column number.
		//! @return			Pointer to col array.
		const Real * operator [] ( size_t col ) const;
		//! Assignment operator.
		Matrix3& operator = ( const Matrix3& rhs );
		//! Matrix-matrix concatentation
		//! @param	rhs		Right hand side.
		//! @return			New concatenated matrix.
		Matrix3 operator * ( const Matrix3& rhs ) const;
		//! Matrix scaling.
		//! @param	rhs		Right hand side scalar.
		//! @return			New scaled matrix.
		Matrix3 operator * ( const Real scalar ) const;
		//! Matrix-matrix concatentation
		//! @param	rhs		Right hand side.
		//! @return			New concatenated matrix.
		Matrix3& operator *= ( const Matrix3& rhs );
		//! Matrix scaling.
		//! @param	rhs		Right hand side scalar.
		//! @return			New scaled matrix.
		Matrix3& operator *= ( const Real scalar );
		//! Matrix-vector multiplication.
		//! @param	rhs		Right hand side vector.
		//! @return			New transformed vector.
		Vector3f operator * ( const Vector3f& rhs ) const;
		//! Swap values with another matrix.
		//! @param	rhs		Right hand side.
		void Swap( Matrix3 & rhs );
		//! Matrix concatenation.
		//! @param	rhs		Right hand side.
		//! @return			New concatenated matrix.
		Matrix3 Concatenate( const Matrix3& rhs ) const;
		//! Get a vector2 from a matrix row.
		//! i.e. M[0][index], M[1][index]
		//! @param	index	Matrix row index.
		//! @return			Vector2 row.
		Vector2f GetRow2( Uint32 index ) const;
		//! Get a vector2 from a matrix column.
		//! i.e. M[index][0], M[index][1]
		//! @param	index	Matrix column index.
		//! @return			Vector2 column.
		Vector2f GetColumn2( Uint32 index ) const;
		//! Get a vector3 from a matrix row.
		//! i.e. M[0][index], M[1][index], M[2][index]
		//! @param	index	Matrix row index.
		//! @return			Vector3 row.
		Vector3f GetRow3( Uint32 index ) const;
		//! Get a vector3 from a matrix column.
		//! i.e. M[index][0], M[index][1], M[index][2]
		//! @param	index	Matrix column index.
		//! @return			Vector3 column.
		Vector3f GetColumn3( Uint32 index ) const;

	/***** Public Static Members *****/
	public:
		//! Creates a matrix which translates by (x, y).
		static Matrix3 Translation( Real x, Real y );
		//! Creates a matrix which scales by (x, y).
		static Matrix3 Scaling( Real x, Real y );
		//! Creates a matrix which rotates anticlockwise by radians.
		static Matrix3 Rotation( Real rad );
	};
}

#include "Matrix3.inl"

CBL_TYPE( cbl::Matrix3, Matrix3 );

#endif // __CBL_MATRIX3_H_
