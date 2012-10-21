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
 * @file Vector.inl
 * @brief std::vector replacement.
 */

namespace cbl
{
	template<typename T>
	inline Vector<T>::iterator::iterator( T* _d )
	: _data( _d )
	{
	}

	template<typename T>
	inline T& Vector<T>::operator * ( void )
	{
		return *_data;
	}

	template<typename T>
	inline typename Vector<T>::iterator& Vector<T>::operator ++ ( void )
	{
		++_data;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::operator ++ ( int )
	{
		return iterator( _data++ );
	}

	template<typename T>
	inline typename Vector<T>::iterator& Vector<T>::operator -- ( void )
	{
		--_data;
		return *this;
	}

	template<typename T>
	inline typename Vector<T>::iterator Vector<T>::operator -- ( int )
	{
		return iterator( _data-- );
	}

	template<typename T>
	inline Vector<T>::Vector()
	: mCapacity(0)
	, mSize(0)
	, mData(new T[1])
	{
	}

	template<typename T>
	inline Vector<T>::Vector( size_t n )
	: mCapacity( Math::ClosestPower2<Uint32>(n) )
	, mSize( n )
	, mData( new T[mCapacity+1] )
	{
	}

	template<typename T>
	inline Vector<T>::Vector( const Vector& rhs )
	: mCapacity( rhs.mCapacity )
	, mSize( rhs.mSize )
	, mData( new T[rhs.mCapacity+1] )
	{
		memcpy( mData, rhs.mData, sizeof(T) * mSize );
	}

	template<typename T>
	Vector<T>& Vector<T>::operator = ( const Vector& rhs )
	{
		if( this == &rhs ) return *this;

		if( mCapacity < rhs.mCapacity ) {
			delete [] mData;
			mData = new T[rhs.mCapacity+1];
		}

		mCapacity = rhs.mCapacity;
		mSize = rhs.mSize;
		memcpy( mData, rhs.mData, sizeof(T) * mSize );
	}

	template<typename T>
	inline size_t Vector<T>::size( void ) const
	{
		return mSize;
	}

	template<typename T>
	void Vector<T>::resize( size_t size )
	{
		if( size <= mSize ) return;
		if( size > mCapacity ) {
			mCapacity = Math::ClosestPower2<Uint32>(size);
			T* newData = new T[ mCapacity + 1 ];
			memcpy( newData, mData, sizeof(T) * mSize );
			delete [] mData;
			mData = newData;
		}
		mSize = size;
	}

	template<typename T>
	T& Vector<T>::back(void)
	{

	}

	const T& back(void) const;
	void reserve( void );
}
