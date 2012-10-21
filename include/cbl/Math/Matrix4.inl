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
 * @file Matrix4.inl
 * @brief 4x4 matrix inline methods.
 */

#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

namespace cbl
{
	inline Matrix4::Matrix4()
	{
		memset( M, 0, 16 * sizeof( Real ) );
	}

    inline Matrix4::Matrix4( const Real arr[4][4] )
	{
		memcpy( M, arr , 16 * sizeof( Real ) );
	}

    inline Matrix4::Matrix4( const Matrix4 & rhs )
	{
		memcpy( M, rhs.M, 16 * sizeof( Real ) );
	}

    inline Matrix4::Matrix4( Real m00, Real m10, Real m20, Real m30,
		Real m01, Real m11, Real m21, Real m31,
		Real m02, Real m12, Real m22, Real m32,
		Real m03, Real m13, Real m23, Real m33 )
	{
		M[0][0] = m00; M[1][0] = m10; M[2][0] = m20; M[3][0] = m30;
		M[0][1] = m01; M[1][1] = m11; M[2][1] = m21; M[3][1] = m31;
		M[0][2] = m02; M[1][2] = m12; M[2][2] = m22; M[3][2] = m32;
		M[0][3] = m03; M[1][3] = m13; M[2][3] = m23; M[3][3] = m33;
	}

    inline Real * Matrix4::operator [] ( size_t col )
	{
		CBL_ASSERT_TRUE( col < 4 );
		return ( Real * )( M[col] );
	}

    inline const Real * Matrix4::operator [] ( size_t col ) const
	{
		CBL_ASSERT_TRUE( col < 4 );
		return ( Real * )( M[col] );
	}
	
    inline Matrix4 & Matrix4::operator = ( const Matrix4 & rhs )
	{
		memcpy( M, rhs.M, 16 * sizeof( Real ) );
		return *this;
	}
	
    inline bool Matrix4::operator == ( const Matrix4 & rhs ) const
	{
        if( M[0][0] != rhs.M[0][0] || M[1][0] != rhs.M[1][0] || M[2][0] != rhs.M[2][0] || M[3][0] != rhs.M[3][0] ||
			M[0][1] != rhs.M[0][1] || M[1][1] != rhs.M[1][1] || M[2][1] != rhs.M[2][1] || M[3][1] != rhs.M[3][1] ||
			M[0][2] != rhs.M[0][2] || M[1][2] != rhs.M[1][2] || M[2][2] != rhs.M[2][2] || M[3][2] != rhs.M[3][2] ||
			M[0][3] != rhs.M[0][3] || M[1][3] != rhs.M[1][3] || M[2][3] != rhs.M[2][3] || M[3][3] != rhs.M[3][3] )
            return false;
		return true;
	}
	
    inline bool Matrix4::operator != ( const Matrix4 & rhs ) const
	{
        if( M[0][0] != rhs.M[0][0] || M[1][0] != rhs.M[1][0] || M[2][0] != rhs.M[2][0] || M[3][0] != rhs.M[3][0] ||
			M[0][1] != rhs.M[0][1] || M[1][1] != rhs.M[1][1] || M[2][1] != rhs.M[2][1] || M[3][1] != rhs.M[3][1] ||
			M[0][2] != rhs.M[0][2] || M[1][2] != rhs.M[1][2] || M[2][2] != rhs.M[2][2] || M[3][2] != rhs.M[3][2] ||
			M[0][3] != rhs.M[0][3] || M[1][3] != rhs.M[1][3] || M[2][3] != rhs.M[2][3] || M[3][3] != rhs.M[3][3] )
            return true;
		return false;
	}

    inline Matrix4 Matrix4::operator * ( const Matrix4 & rhs ) const
    {
        return Concatenate( rhs );
    }

    inline Vector3r Matrix4::operator * ( const Vector3r & v ) const
    {
        Vector3r r;
        Real finv = 1.0f / ( M[0][3] * v.X + M[1][3] * v.Y + M[2][3] * v.Z + M[3][3] );

        r.X = ( M[0][0] * v.X + M[1][0] * v.Y + M[2][0] * v.Z + M[3][0] ) * finv;
        r.Y = ( M[0][1] * v.X + M[1][1] * v.Y + M[2][1] * v.Z + M[3][1] ) * finv;
        r.Z = ( M[0][2] * v.X + M[1][2] * v.Y + M[2][2] * v.Z + M[3][2] ) * finv;

        return r;
    }

