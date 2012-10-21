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
 * @file WeakPtr.h
 * @brief Weak pointer.
 */

#ifndef __CBL_WEAKPTR_H_
#define __CBL_WEAKPTR_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/SharedPtr.h"

namespace cbl
{
	//! @brief Weak pointer to be used in conjunction with the SharedPtr.
	//!
	//! Usage:
	//! SharedPtr<int> ptr( new int(1) );
	//! WeakPtr<int> weakPtr( ptr );
	//! 
	//! SharedPtr<int> grab = weakPtr.Lock();
	//! // Do something.
	//! if( grab )
	//!	    std::cout << "Pointer exists!";
	//! else
	//!		std::cout << "Pointer invalid!";
	template< typename T >
	class WeakPtr
	{
	/***** Types *****/
	public:
		//! Pointer type.
		typedef T		Type;

	/***** Properties *****/
	public:
		//! Returns the weak reference count.
		Int32 Count( void ) const;

	/***** Public Methods *****/
	public:
		//! Constructor. Initialises pointer to NULL.
		WeakPtr();
		//! Copy constructor.
		//! @param	rhs		Weak pointer to copy from.
		WeakPtr( const WeakPtr & ptr );
		//! Copy constructor for different weak pointer types.
		//! This is useful for manipulating weak pointers of inherited types.
		//! @param	rhs		Weak pointer to copy from.
		template< typename U >
		WeakPtr( const WeakPtr<U> & ptr );
		//! Copy constructor for shared pointer types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	rhs		Shared pointer to copy from.
		template< typename U >
		WeakPtr( const SharedPtr<U> & ptr );
		//! Destructor.
		~WeakPtr();
		//! Assignment operator.
		//! @param	rhs		Weak pointer to assign from.
		WeakPtr & operator = ( const WeakPtr & rhs );
		//! Assignment operator for different weak pointer types.
		//! This is useful for manipulating weak pointers of inherited types.
		//! @param	rhs		Weak pointer to assign from.
		template< typename U >
		WeakPtr & operator = ( const WeakPtr<U> & rhs );
		//! Assignment operator for different shared pointer types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	rhs		Weak pointer to assign from.
		template< typename U >
		WeakPtr & operator = ( const SharedPtr<U> & rhs );
		//! Lock the weak pointer to prevent it from being deleted while being used.
		//! This is the only way to access the weak pointer.
		//! @return			Shared pointer to the weak reference.
		SharedPtr<T> Lock( void ) const;
		//! Lock the weak pointer to prevent it from being deleted while being used.
		//! This is the only way to access the weak pointer.
		//! @return			Shared pointer to the weak reference.
		template< typename U >
		SharedPtr<U> Lock( void ) const;
		//! Boolean operator to perform pointer validation checks: if( mSharedPtr ) ...
		operator bool( void ) const;

	/***** Private Members *****/
	private:
		T				* mPointer;		//!< Pointer to object.
		mutable Int32	* mRefCount;	//!< Reference counter.
		mutable Int32	* mWeakCount;	//!< Weak reference counter.
		template< typename U >
		friend class SharedPtr;			//!< Befriend all shared pointers.
		template< typename U >
		friend class WeakPtr;			//!< Befriend all weak pointers.
	};
	
	/***** Support Functions *****/
	//! Comparison operator.
	//! Checks if the pointer is the same as the specified shared pointer.
	//! @return			Flag indicating if pointers are the same.
	template< typename T, typename U >
	bool operator == ( const WeakPtr<T> & lhs, const WeakPtr<T> & rhs );
	//! Comparison operator.
	//! Checks if the pointer is different from the specified pointer.
	//! @return			Flag indicating if pointers are not the same.
	template< typename T, typename U >
	bool operator != ( const WeakPtr<T> & lhs, const WeakPtr<U> & rhs );
	//! Less-than operator.
	//! Used for STL less-than comparison operations i.e. sorting.
	template< typename T, typename U >
	bool operator < ( const WeakPtr<T> & lhs, const WeakPtr<U> & rhs );
	//! Checks if the pointer is the same as the specified shared pointer.
	//! @return			Flag indicating if pointers are the same.
	template< typename T, typename U >
	bool operator == ( const WeakPtr<T> & lhs, const SharedPtr<T> & rhs );
	//! Comparison operator.
	//! Checks if the pointer is different from the specified pointer.
	//! @return			Flag indicating if pointers are not the same.
	template< typename T, typename U >
	bool operator != ( const WeakPtr<T> & lhs, const SharedPtr<U> & rhs );
	//! Less-than operator.
	//! Used for STL less-than comparison operations i.e. sorting.
	template< typename T, typename U >
	bool operator < ( const WeakPtr<T> & lhs, const SharedPtr<U> & rhs );
	//! Insertion operator for std::ostream.
	//! @param	stream	Output stream.
	//! @param	ptr		The weak pointer.
	template< typename T >
	Ostream & operator << ( Ostream & stream, const WeakPtr<T> & ptr );
}

#include "WeakPtr.inl"

#endif // __CBL_WEAKPTR_H_
