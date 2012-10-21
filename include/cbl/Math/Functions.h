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
 * @file Math.h
 * @brief Math functions.
 */

#ifndef __CBL_FUNCTIONS_H_
#define __CBL_FUNCTIONS_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	namespace Math
	{
		/***** Static Variables *****/
		static const Real Pi			= 3.14159265f;
		static const Real PiHalf		= 1.57079633f;
		static const Real DegToRad		= 0.0174532925f;
		static const Real Epsilon		= 0.00048828125f; // 1 / 2048
		static const Real SquareEpsilon	= 2.384185791015625e-7f; // ( Epsilon * Epsilon )

		/***** Function Declarations *****/
		#define isnan _isnan
		//! Get an absolute value.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Absolute value.
		template< typename T, typename U >
		const T Abs( U value );
		//! Get the square root of a number.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Square root value.
		template< typename T, typename U >
		const T Sqrt( U value );
		//! Get the ceiling of a value.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Rounded value.
		template< typename T, typename U >
		const T Ceil( U value );
		//! Get the floor of a value.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Floored value.
		template< typename T, typename U >
		const T Floor( U value );
		//! Get the minimum of two values.
		//! @tparam	T	Return/Input type.
		//! @return		Minimum of two values.
		template< typename T >
		const T Min( T lhs, T rhs );
		//! Get the maximum of two values.
		//! @tparam	T	Return/Input type.
		//! @return		Maximum of two values.
		template< typename T >
		const T Max( T lhs, T rhs );
		//! Clamps a value to specified minimum and maximum values.
		//! @tparam	T	Return type.
		//! @param	dst	Destination.
		template< typename T >
		const T Clamp( T min, T max, T value );
		//! Get the nearest rounded value.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Rounded value.
		template< typename T, typename U >
		const T Round( U value );
		//! Get the sine of an angle in radians.
		template< typename T, typename U >
		const T Sin( U value );
		//! Get the cosine of an angle in radians.
		template< typename T, typename U >
		const T Cos( U value );
		//! Get the tangent of an angle in radians.
		template< typename T, typename U >
		const T Tan( U value );
		//! Get the arc-tangent of an angle in radians.
		template< typename T, typename U >
		const T Atan( U value );
		//! Get the arc-tangent of two sides.
		template< typename T, typename U >
		const T Atan2( U y, U x );
		//! Raise to power.
		//! @tparam	T	Return type.
		//! @return		Number raised to power.
		template< typename T, typename U, typename V >
		const T Power( U base, V exponent );
		//! Geometric sum:
		//! s = ( 1 - r ^ ( n + 1 ) ) / ( 1 - r )
		//! i.e. s = 1 + r ^ 1 + r ^ 2 + ... + r ^ n
		//! @tparam	T	Return type.
		//! @return		Geometric series sum.
		template< typename T, typename U, typename V >
		const T GeometricSum( U r, V n );
		//! Get the smallest power 2 value that's larger than the specified number.
		//! @tparam	T	Return type.
		//! @tparam	U	Input type.
		//! @return		Smallest power 2 value that's larger than the specified number.
		template< typename T, typename U >
		const T ClosestPower2( U value );

		/***** Inline Functions *****/
		template< typename T, typename U >
		inline const T Abs( U value ) {
			return static_cast< T >( value < 0 ? -value : value );
		}
		
		template< typename T, typename U >
		inline const T Sqrt< T >( U value ) {
			return static_cast< T >( ::sqrt( value ) );
		}
		
		template< typename T, typename U >
		inline const T Ceil< T >( U value ) {
			return static_cast< T >( ::ceil( value ) );
		}
		
		template< typename T, typename U >
		inline const T Floor( U value ) {
			return static_cast< T >( ::floor( value ) );
		}

		template< typename T >
		inline const T Min( T lhs, T rhs ) {
			return lhs < rhs ? lhs : rhs;
		}

		template< typename T >
		inline const T Max( T lhs, T rhs ) {
			return lhs > rhs ? lhs : rhs;
		}

		template< typename T >
		inline const T Clamp( T min, T max, T value ) {
			if( max < min ) std::swap( min, max );
			return value < min ? min : value > max ? max : value;
		}
		
		template< typename T, typename U >
		inline const T Round< T >( U value ) {
			return static_cast< T >( Floor< U, U >( value < 0.0f ? value - 0.5f : value + 0.5f ) );
		}
		
		template< typename T, typename U >
		inline const T Sin< T >( U value ) {
			return static_cast< T >( ::sin( value ) );
		}
		
		template< typename T, typename U >
		inline const T Cos< T >( U value ) {
			return static_cast< T >( ::cos( value ) );
		}
		
		template< typename T, typename U >
		inline const T Tan< T >( U value ) {
			return static_cast< T >( ::tan( value ) );
		}
		
		template< typename T, typename U >
		inline const T Atan< T >( U value ) {
			return static_cast< T >( ::atan( value ) );
		}
		
		template< typename T, typename U >
		inline const T Atan2< T >( U y, U x ) {
			return static_cast< T >( ::atan2( y, x ) );
		}

		template< typename T, typename U, typename V >
		inline const T Power( U base, V exponent ) {
			return static_cast< T >( ::pow( static_cast< Float64 >(base), static_cast< Float64 >( exponent ) ) );
		}
		
		template< typename T, typename U, typename V >
		inline const T GeometricSum( U r, V n ) {
			return static_cast< T >( ( Power<cbl::Uint32>( r, n + 1 ) - 1 ) / ( r - 1 ) );
		}
		
		template< typename T, typename U >
		inline const T ClosestPower2( U value ) {
			cbl::Uint32 v = cbl::Uint32( value ) - 1;
			v |= v >> 1;
			v |= v >> 2;
			v |= v >> 4;
			v |= v >> 8;
			v |= v >> 16;
			return T(v+1);
		}

        //! Check for most significant bit in an integer
        inline unsigned int MostSigBit32(register Uint32 x)
        {
            x |= (x >> 1);
            x |= (x >> 2);
            x |= (x >> 4);
            x |= (x >> 8);
            x |= (x >> 16);
            return(x & ~(x >> 1));
        }

        inline unsigned int NumOnesInBit32(register Uint32 x)
        {
            x -= ((x >> 1) & 0x55555555);
            x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
            x = (((x >> 4) + x) & 0x0f0f0f0f);
            x += (x >> 8);
            x += (x >> 16);
            return(x & 0x0000003f);
        }

        inline unsigned int LastZeroBitPos(register Uint32 x)
        {
            x |= (x >> 1);
            x |= (x >> 2);
            x |= (x >> 4);
            x |= (x >> 8);
            x |= (x >> 16);
            return(32 - NumOnesInBit32(x));
        }
	}
}

#endif // __CBL_FUNCTIONS_H_
