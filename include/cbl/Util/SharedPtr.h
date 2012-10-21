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
 * @file SharedPtr.h
 * @brief Shared pointer.
 */

#ifndef __CBL_SHAREDPTR_H_
#define __CBL_SHAREDPTR_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	// Forward declarations
	template< typename T > class WeakPtr;

	//! @brief The shared pointer is a reference counted smart pointer which deletes objects when
	//! it is no longer being referenced.
	template< typename T >
	class SharedPtr
	{
	/***** Types *****/
	public:
		//! Pointer type.
		typedef T		Type;

	/***** Properties *****/
	public:
		//! Returns the reference count.
		Int32 Count( void ) const;

	/***** Public Methods *****/
	public:
		//! Constructor. Initialises pointer to NULL.
		SharedPtr();
		//! Constructor.
		//! @param	ptr		Pointer to object.
		explicit SharedPtr( T * ptr );
		//! Constructor for different types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	ptr		Pointer to object.
		template< typename U >
		explicit SharedPtr( U * ptr );
		//! Copy constructor.
		//! @param	rhs		Shared pointer to copy from.
		SharedPtr( const SharedPtr & rhs );
		//! Copy constructor for different shared pointer types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	rhs		Shared pointer to copy from.
		template< typename U >
		SharedPtr( const SharedPtr<U> & rhs );
		//! Copy constructor for weak pointer types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	rhs		Shared pointer to copy from.
		template< typename U >
		SharedPtr( const WeakPtr<U> & rhs );
		//! Destructor.
		~SharedPtr();
		//! Assignment operator.
		//! @param	rhs		Shared pointer to assign from.
		SharedPtr & operator = ( const SharedPtr & rhs );
		//! Assignment operator for different shared pointer types.
		//! This is useful for manipulating shared pointers of inherited types.
		//! @param	rhs		Shared pointer to assign from.
		template< typename U >
		SharedPtr & operator = ( const SharedPtr<U> & rhs );
		//! Dereference operator.
		//! @return			Reference to object.
		T & operator * () const;
		//! Pointer operator.
		//! @return			Pointer to object.
		T * operator->() const;
		//! Get the pointer.
		//! @return			Pointer to object.
		T * Get() const;
		//! Reset the shared pointer.
		void Reset( T * ptr );
		//! Reset the shared pointer.
		template< typename U >
		void Reset( const SharedPtr<U> & rhs );
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
	bool operator == ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs );
	//! Comparison operator.
	//! Checks if the pointer is different from the specified pointer.
	//! @return			Flag indicating if pointers are not the same.
	template< typename T, typename U >
	bool operator != ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs );
	//! Less-than operator.
	//! Used for STL less-than comparison operations i.e. sorting.
	template< typename T, typename U >
	bool operator < ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs );
	//! Checks if the pointer is the same as the specified shared pointer.
	//! @return			Flag indicating if pointers are the same.
	template< typename T, typename U >
	bool operator == ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs );
	//! Comparison operator.
	//! Checks if the pointer is different from the specified pointer.
	//! @return			Flag indicating if pointers are not the same.
	template< typename T, typename U >
	bool operator != ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs );
	//! Less-than operator.
	//! Used for STL less-than comparison operations i.e. sorting.
	template< typename T, typename U >
	bool operator < ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs );
	//! Insertion operator for std::ostream.
	//! @param	stream	Output stream.
	//! @param	ptr		The shared pointer.
	template< typename T >
	Ostream & operator << ( Ostream & stream, const SharedPtr<T> & ptr );
}

#include "SharedPtr.inl"

#endif // __CBL_SHAREDPTR_H_
