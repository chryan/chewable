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
 * @file Matrix4.cpp
 * @brief 4x4 matrix method definitions.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Math/Matrix4.h"

using namespace cbl;

const Matrix4 Matrix4::ZERO(
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0,
    0, 0, 0, 0 );

const Matrix4 Matrix4::IDENTITY(
    1, 0, 0, 0,
    0, 1, 0, 0,
    0, 0, 1, 0,
    0, 0, 0, 1 );

Matrix4 Matrix4::Rotation( const Vector3r & v, Real r )
{
	Vector3r n = v.GetNormalised();
	Real c = cos( r );
	Real nc = 1.0f - c;
	Real s = sin( r );
	Real xs = n.X*s;
	Real ys = n.Y*s;
	Real zs = n.Z*s;

	Real xx = n.X * n.X;
	Real xyc = n.X * n.Y * nc;
	Real xzc = n.X * n.Z * nc;
	Real yy = n.Y * n.Y;
	Real yzc = n.Y * n.Z * nc;
	Real zz = n.Z * n.Z;

	return Matrix4( xx + (1.0f-xx)*c,	xyc + zs,			xzc - ys, 0.0,
					xyc - zs,			yy + (1.0f-yy)*c,	yzc + xs, 0.0, 
					xzc + ys,			yzc - xs,			zz + (1.0f-zz)*c, 0.0,
					0.0, 0.0, 0.0, 1.0f );
}

Matrix4 Matrix4::Inverse() const
{
	Real m00 = M[0][0], m01 = M[0][1], m02 = M[0][2], m03 = M[0][3];
	Real m10 = M[1][0], m11 = M[1][1], m12 = M[1][2], m13 = M[1][3];
	Real m20 = M[2][0], m21 = M[2][1], m22 = M[2][2], m23 = M[2][3];
	Real m30 = M[3][0], m31 = M[3][1], m32 = M[3][2], m33 = M[3][3];

	Real v0 = m20 * m31 - m21 * m30;
	Real v1 = m20 * m32 - m22 * m30;
	Real v2 = m20 * m33 - m23 * m30;
	Real v3 = m21 * m32 - m22 * m31;
	Real v4 = m21 * m33 - m23 * m31;
	Real v5 = m22 * m33 - m23 * m32;

	Real t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	Real t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	Real t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	Real t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	Real invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	Real d00 = t00 * invDet;
	Real d10 = t10 * invDet;
	Real d20 = t20 * invDet;
	Real d30 = t30 * invDet;

	Real d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	Real d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	Real d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	Real d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	Real d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	Real d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return Matrix4(
		d00, d10, d20, d30,
		d01, d11, d21, d31,
		d02, d12, d22, d32,
		d03, d13, d23, d33
	);
}