    inline Vector4r Matrix4::operator * ( const Vector4r & v ) const
    {
        return Vector4r(
            M[0][0] * v.X + M[1][0] * v.Y + M[2][0] * v.Z + M[3][0] * v.W, 
            M[0][1] * v.X + M[1][1] * v.Y + M[2][1] * v.Z + M[3][1] * v.W,
            M[0][2] * v.X + M[1][2] * v.Y + M[2][2] * v.Z + M[3][2] * v.W,
            M[0][3] * v.X + M[1][3] * v.Y + M[2][3] * v.Z + M[3][3] * v.W
            );
    }

	inline Matrix4 Matrix4::operator * ( const cbl::Real scalar ) const
	{
		Matrix4 newM = *this;
		newM.M[0][0] *= scalar;
		newM.M[1][0] *= scalar;
		newM.M[2][0] *= scalar;
		newM.M[3][0] *= scalar;
		newM.M[0][1] *= scalar;
		newM.M[1][1] *= scalar;
		newM.M[2][1] *= scalar;
		newM.M[3][1] *= scalar;
		newM.M[0][2] *= scalar;
		newM.M[1][2] *= scalar;
		newM.M[2][2] *= scalar;
		newM.M[3][2] *= scalar;
		newM.M[0][3] *= scalar;
		newM.M[1][3] *= scalar;
		newM.M[2][3] *= scalar;
		newM.M[3][3] *= scalar;

		return newM;
	}

	inline Matrix4 & Matrix4::operator *= ( const cbl::Matrix4 & rhs )
	{
		*this = *this * rhs;
		return *this;
	}

	inline Matrix4 & Matrix4::operator *= ( const cbl::Real scalar )
	{
		M[0][0] *= scalar;
		M[1][0] *= scalar;
		M[2][0] *= scalar;
		M[3][0] *= scalar;
		M[0][1] *= scalar;
		M[1][1] *= scalar;
		M[2][1] *= scalar;
		M[3][1] *= scalar;
		M[0][2] *= scalar;
		M[1][2] *= scalar;
		M[2][2] *= scalar;
		M[3][2] *= scalar;
		M[0][3] *= scalar;
		M[1][3] *= scalar;
		M[2][3] *= scalar;
		M[3][3] *= scalar;

		return *this;
	}

    inline Matrix4 Matrix4::operator + ( const Matrix4 & rhs ) const
    {
        Matrix4 r;

        r.M[0][0] = M[0][0] + rhs.M[0][0];
        r.M[1][0] = M[1][0] + rhs.M[1][0];
        r.M[2][0] = M[2][0] + rhs.M[2][0];
        r.M[3][0] = M[3][0] + rhs.M[3][0];

        r.M[0][1] = M[0][1] + rhs.M[0][1];
        r.M[1][1] = M[1][1] + rhs.M[1][1];
        r.M[2][1] = M[2][1] + rhs.M[2][1];
        r.M[3][1] = M[3][1] + rhs.M[3][1];

        r.M[0][2] = M[0][2] + rhs.M[0][2];
        r.M[1][2] = M[1][2] + rhs.M[1][2];
        r.M[2][2] = M[2][2] + rhs.M[2][2];
        r.M[3][2] = M[3][2] + rhs.M[3][2];

        r.M[0][3] = M[0][3] + rhs.M[0][3];
        r.M[1][3] = M[1][3] + rhs.M[1][3];
        r.M[2][3] = M[2][3] + rhs.M[2][3];
        r.M[3][3] = M[3][3] + rhs.M[3][3];

        return r;
    }

