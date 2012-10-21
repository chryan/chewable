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
 * @file Vector3.inl
 * @brief 3D vector inline templated functions.
 */

#include "cbl/Debug/Assert.h"

namespace cbl
{
	/***** Constants Definitions *****/
	template< typename T >
	const typename Vector3<T> Vector3<T>::ZERO		= Vector3<T>( T(0) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::ONE		= Vector3<T>( T(1) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::N_ONE		= Vector3<T>( T(-1) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_X	= Vector3<T>( T(1), T(0), T(0) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_Y	= Vector3<T>( T(0), T(1), T(0) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_Z	= Vector3<T>( T(0), T(0), T(1) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_NX	= Vector3<T>( T(-1), T(0), T(0) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_NY	= Vector3<T>( T(0), T(-1), T(0) );
	template< typename T >
	const typename Vector3<T> Vector3<T>::UNIT_NZ	= Vector3<T>( T(0), T(0), T(-1) );

	/***** Inline Methods *****/
	template< typename T >
	inline Vector3<T>::Vector3()
	: X( T(0) ), Y( T(0) ), Z( T(0) )
	{
	}

	template< typename T >
	inline Vector3<T>::Vector3( const T t )
	: X( t ), Y( t ), Z( t )
	{
	}

	template< typename T >
	inline Vector3<T>::Vector3( const T coords[3] )
	: X( coords[0] ), Y( coords[1] ), Z( coords[2] )
	{
	}

	template< typename T >
	inline Vector3<T>::Vector3( const Vector3 & rhs )
	: X( rhs.X ), Y( rhs.Y ), Z( rhs.Z )
	{
	}

	template< typename T >
	inline Vector3<T>::Vector3( const T x, const T y, const T z )
	: X( x ), Y( y ), Z( z )
	{
	}
	
	template< typename T >
	inline const T Vector3<T>::operator [] ( const size_t index ) const
	{
		CBL_ASSERT( index < 3, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( &X + index );
	}

	template< typename T >
	inline T & Vector3<T>::operator [] ( const size_t index )
	{
		CBL_ASSERT( index < 3, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( (&X) + index );
	}
	
	template< typename T >
	inline const typename Vector3<T> Vector3<T>::operator + ( const Vector3 & rhs ) const
	{
		return Vector3( X + rhs.X, Y + rhs.Y, Z + rhs.Z );
	}

	template< typename T >
	inline const typename Vector3<T> Vector3<T>::operator - ( const Vector3 & rhs ) const
	{
		return Vector3( X - rhs.X, Y - rhs.Y, Z - rhs.Z );
	}

	template< typename T >
	inline const typename Vector3<T> Vector3<T>::operator - ( void ) const
	{
		return Vector3( -X, -Y, -Z );
	}

	template< typename T >
	inline const typename Vector3<T> Vector3<T>::operator * ( const Real scale ) const
	{
		return Vector3( T( X * scale ), T( Y * scale ), T( Z * scale ) );
	}

	template< typename T >
	inline const typename Vector3<T> Vector3<T>::operator / ( const Real scale ) const
	{
		return Vector3( T( X / scale ), T( Y / scale ), T( Z / scale ) );
	}
	
	template< typename T>
	inline const typename Vector3<T> Vector3<T>::operator * ( const Vector3 & rhs ) const
	{
		return Vector3( X * rhs.X, Y * rhs.Y, Z * rhs.Z );
	}
	
	template< typename T>
	inline typename Vector3<T> & Vector3<T>::operator = ( const Vector3 & rhs )
	{
		X = rhs.X;
		Y = rhs.Y;
		Z = rhs.Z;
		return *this;
	}

	template< typename T>
	inline typename Vector3<T> & Vector3<T>::operator += ( const Vector3 & rhs )
	{
		X += rhs.X;
		Y += rhs.Y;
		Z += rhs.Z;
		return *this;
	}
	
	template< typename T>
	inline typename Vector3<T> & Vector3<T>::operator -= ( const Vector3 & rhs )
	{
		X -= rhs.X;
		Y -= rhs.Y;
		Z -= rhs.Z;
		return *this;
	}

	template< typename T>
	inline typename Vector3<T> & Vector3<T>::operator *= ( const Real scale )
	{
		X = T( X * scale );
		Y = T( Y * scale );
		Z = T( Z * scale );
		return *this;
	}

	template< typename T>
	inline typename Vector3<T> & Vector3<T>::operator /= ( const Real scale )
	{
		X = T( X / scale );
		Y = T( Y / scale );
		Z = T( Z / scale );
		return *this;
	}
	
	template< typename T>
	inline const bool Vector3<T>::operator == ( const Vector3 & rhs ) const
	{
		return ( X == rhs.X && Y == rhs.Y && Z == rhs.Z );
	}

	template< typename T>
	inline const bool Vector3<T>::operator != ( const Vector3 & rhs ) const
	{
		return ( X != rhs.X || Y != rhs.Y || Z != rhs.Z );
	}

	template< typename T >
	inline void Vector3<T>::Swap( Vector3 & rhs )
	{
		std::swap( X, rhs.X );
		std::swap( Y, rhs.Y );
		std::swap( Z, rhs.Z );
	}
	
	template< typename T>
	inline void Vector3<T>::Set( const T x, const T y, const T z )
	{
		X = x;
		Y = y;
		Z = z;
	}

	template< typename T>
	inline void Vector3<T>::Normalise( void )
	{
		CBL_FAIL( "Normalise() not defined for this type." );
	}
	
	template< typename T>
	inline const typename Vector3<T> Vector3<T>::GetNormalised( void ) const
	{
		CBL_FAIL( "GetNormalise() not defined for this type." );
		return Vector3( *this );
	}
	
	template< typename T>
	inline const Real Vector3<T>::GetLength( void ) const
	{
		return cbl::Math::Sqrt<Real>( GetSquaredLength() );
	}

	template< typename T>
	inline const Real Vector3<T>::GetSquaredLength( void ) const
	{
		return GetDotProduct( *this );
	}
	
	template< typename T>
	inline const Real Vector3<T>::GetDistance( const Vector3 & rhs ) const
	{
		return cbl::Math::Sqrt<Real>( GetSquaredDistance( rhs ) );
	}

	template< typename T>
	inline const Real Vector3<T>::GetSquaredDistance( const Vector3 & rhs ) const
	{
		T x = X - rhs.X;
		T y = Y - rhs.Y;
		T z = Z - rhs.Z;
		return Real( x * x + y * y + z * z );
	}
	
	template< typename T>
	inline const Real Vector3<T>::GetDotProduct( const Vector3 & rhs ) const
	{
		return Real( X * rhs.X + Y * rhs.Y + Z * rhs.Z );
	}

	template< typename T>
	inline const typename Vector3<T> Vector3<T>::GetCrossProduct( const Vector3 & rhs ) const
	{
		return Vector3(
			( Y * rhs.Z - Z * rhs.Y ),
			( Z * rhs.X - X * rhs.Z ),
			( X * rhs.Y - Y * rhs.X )
			);
	}
	
	template< typename T >
	template< typename O >
	inline Vector3<T>::operator Vector3<O> () const
	{
		return typename Vector3<O>( O( X ), O( Y ), O( Z ) );
	}
	
	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector3<T> & vector )
	{
		stream << "(" << vector.X << ", " << vector.Y << ", " << vector.Z << ")";
		return stream;
	}

	/***** Vector3f Definitions *****/

	template<>
	CBL_API void Vector3<Float32>::Normalise( void );

	template<>
	CBL_API const typename Vector3<Float32> Vector3<Float32>::GetNormalised( void ) const;

	template<>
	CBL_API void Vector3<Float64>::Normalise( void );

	template<>
	CBL_API const typename Vector3<Float64> Vector3<Float64>::GetNormalised( void ) const;
}
