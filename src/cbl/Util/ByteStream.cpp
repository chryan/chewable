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
 * @file ByteStream.cpp
 * @brief Streams integral types to/from a serialised stream.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Util/ByteStream.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

using namespace cbl;

ByteStream::ByteStream()
: mBytes( NULL )
, mSize( 0 )
, mMaxSize( 4096 )
, mStartMarker( 0 )
{
	mBytes = new Char[ mMaxSize ];
}

ByteStream::~ByteStream()
{
	CBL_DELETE_ARRAY( mBytes );
}

ByteStream::ByteStream( const Char * buffer, Int32 size )
	: mBytes( NULL ),
	mSize( size ),
	mMaxSize( 4096 ),
	mStartMarker( 0 )
{
	while( mMaxSize < mSize )
		mMaxSize *= 2;

	mBytes = new Char[ mMaxSize ];
	memcpy( mBytes, buffer, size );
}

ByteStream::ByteStream( const ByteStream & rhs )
	: mBytes( NULL ),
	mSize( rhs.mSize ),
	mMaxSize( rhs.mMaxSize ),
	mStartMarker( 0 )
{
	mBytes = new Char[ mMaxSize ];
	memset( mBytes, 0, mMaxSize );
	memcpy( mBytes, rhs.mBytes + rhs.mStartMarker, mSize );
}

const Char * ByteStream::GetBytes() const
{
	return ( mBytes + mStartMarker );
}

void ByteStream::Write( const Char * src, Uint32 size )
{
	Uint32 newSize = mSize + size;
	if( mStartMarker + newSize > mMaxSize )
		Compress();
	if( newSize > mMaxSize )
		Reallocate( mMaxSize * 2 );

	memcpy( mBytes + mStartMarker + mSize, src, size );
	mSize = newSize;
}

void ByteStream::Read( Char * dst, Uint32 size )
{
	CBL_ASSERT( size <= mSize, "Read access error." );
	CBL_ASSERT( mStartMarker + size <= mMaxSize, "Read access error." );
	memcpy( dst, ( mBytes + mStartMarker ), size );
	mStartMarker += size;
	mSize -= size;
}

void ByteStream::Read( ByteStream & dst, Uint32 size )
{
	CBL_ASSERT( size <= mSize, "Read access error." );
	CBL_ASSERT( mStartMarker + size <= mMaxSize, "Read access error." );
	dst.Write( ( mBytes + mStartMarker ), size );
	mStartMarker += size;
	mSize -= size;
}

Int32 ByteStream::Find( Char find ) const
{
	for( Uint32 i = 0; i < mSize; ++i )
	{
		if( mBytes[i+mStartMarker] == find )
			return i;
	}
	return -1;
}

void ByteStream::Clear( void )
{
	mStartMarker = 0;
	mSize = 0;
}

ByteStream & ByteStream::operator = ( const ByteStream & rhs )
{
	if( &rhs != this )
	{
		mSize = 0;
		mStartMarker = 0;
		Write( rhs.GetBytes(), rhs.GetSize() );
	}
	
	return *this;
}

void ByteStream::Compress( void )
{
	for( Uint32 i = 0; i < mSize; ++i )
	{
		mBytes[i] = mBytes[i + mStartMarker];
	}
	mStartMarker = 0;
}

void ByteStream::Reallocate( Uint32 size )
{
	mMaxSize = size;
	Char * tmp = new Char[ mMaxSize ];
	memcpy( tmp, mBytes, mSize );

	CBL_DELETE_ARRAY( mBytes );
	mBytes = tmp;
}

template<>
ByteStream & ByteStream::operator << ( const ByteStream & rhs )
{
	Write( rhs.mBytes, rhs.mSize );
	return *this;
}