    inline Matrix4 Matrix4::operator - ( const Matrix4 & rhs ) const
    {
        Matrix4 r;
        r.M[0][0] = M[0][0] - rhs.M[0][0];
        r.M[1][0] = M[1][0] - rhs.M[1][0];
        r.M[2][0] = M[2][0] - rhs.M[2][0];
        r.M[3][0] = M[3][0] - rhs.M[3][0];

        r.M[0][1] = M[0][1] - rhs.M[0][1];
        r.M[1][1] = M[1][1] - rhs.M[1][1];
        r.M[2][1] = M[2][1] - rhs.M[2][1];
        r.M[3][1] = M[3][1] - rhs.M[3][1];

        r.M[0][2] = M[0][2] - rhs.M[0][2];
        r.M[1][2] = M[1][2] - rhs.M[1][2];
        r.M[2][2] = M[2][2] - rhs.M[2][2];
        r.M[3][2] = M[3][2] - rhs.M[3][2];

        r.M[0][3] = M[0][3] - rhs.M[0][3];
        r.M[1][3] = M[1][3] - rhs.M[1][3];
        r.M[2][3] = M[2][3] - rhs.M[2][3];
        r.M[3][3] = M[3][3] - rhs.M[3][3];

        return r;
    }

	inline void Matrix4::Swap( Matrix4 & rhs )
	{	
		std::swap( M[0][0], rhs.M[0][0] );
		std::swap( M[1][0], rhs.M[1][0] );
		std::swap( M[2][0], rhs.M[2][0] );
		std::swap( M[3][0], rhs.M[3][0] );
		std::swap( M[0][1], rhs.M[0][1] );
		std::swap( M[1][1], rhs.M[1][1] );
		std::swap( M[2][1], rhs.M[2][1] );
		std::swap( M[3][1], rhs.M[3][1] );
		std::swap( M[0][2], rhs.M[0][2] );
		std::swap( M[1][2], rhs.M[1][2] );
		std::swap( M[2][2], rhs.M[2][2] );
		std::swap( M[3][2], rhs.M[3][2] );
		std::swap( M[0][3], rhs.M[0][3] );
		std::swap( M[1][3], rhs.M[1][3] );
		std::swap( M[2][3], rhs.M[2][3] );
		std::swap( M[3][3], rhs.M[3][3] );
	}
	
	inline Matrix4 Matrix4::Concatenate( const Matrix4 & rhs ) const
	{
		Matrix4 r;
		r.M[0][0] = M[0][0] * rhs.M[0][0] + M[1][0] * rhs.M[0][1] + M[2][0] * rhs.M[0][2] + M[3][0] * rhs.M[0][3];
		r.M[1][0] = M[0][0] * rhs.M[1][0] + M[1][0] * rhs.M[1][1] + M[2][0] * rhs.M[1][2] + M[3][0] * rhs.M[1][3];
		r.M[2][0] = M[0][0] * rhs.M[2][0] + M[1][0] * rhs.M[2][1] + M[2][0] * rhs.M[2][2] + M[3][0] * rhs.M[2][3];
		r.M[3][0] = M[0][0] * rhs.M[3][0] + M[1][0] * rhs.M[3][1] + M[2][0] * rhs.M[3][2] + M[3][0] * rhs.M[3][3];

		r.M[0][1] = M[0][1] * rhs.M[0][0] + M[1][1] * rhs.M[0][1] + M[2][1] * rhs.M[0][2] + M[3][1] * rhs.M[0][3];
		r.M[1][1] = M[0][1] * rhs.M[1][0] + M[1][1] * rhs.M[1][1] + M[2][1] * rhs.M[1][2] + M[3][1] * rhs.M[1][3];
		r.M[2][1] = M[0][1] * rhs.M[2][0] + M[1][1] * rhs.M[2][1] + M[2][1] * rhs.M[2][2] + M[3][1] * rhs.M[2][3];
		r.M[3][1] = M[0][1] * rhs.M[3][0] + M[1][1] * rhs.M[3][1] + M[2][1] * rhs.M[3][2] + M[3][1] * rhs.M[3][3];

		r.M[0][2] = M[0][2] * rhs.M[0][0] + M[1][2] * rhs.M[0][1] + M[2][2] * rhs.M[0][2] + M[3][2] * rhs.M[0][3];
		r.M[1][2] = M[0][2] * rhs.M[1][0] + M[1][2] * rhs.M[1][1] + M[2][2] * rhs.M[1][2] + M[3][2] * rhs.M[1][3];
		r.M[2][2] = M[0][2] * rhs.M[2][0] + M[1][2] * rhs.M[2][1] + M[2][2] * rhs.M[2][2] + M[3][2] * rhs.M[2][3];
		r.M[3][2] = M[0][2] * rhs.M[3][0] + M[1][2] * rhs.M[3][1] + M[2][2] * rhs.M[3][2] + M[3][2] * rhs.M[3][3];

		r.M[0][3] = M[0][3] * rhs.M[0][0] + M[1][3] * rhs.M[0][1] + M[2][3] * rhs.M[0][2] + M[3][3] * rhs.M[0][3];
		r.M[1][3] = M[0][3] * rhs.M[1][0] + M[1][3] * rhs.M[1][1] + M[2][3] * rhs.M[1][2] + M[3][3] * rhs.M[1][3];
		r.M[2][3] = M[0][3] * rhs.M[2][0] + M[1][3] * rhs.M[2][1] + M[2][3] * rhs.M[2][2] + M[3][3] * rhs.M[2][3];
		r.M[3][3] = M[0][3] * rhs.M[3][0] + M[1][3] * rhs.M[3][1] + M[2][3] * rhs.M[3][2] + M[3][3] * rhs.M[3][3];

		return r;
	}

