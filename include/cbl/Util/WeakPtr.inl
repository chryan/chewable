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
 * @file WeakPtr.inl
 * @brief Weak pointer inline methods.
 */

namespace cbl
{
	template< typename T >
	Int32 WeakPtr<T>::Count( void ) const
	{
		return *mWeakCount;
	}

	template< typename T >
	inline WeakPtr<T>::WeakPtr()
		: mPointer( NULL )
		, mRefCount( new Int32(0) )
		, mWeakCount( new Int32(1) )
	{
	}

	template< typename T >
	inline WeakPtr<T>::WeakPtr( const WeakPtr & ptr )
		: mPointer( ptr.mPointer )
		, mRefCount( ptr.mRefCount )
		, mWeakCount( &(++*ptr.mWeakCount) )
	{
	}

	template< typename T >
	template< typename U >
	inline WeakPtr<T>::WeakPtr( const WeakPtr<U> & ptr )
		: mPointer( static_cast<T*>( ptr.mPointer ) )
		, mRefCount( ptr.mRefCount )
		, mWeakCount( &(++*ptr.mWeakCount) )
	{
	}

	template< typename T >
	template< typename U >
	inline WeakPtr<T>::WeakPtr( const SharedPtr<U> & ptr )
		: mPointer( static_cast<T*>( ptr.mPointer ) )
		, mRefCount( ptr.mRefCount )
		, mWeakCount( &(++*ptr.mWeakCount) )
	{
	}

	template< typename T >
	inline WeakPtr<T>::~WeakPtr()
	{
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}
	}
	

	template< typename T >
	inline WeakPtr<T> & WeakPtr<T>::operator = ( const WeakPtr & rhs )
	{
		if( &rhs != this )
		{
			if( --*mWeakCount == 0 )
			{
				delete mRefCount;
				delete mWeakCount;
			}

			mPointer	= rhs.mPointer;
			mRefCount	= rhs.mRefCount;
			mWeakCount	= &(++*rhs.mWeakCount);
		}

		return *this;
	}

	template< typename T >
	template< typename U >
	inline WeakPtr<T> & WeakPtr<T>::operator = ( const WeakPtr<U> & rhs )
	{
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}

		mPointer	= rhs.mPointer;
		mRefCount	= rhs.mRefCount;
		mWeakCount	= &(++*rhs.mWeakCount);

		return *this;
	}

	template< typename T >
	template< typename U >
	inline WeakPtr<T> & WeakPtr<T>::operator = ( const SharedPtr<U> & rhs )
	{
		if( --*mWeakCount == 0 )
		{
			delete mRefCount;
			delete mWeakCount;
		}

		mPointer	= rhs.mPointer;
		mRefCount	= rhs.mRefCount;
		mWeakCount	= &(++*rhs.mWeakCount);
		return *this;
	}
	
	template< typename T >
	inline SharedPtr<T> WeakPtr<T>::Lock( void ) const
	{
		if( *mRefCount == 0 )
			return SharedPtr<T>();

		return SharedPtr<T>( *this );
	}

	template< typename T >
	template< typename U >
	inline SharedPtr<U> WeakPtr<T>::Lock( void ) const
	{
		if( *mRefCount == 0 )
			return SharedPtr<U>();

		return SharedPtr<U>( *this );
	}
	
	template< typename T >
	WeakPtr<T>::operator bool( void ) const
	{
		return ( *mRefCount > 0 );
	}

	template< typename T, typename U >
	bool operator == ( const WeakPtr<T> & lhs, const WeakPtr<T> & rhs )
	{
		return ( lhs.Lock() == rhs.Lock() );
	}

	template< typename T, typename U >
	bool operator != ( const WeakPtr<T> & lhs, const WeakPtr<U> & rhs )
	{
		return ( lhs.Lock() != rhs.Lock() );
	}

	template< typename T, typename U >
	bool operator < ( const WeakPtr<T> & lhs, const WeakPtr<U> & rhs )
	{
		return ( lhs.Lock() < rhs.Lock() );
	}

	template< typename T, typename U >
	bool operator == ( const WeakPtr<T> & lhs, const SharedPtr<T> & rhs )
	{
		return ( lhs.Lock() == rhs );
	}

	template< typename T, typename U >
	bool operator != ( const WeakPtr<T> & lhs, const SharedPtr<U> & rhs )
	{
		return ( lhs.Lock() != rhs );
	}

	template< typename T, typename U >
	bool operator < ( const WeakPtr<T> & lhs, const SharedPtr<U> & rhs )
	{
		return ( lhs.Lock() < rhs );
	}

	template< typename T >
	Ostream & operator << ( Ostream & stream, const WeakPtr<T> & ptr )
	{
		SharedPtr<T> s = ptr.Lock();
		stream << ( s ? s : "NULL" );
		return stream;
	}
}