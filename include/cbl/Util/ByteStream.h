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
 * @file ByteStream.h
 * @brief Streams integral types to/from a serialised stream.
 */

#ifndef __CBL_BYTESTREAM_H_
#define __CBL_BYTESTREAM_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Thread/Mutex.h"

namespace cbl
{
	//! Byte stream utility class.
	//! Converts integral values into serialised bytes.
	//! WARNING: Does not check for Endian format!
	class CBL_API ByteStream
	{
	/***** Properties *****/
	public:
		GETTER_AUTO( Uint32, Size );
		GETTER_AUTO( Uint32, MaxSize );

		const Char * GetBytes() const;

	/***** Public Methods *****/
	public:
		//! Constructor.
		ByteStream();
		//! Constructor.
		//! @param	buffer	Buffer to copy from.
		//! @Param	size	Size of the buffer.
		ByteStream( const Char * buffer, Int32 size );
		//! Copy constructor.
		ByteStream( const ByteStream & rhs );
		//! Destructor.
		~ByteStream();
		//! Write to byte stream.
		void Write( const Char * src, Uint32 size );
		//! Read from byte stream.
		void Read( Char * dst, Uint32 size );
		//! Read from byte stream into another byte stream.
		void Read( ByteStream & dst, Uint32 size );
		//! Find a specific byte in the stream data.
		//! @return			Returns -1 if not found, otherwise returns
		//!					the position of the first occurence.
		Int32 Find( Char find ) const;
		//! Clear stream data.
		//! Note that this does not actually erase previously written data, but resets
		//! the counters back to 0 to save on performance.
		void Clear( void );
		//! Assignment operator.
		ByteStream & operator = ( const ByteStream & rhs );
		//! Insertion operator. Inserts bytes from an integral value.
		//! @tparam			Type.
		template< typename T >
		ByteStream& operator << ( const T& value );
		//! Insertion operator. Inserts bytes from c-string.
		ByteStream& operator << ( const Char* value );
		//! Insertion operator. Inserts bytes from string.
		ByteStream& operator << ( const String& value );
		//! Extraction operator. Extracts bytes to an integral value.
		//! @tparam			Type.
		template< typename T >
		ByteStream& operator >> ( T & value );
		//! Extraction operator. Extracts bytes to a string.
		ByteStream& operator >> ( String& value );
		//! Gets a value from the stream without removing data.
		//! @tparam			Type.
		//! @param			Reference value to set.
		template< typename T >
		void Peek( T & value ) const;
		
	/***** Private Methods *****/
	private:
		//! Shifts the data to back to the start of the storage array.
		void Compress( void );
		//! Reallocates memory for the byte stream using th specified size.
		void Reallocate( Uint32 size );

	/***** Private Members *****/
	private:
		Char		* mBytes;	//!< Bytes.
		Uint32		mSize;		//!< Current byte stream size.
		Uint32		mMaxSize;	//!< Maximum byte stream size before reallocation.
		Uint32		mStartMarker;
		CBL_MUTEX_DECLARE( mtxRW );
	};

	/***** Template Method Definitions *****/
	template< typename T >
	inline ByteStream& ByteStream::operator << ( const T& value )
	{
		const Char * ptr = reinterpret_cast< const Char * >( &value );
		Write( ptr, sizeof( T ) );

		return *this;
	}

	template< typename T >
	inline ByteStream& ByteStream::operator >> ( T & value )
	{
		Char * ptr = reinterpret_cast< Char * >( &value );
		Read( ptr, sizeof( T ) );

		return *this;
	}

	/***** String serializations *****/
	inline ByteStream& ByteStream::operator << ( const Char* value )
	{
		// We want to write the null character as well.
		Write( value, ::strlen( value ) + 1 );
		return *this;
	}

	inline ByteStream& ByteStream::operator << ( const String& value )
	{
		// We want to write the null character as well.
		Write( value.c_str(), value.length() + 1 );
		return *this;
	}

	inline ByteStream& ByteStream::operator >> ( String& value )
	{
		Int32 size = Find( '\0' );
		if( size > 0 ) {
			value.resize( (size_t)size, '\0' );
			Read( &(value[0]), size );
		}
		return *this;
	}
	
	template< typename T >
	inline void ByteStream::Peek( T & value ) const
	{
		CBL_MUTEX_SCOPEDLOCK( mtxRW );

		Char * ptr = reinterpret_cast< Char * >( &value );
		fread( ptr, GetBytes(), sizeof( T ));
	}
	
	template<>
	ByteStream & ByteStream::operator << ( const ByteStream & rhs );
	
	//! Undefined
	template<>
	ByteStream & ByteStream::operator >> ( const ByteStream & rhs );
}

#endif // __CBL_BYTESTREAM_H_
