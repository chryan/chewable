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
 * @brief Shared pointer method definitions.
 */

namespace cbl
{
	/***** Template Method Definitions *****/
	template< typename T >
	inline Int32 SharedPtr<T>::Count() const
	{
		return *mRefCount;
	}

	template< typename T >
	inline SharedPtr<T>::SharedPtr()
		: mPointer( NULL )
		, mRefCount( new Int32(1) )
		, mWeakCount( new Int32(1) )
	{
	}
	
	template< typename T >
	inline SharedPtr<T>::SharedPtr( T * ptr )
		: mPointer( ptr )
		, mRefCount( new Int32(1) )
		, mWeakCount( new Int32(1) )
	{
	}
	
	template< typename T >
	template< typename U >
	inline SharedPtr<T>::SharedPtr( U * ptr )
		: mPointer( static_cast<T*>( ptr ) )
		, mRefCount( new Int32(1) )
		, mWeakCount( new Int32(1) )
	{
	}
	
	template< typename T >
	inline SharedPtr<T>::SharedPtr( const SharedPtr & rhs )
		: mPointer( rhs.mPointer )
		, mRefCount( &(++*rhs.mRefCount) )
		, mWeakCount( &(++*rhs.mWeakCount) )
	{
	}

	template< typename T >
	template< typename U >
	inline SharedPtr<T>::SharedPtr( const SharedPtr<U> & rhs )
		: mPointer( static_cast<T*>( rhs.mPointer ) )
		, mRefCount( &(++*rhs.mRefCount) )
		, mWeakCount( &(++*rhs.mWeakCount) )
	{
	}
	
	template< typename T >
	template< typename U >
	inline SharedPtr<T>::SharedPtr( const WeakPtr<U> & rhs )
		: mPointer( static_cast<T*>( rhs.mPointer ) )
		, mRefCount( &(++*rhs.mRefCount) )
		, mWeakCount( &(++*rhs.mWeakCount) )
	{
	}
	
	template< typename T >
	inline SharedPtr<T>::~SharedPtr()
	{
		if( --*mRefCount == 0 )
			delete mPointer;
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}
	}
	
	template< typename T >
	inline SharedPtr<T> & SharedPtr<T>::operator = ( const SharedPtr & rhs )
	{
		return operator=<T>( rhs );
	}

	template< typename T >
	template< typename U >
	inline SharedPtr<T> & SharedPtr<T>::operator = ( const SharedPtr<U> & rhs )
	{
		if( &rhs != this && rhs.mPointer != mPointer )
		{
			if( --*mRefCount == 0 )
				delete mPointer;
			if( --*mWeakCount == 0 )
			{
				delete mRefCount;
				delete mWeakCount;
			}

			mPointer	= static_cast<T*>( rhs.mPointer );
			mRefCount	= &(++*rhs.mRefCount);
			mWeakCount	= &(++*rhs.mWeakCount);
		}

		return *this;
	}

	template< typename T >
	inline typename SharedPtr<T>::Type & SharedPtr<T>::operator * () const
	{
		return *mPointer;
	}
	
	template< typename T >
	inline typename SharedPtr<T>::Type * SharedPtr<T>::operator->() const
	{
		return mPointer;
	}

	template< typename T >
	inline typename SharedPtr<T>::Type * SharedPtr<T>::Get() const
	{
		return mPointer;
	}

	template< typename T >
	void SharedPtr<T>::Reset( T * ptr )
	{
		if( --*mRefCount == 0 )
			delete mPointer;
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}

		mPointer	= static_cast<T*>( ptr );
		mRefCount	= new Int32(1);
		mWeakCount	= new Int32(1);
	}

	template< typename T >
	template< typename U >
	void SharedPtr<T>::Reset( const SharedPtr<U> & rhs )
	{
		if( --*mRefCount == 0 )
			delete mPointer;
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}
		
		mPointer	= static_cast<T*>( rhs.mPointer );
		mRefCount	= &(++*rhs.mRefCount);
		mWeakCount	= &(++*rhs.mWeakCount);
	}
	
	template< typename T >
	inline SharedPtr<T>::operator bool( void ) const
	{
		return ( mPointer != NULL );
	}
	
	template< typename T, typename U >
	inline bool operator == ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs )
	{
		return ( lhs.Get() == rhs.Get() );
	}

	template< typename T, typename U >
	inline bool operator != ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs )
	{
		return ( lhs.Get() != rhs.Get() );
	}
	
	template< typename T, typename U >
	inline bool operator < ( const SharedPtr<T> & lhs, const SharedPtr<U> & rhs )
	{
		return ( lhs.Get() < rhs.Get() );
	}
	
	template< typename T, typename U >
	inline bool operator == ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs )
	{
		return ( lhs.Get() == rhs.Lock().Get() );
	}

	template< typename T, typename U >
	inline bool operator != ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs )
	{
		return ( lhs.Get() != rhs.Lock().Get() );
	}
	
	template< typename T, typename U >
	inline bool operator < ( const SharedPtr<T> & lhs, const WeakPtr<U> & rhs )
	{
		return ( lhs.Get() < rhs.Lock().Get() );
	}
	
	template< typename T >
	inline Ostream & operator << ( Ostream & stream, const SharedPtr<T> & ptr )
	{
		stream << *ptr;
		return stream;
	}
}