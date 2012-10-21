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
 * @file Vector2.inl
 * @brief 2D vector inline templated functions.
 */

#include "cbl/Debug/Assert.h"

namespace cbl
{
	/***** Constants Definitions *****/
	template< typename T >
	const typename Vector2<T> Vector2<T>::ZERO		= Vector2<T>( T(0) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::ONE		= Vector2<T>( T(1) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::N_ONE		= Vector2<T>( T(-1) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::UNIT_X	= Vector2<T>( T(1), T(0) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::UNIT_Y	= Vector2<T>( T(0), T(1) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::UNIT_NX	= Vector2<T>( T(-1), T(0) );
	template< typename T >
	const typename Vector2<T> Vector2<T>::UNIT_NY	= Vector2<T>( T(0), T(-1) );

	/***** Inline Methods *****/
	template< typename T >
	inline Vector2<T>::Vector2()
	: X( T(0) ), Y( T(0) )
	{
	}

	template< typename T >
	inline Vector2<T>::Vector2( const T t )
	: X( t ), Y( t )
	{
	}

	template< typename T >
	inline Vector2<T>::Vector2( const T coords[2] )
	: X( coords[0] ), Y( coords[1] )
	{
	}

	template< typename T >
	inline Vector2<T>::Vector2( const Vector2 & rhs )
	: X( rhs.X ), Y( rhs.Y )
	{
	}

	template< typename T >
	inline Vector2<T>::Vector2( const T x, const T y )
	: X( x ), Y( y )
	{
	}
	
	template< typename T >
	inline const T Vector2<T>::operator [] ( const size_t index ) const
	{
		CBL_ASSERT( index < 2, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( &X + index );
	}

	template< typename T >
	inline T & Vector2<T>::operator [] ( const size_t index )
	{
		CBL_ASSERT( index < 2, "Accessing beyond index bounds." ); // Halt the program if this exceeds.
		// For fast variable access.
		return *( (&X) + index );
	}
	
	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator + ( const Vector2 & rhs ) const
	{
		return Vector2( X + rhs.X, Y + rhs.Y );
	}

	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator - ( const Vector2 & rhs ) const
	{
		return Vector2( X - rhs.X, Y - rhs.Y );
	}

	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator - ( void ) const
	{
		return Vector2( -X, -Y );
	}

	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator * ( const Real scale ) const
	{
		return Vector2( T( X * scale ), T( Y * scale ) );
	}

	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator / ( const Real scale ) const
	{
		return Vector2( T( X / scale ), T( Y / scale ) );
	}
	
	template< typename T >
	inline const typename Vector2<T> Vector2<T>::operator * ( const Vector2 & rhs ) const
	{
		return Vector2( X * rhs.X, Y * rhs.Y );
	}
	
	template< typename T >
	inline typename Vector2<T> & Vector2<T>::operator = ( const Vector2 & rhs )
	{
		X = rhs.X;
		Y = rhs.Y;
		return *this;
	}

	template< typename T >
	inline typename Vector2<T> & Vector2<T>::operator += ( const Vector2 & rhs )
	{
		X += rhs.X;
		Y += rhs.Y;
		return *this;
	}
	
	template< typename T >
	inline typename Vector2<T> & Vector2<T>::operator -= ( const Vector2 & rhs )
	{
		X -= rhs.X;
		Y -= rhs.Y;
		return *this;
	}

	template< typename T >
	inline typename Vector2<T> & Vector2<T>::operator *= ( const Real scale )
	{
		X = T( X * scale );
		Y = T( Y * scale );
		return *this;
	}

	template< typename T >
	inline typename Vector2<T> & Vector2<T>::operator /= ( const Real scale )
	{
		X = T( X / scale );
		Y = T( Y / scale );
		return *this;
	}
	
	template< typename T >
	inline const bool Vector2<T>::operator == ( const Vector2 & rhs ) const
	{
		return ( X == rhs.X && Y == rhs.Y );
	}

	template< typename T >
	inline const bool Vector2<T>::operator != ( const Vector2 & rhs ) const
	{
		return ( X != rhs.X || Y != rhs.Y );
	}

	template< typename T >
	inline void Vector2<T>::Swap( Vector2 & rhs )
	{
		std::swap( X, rhs.X );
		std::swap( Y, rhs.Y );
	}
	
	template< typename T >
	inline void Vector2<T>::Set( T x, T y )
	{
		X = x;
		Y = y;
	}

	template< typename T >
	inline void Vector2<T>::Normalise( void )
	{
		CBL_FAIL( "Normalise() not defined for this type." );
	}
	
	template< typename T >
	inline const typename Vector2<T> Vector2<T>::GetNormalised( void ) const
	{
		CBL_FAIL( "GetNormalise() not defined for this type." );
		return Vector2<T>( *this );
	}
	
	template< typename T >
	inline const Real Vector2<T>::GetLength( void ) const
	{
		return cbl::Math::Sqrt<Real>( GetSquaredLength() );
	}

	template< typename T >
	inline const Real Vector2<T>::GetSquaredLength( void ) const
	{
		return GetDotProduct( *this );
	}
	
	template< typename T >
	inline const Real Vector2<T>::GetDistance( const Vector2 & rhs ) const
	{
		return cbl::Math::Sqrt<Real>( GetSquaredDistance( rhs ) );
	}

	template< typename T >
	inline const Real Vector2<T>::GetSquaredDistance( const Vector2 & rhs ) const
	{
		T x = X - rhs.X;
		T y = Y - rhs.Y;
		return Real( x * x + y * y );
	}
	
	template< typename T >
	inline const Real Vector2<T>::GetDotProduct( const Vector2 & rhs ) const
	{
		return Real( X * rhs.X + Y * rhs.Y );
	}

	template< typename T >
	inline const Real Vector2<T>::GetCrossProduct( const Vector2 & rhs ) const
	{
		return Real( X * rhs.Y - Y * rhs.X );
	}
	
	template< typename T >
	template< typename O >
	inline Vector2<T>::operator Vector2<O> () const
	{
		return typename Vector2<O>( O( X ), O( Y ) );
	}

	template< typename T >
	std::ostream & operator << ( std::ostream & stream, const Vector2<T> & vector )
	{
		stream << "(" << vector.X << ", " << vector.Y << ")";
		return stream;
	}

	/***** Vector2f Specialisation Declarations *****/
	template<>
	CBL_API void Vector2<Float32>::Normalise( void );

	template<>
	CBL_API const typename Vector2<Float32> Vector2<Float32>::GetNormalised( void ) const;

	template<>
	CBL_API void Vector2<Float64>::Normalise( void );
	
	template<>
	CBL_API const typename Vector2<Float64> Vector2<Float64>::GetNormalised( void ) const;
}
