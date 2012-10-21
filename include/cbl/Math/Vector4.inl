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
 * @file Vector4.inl
 * @brief 4D vector inline templated functions.
 */

#include "cbl/Debug/Assert.h"

namespace cbl
{
	/***** Inline Methods *****/
	template< typename T >
	inline Vector4<T>::Vector4()
	: X( T(0) ), Y( T(0) ), Z( T(0) ), W( T(0) )
	{
	}

	template< typename T >
	inline Vector4<T>::Vector4( const T t )
	: X( t ), Y( t ), Z( t ), W( t )
	{
	}

	template< typename T >
	inline Vector4<T>::Vector4( const T coords[4] )
	: X( coords[0] ), Y( coords[1] ), Z( coords[2] ), W( coords[3] )
	{
	}

	template< typename T >
	inline Vector4<T>::Vector4( const Vector4 & rhs )
	: X( rhs.X ), Y( rhs.Y ), Z( rhs.Z ), W( rhs.W )
	{
	}

	template< typename T >
	inline Vector4<T>::Vector4( const Vector3<T> & rhs )
	: X( rhs.X ), Y( rhs.Y ), Z( rhs.Z ), W( T(1) )
	{
	}

	template< typename T >
	inline Vector4<T>::Vector4( const T x, const T y, const T z, const T w )
	: X( x ), Y( y ), Z( z ), W( w )
	{
	}
	
	template< typename T >
	inline const T Vector4<T>::operator [] ( const size_t index ) const
	{
		CBL_ASSERT( index < 4, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( &X + index );
	}

	template< typename T >
	inline T & Vector4<T>::operator [] ( const size_t index )
	{
		CBL_ASSERT( index < 4, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( (&X) + index );
	}
	
	template< typename T >
	inline const typename Vector4<T> Vector4<T>::operator + ( const Vector4 & rhs ) const
	{
		return Vector4( X + rhs.X, Y + rhs.Y, Z + rhs.Z, W + rhs.W );
	}

	template< typename T >
	inline const typename Vector4<T> Vector4<T>::operator - ( const Vector4 & rhs ) const
	{
		return Vector4( X - rhs.X, Y - rhs.Y, Z - rhs.Z, W - rhs.W );
	}

	template< typename T >
	inline const typename Vector4<T> Vector4<T>::operator - ( void ) const
	{
		return Vector4( -X, -Y, -Z, -W );
	}

	template< typename T >
	inline const typename Vector4<T> Vector4<T>::operator * ( const Real scale ) const
	{
		return Vector4( T( X * scale ), T( Y * scale ), T( Z * scale ), T( W * scale ) );
	}

	template< typename T >
	inline const typename Vector4<T> Vector4<T>::operator / ( const Real scale ) const
	{
		return Vector4( T( X / scale ), T( Y / scale ), T( Z / scale ), T( W / scale ) );
	}
	
	template< typename T>
	inline const typename Vector4<T> Vector4<T>::operator * ( const Vector4 & rhs ) const
	{
		return Vector4( X * rhs.X, Y * rhs.Y, Z * rhs.Z, W * rhs.W );
	}
	
	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator = ( const Vector4 & rhs )
	{
		X = rhs.X;
		Y = rhs.Y; 
		Z = rhs.Z;
		W = rhs.W;
		return *this;
	}
	
	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator = ( const Vector3<T> & rhs )
	{
		X = rhs.X;
		Y = rhs.Y; 
		Z = rhs.Z;
		W = T(1);
		return *this;
	}

	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator += ( const Vector4 & rhs )
	{
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		W += rhs.W;
		return *this;
	}
	
	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator -= ( const Vector4 & rhs )
	{
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		W -= rhs.W;
		return *this;
	}

	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator *= ( const Real scale )
	{
		X = T( X * scale );
		Y = T( Y * scale );
		Z = T( Z * scale );
		W = T( W * scale );
		return *this;
	}

	template< typename T>
	inline typename Vector4<T> & Vector4<T>::operator /= ( const Real scale )
	{
		X = T( X / scale );
		Y = T( Y / scale );
		Z = T( Z / scale );
		W = T( W / scale );
		return *this;
	}
	
	template< typename T>
	inline const bool Vector4<T>::operator == ( const Vector4 & rhs ) const
	{
		return ( X == rhs.X && Y == rhs.Y && Z == rhs.Z && W == rhs.W );
	}

	template< typename T>
	inline const bool Vector4<T>::operator != ( const Vector4 & rhs ) const
	{
		return ( X != rhs.X || Y != rhs.Y || Z != rhs.Z || W != rhs.W );
	}

	template< typename T >
	inline void Vector4<T>::Swap( Vector4 & rhs )
	{
		std::swap( X, rhs.X );
		std::swap( Y, rhs.Y );
		std::swap( Z, rhs.Z );
		std::swap( W, rhs.W );
	}
	
	template< typename T>
	inline void Vector4<T>::Set( const T x, const T y, const T z, const T w )
	{
		X = x;
		Y = y;
		Z = z;
		W = w;
	}
	
	template< typename T>
	inline const Real Vector4<T>::GetDotProduct( const Vector4 & rhs ) const
	{
		return Real( X * rhs.X + Y * rhs.Y + Z * rhs.Z + W * rhs.W );
	}
	
	template< typename T >
	template< typename O >
	inline Vector4<T>::operator Vector4<O> () const
	{
		return typename Vector4<O>( O( X ), O( Y ), O( Z ), O( W ) );
	}

	template< typename T >
	inline Vector4<T>::operator Vector3<T> () const
	{
		T w = abs( W ) > 0.0 ? W : 1.0f;
		return typename Vector3<T>( X / w, Y / w, Z / w );
	}
	
	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector4<T> & vector )
	{
		stream << "(" << vector.X << ", " << vector.Y << ", " << vector.Z << ", " << vector.W << ")";
		return stream;
	}
}
