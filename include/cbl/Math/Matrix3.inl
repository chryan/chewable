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
 * @file Matrix3.inl
 * @brief 3x3 matrix utility class.
 */

namespace cbl
{
	inline Matrix3::Matrix3()
	{
		memset( _M, 0, sizeof(_M) );
	}

	inline Matrix3::Matrix3( const Real arr[3][3] )
	{
		memcpy( M, arr, sizeof(_M) );
	}

	inline Matrix3::Matrix3( const Matrix3 & rhs )
	{
		memcpy( _M, rhs._M, sizeof(_M) );
	}

	inline Matrix3::Matrix3( Real m00, Real m10, Real m20, 
		Real m01, Real m11, Real m21,
		Real m02, Real m12, Real m22 )
	{
		M[0][0] = m00; M[1][0] = m10; M[2][0] = m20; 
		M[0][1] = m01; M[1][1] = m11; M[2][1] = m21; 
		M[0][2] = m02; M[1][2] = m12; M[2][2] = m22; 
	}

	inline Real * Matrix3::operator [] ( size_t col )
	{
		CBL_ASSERT_TRUE( col < 4 );
		return ( Real * )( M[col] );
	}

	inline const Real * Matrix3::operator [] ( size_t col ) const
	{
		CBL_ASSERT_TRUE( col < 4 );
		return ( Real * )( M[col] );
	}

	inline Matrix3& Matrix3::operator= ( const Matrix3 & rhs )
	{
		memcpy( M, rhs.M, sizeof(_M) );
		return *this;
	}

	inline Matrix3 Matrix3::operator * ( const Matrix3 & rhs ) const
	{
		return Concatenate( rhs );
	}

	inline Matrix3 Matrix3::operator * ( const Real scalar ) const
	{
		Matrix3 newM = *this;
		newM.M[0][0] *= scalar;
		newM.M[1][0] *= scalar;
		newM.M[2][0] *= scalar;
		newM.M[0][1] *= scalar;
		newM.M[1][1] *= scalar;
		newM.M[2][1] *= scalar;
		newM.M[0][2] *= scalar;
		newM.M[1][2] *= scalar;
		newM.M[2][2] *= scalar;

		return newM;
	}

	inline Matrix3 & Matrix3::operator *= ( const Matrix3 & rhs )
	{
		*this = *this * rhs;
		return *this;
	}

	inline Matrix3 & Matrix3::operator *= ( const Real scalar )
	{
		M[0][0] *= scalar;
		M[1][0] *= scalar;
		M[2][0] *= scalar;
		M[0][1] *= scalar;
		M[1][1] *= scalar;
		M[2][1] *= scalar;
		M[0][2] *= scalar;
		M[1][2] *= scalar;
		M[2][2] *= scalar;

		return *this;
	}

	inline Vector3f Matrix3::operator * ( const Vector3f & v ) const
	{
		return Vector3f(
			M[0][0] * v.X + M[1][0] * v.Y + M[2][0] * v.Z, 
			M[0][1] * v.X + M[1][1] * v.Y + M[2][1] * v.Z,
			M[0][2] * v.X + M[1][2] * v.Y + M[2][2] * v.Z
			);
	}

	inline void Matrix3::Swap( Matrix3& rhs )
	{
		std::swap( M[0][0], rhs.M[0][0] );
		std::swap( M[1][0], rhs.M[1][0] );
		std::swap( M[2][0], rhs.M[2][0] );
		std::swap( M[0][1], rhs.M[0][1] );
		std::swap( M[1][1], rhs.M[1][1] );
		std::swap( M[2][1], rhs.M[2][1] );
		std::swap( M[0][2], rhs.M[0][2] );
		std::swap( M[1][2], rhs.M[1][2] );
		std::swap( M[2][2], rhs.M[2][2] );
	}

	inline Matrix3 Matrix3::Concatenate( const Matrix3& rhs ) const
	{
		Matrix3 r;
		r.M[0][0] = M[0][0] * rhs.M[0][0] + M[1][0] * rhs.M[0][1] + M[2][0] * rhs.M[0][2];
		r.M[1][0] = M[0][0] * rhs.M[1][0] + M[1][0] * rhs.M[1][1] + M[2][0] * rhs.M[1][2];
		r.M[2][0] = M[0][0] * rhs.M[2][0] + M[1][0] * rhs.M[2][1] + M[2][0] * rhs.M[2][2];

		r.M[0][1] = M[0][1] * rhs.M[0][0] + M[1][1] * rhs.M[0][1] + M[2][1] * rhs.M[0][2];
		r.M[1][1] = M[0][1] * rhs.M[1][0] + M[1][1] * rhs.M[1][1] + M[2][1] * rhs.M[1][2];
		r.M[2][1] = M[0][1] * rhs.M[2][0] + M[1][1] * rhs.M[2][1] + M[2][1] * rhs.M[2][2];

		r.M[0][2] = M[0][2] * rhs.M[0][0] + M[1][2] * rhs.M[0][1] + M[2][2] * rhs.M[0][2];
		r.M[1][2] = M[0][2] * rhs.M[1][0] + M[1][2] * rhs.M[1][1] + M[2][2] * rhs.M[1][2];
		r.M[2][2] = M[0][2] * rhs.M[2][0] + M[1][2] * rhs.M[2][1] + M[2][2] * rhs.M[2][2];

		return r;
	}

	inline Vector2f Matrix3::GetRow2( Uint32 index ) const {
		return Vector2f( M[0][index], M[1][index] );
	}

	inline Vector2f Matrix3::GetColumn2( Uint32 index ) const {
		return Vector2f( M[index] );
	}

	inline Vector3f Matrix3::GetRow3( Uint32 index ) const {
		return Vector3f( M[0][index], M[1][index], M[2][index] );
	}

	inline Vector3f Matrix3::GetColumn3( Uint32 index ) const {
		return Vector3f( M[index] );
	}

	inline Matrix3 Matrix3::Translation( Real x, Real y )
	{
		return Matrix3( 1, 0, 0,
						0, 1, 0, 
						x, y, 1 );
	}

	inline Matrix3 Matrix3::Scaling( Real x, Real y )
	{
		return Matrix3( x, 0, 0,
						0, y, 0, 
						0, 0, 1 );
	}

	inline Matrix3 Matrix3::Rotation( Real rad )
	{
		Real cosA = Math::Cos< Real >( rad );
		Real sinA = Math::Sin< Real >( rad );

		return Matrix3( cosA, sinA, 0,
					   -sinA, cosA, 0, 
						   0,    0, 1 );
	}
}
