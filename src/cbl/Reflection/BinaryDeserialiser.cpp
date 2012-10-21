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
 * @file BinaryDeserialiser.cpp
 * @brief Binary deserialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Reflection/BinaryDeserialiser.h"

using namespace cbl;

bool BinaryDeserialiser::IsStreamEnded( void ) const
{
	Uint32 typeHash = 0;
	(*(std::istream*)mStream).read( (Char*)(&typeHash), sizeof( Uint32 ) );

	std::streamsize size = (*(std::istream*)mStream).gcount();
	for( std::streamsize i = 0; i < size; ++i ) {
		(*(std::istream*)mStream).unget();
	}

	return ( typeHash == 0 ) || ( size != sizeof( Uint32 ) );
}

HashValue BinaryDeserialiser::GetNextType( void ) const
{
	Uint32 typeHash = 0;
	(*(std::istream*)mStream).read( (Char*)(&typeHash), sizeof( Uint32 ) );

	std::streamsize size = (*(std::istream*)mStream).gcount();
	for( std::streamsize i = 0; i < size; ++i ) {
		(*(std::istream*)mStream).unget();
	}

	return size != sizeof( Uint32 ) ? 0 : typeHash;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::Initialise( StreamPtr s, const Type*, void* )
{
	return s;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::Shutdown( StreamPtr s, const Type*, void* )
{
	return s;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::TraverseStream( StreamPtr s, const Char* path )
{
	size_t size = strlen( path ) + 1;
	Char* p = new Char[ size ];
	(*(std::istream*)s).read( p, size );

	return strcmp( p, path ) == 0 ? s : NULL;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::OnContainer( StreamPtr s, Uint32& size )
{
	(*(std::istream*)s).read( (Char*)(&size), sizeof( Uint32 ) );

	if( (*(std::istream*)s).gcount() != sizeof( Uint32 ) )
		return NULL;

	return s;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::OnType( StreamPtr s, HashValue& type )
{
	(*(std::istream*)s).read( (Char*)(&type), sizeof( HashValue ) );

	if( (*(std::istream*)s).gcount() != sizeof( HashValue ) )
		return NULL;

	return s;
}

BinaryDeserialiser::StreamPtr BinaryDeserialiser::OnValue( StreamPtr s, const Type* type, void* obj, const FieldAttr* attr )
{
	if( type->FromString ) {
		// Only read the next byte if this type is not a string type.
		bool isStr = type->Name == cbl::TypeCName<String>();
		if( isStr ) {
			// Read string size.
			cbl::Uint32 len = 0;
			CBL_ASSERT_FALSE( (*(std::istream*)s).eof() );
			(*(std::istream*)s).read( (Char*)(&len), sizeof(Uint32) );
			// Read string.
			Char* str = new Char[len];
			(*(std::istream*)s).read( str, len );
			// Assign read value to our string.
			((String*)obj)->assign( str, len );
			CBL_DELETE_ARRAY( str );
		} else {
			Uchar useStr = 0;
			(*(std::istream*)s).read( (Char*)(&useStr), sizeof( Uchar ) );

			if( useStr != 0 ) {
				Char c = 0;
				String str;
				(*(std::istream*)s).get( c );
				while( (*(std::istream*)s).good() && c != '\0' ) {
					str += c;
					(*(std::istream*)s).get( c );
				}
				type->FromString( str, type, obj, attr );
			} else {
				(*(std::istream*)s).read( (Char*)(obj), type->Size );
			}
		}

		// We've handled the data.
		return NULL;
	}

	return s;
}

void BinaryDeserialiser::OnStreamSet( void )
{
}