	inline Matrix4 Matrix4::Transpose( void ) const
	{
		return Matrix4(	M[0][0], M[0][1], M[0][2], M[0][3],
						M[1][0], M[1][1], M[1][2], M[1][3],
						M[2][0], M[2][1], M[2][2], M[2][3],
						M[3][0], M[3][1], M[3][2], M[3][3]);
	}

	inline cbl::Vector3f Matrix4::GetRow3( cbl::Uint32 index ) const {
		return cbl::Vector3f( M[0][index], M[1][index], M[2][index] );
	}

	inline cbl::Vector3f Matrix4::GetColumn3( cbl::Uint32 index ) const {
		return cbl::Vector3f( M[index] );
	}

	inline cbl::Vector4f Matrix4::GetRow4( cbl::Uint32 index ) const {
		return cbl::Vector4f( M[0][index], M[1][index], M[2][index], M[3][index] );
	}

	inline cbl::Vector4f Matrix4::GetColumn4( cbl::Uint32 index ) const {
		return cbl::Vector4f( M[index] );
	}
	
	inline Matrix4 Matrix4::Translation( const Vector3r & v )
	{
		return Matrix4( 1, 0, 0, v.X,
						0, 1, 0, v.Y, 
						0, 0, 1, v.Z,
						0, 0, 0, 1 );
	}

	inline Matrix4 Matrix4::Translation( Real x, Real y, Real z )
	{
		return Matrix4( 1, 0, 0, x,
						0, 1, 0, y, 
						0, 0, 1, z,
						0, 0, 0, 1 );
	}
	
	inline Matrix4 Matrix4::Scaling( const Vector3r & v )
	{
		return Matrix4( v.X,   0,   0,   0,
						  0, v.Y,   0,   0, 
						  0,   0, v.Z,   0,
						  0,   0,   0,   1 );
	}

	inline Matrix4 Matrix4::Scaling( Real x, Real y, Real z )
	{
		return Matrix4( x, 0, 0, 0,
						0, y, 0, 0, 
						0, 0, z, 0,
						0, 0, 0, 1 );
	}
	
	inline Matrix4 Matrix4::RotationX( Real r )
	{
		Real c = cos( r );
		Real s = sin( r );
		return Matrix4( 1, 0, 0, 0,
						0, c,-s, 0, 
						0, s, c, 0,
						0, 0, 0, 1 );
	}

	inline Matrix4 Matrix4::RotationY( Real r )
	{
		Real c = cos( r );
		Real s = sin( r );
		return Matrix4( c, 0, s, 0,
						0, 1, 0, 0, 
					   -s, 0, c, 0,
						0, 0, 0, 1 );
	}

	inline Matrix4 Matrix4::RotationZ( Real r )
	{
		Real c = cos( r );
		Real s = sin( r );
		return Matrix4( c,-s, 0, 0,
						s, c, 0, 0, 
						0, 0, 1, 0,
						0, 0, 0, 1 );
	}
}
