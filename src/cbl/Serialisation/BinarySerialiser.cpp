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
 * @file BinarySerialiser.cpp
 * @brief Binary serialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Serialisation/BinarySerialiser.h"

using namespace cbl;

BinarySerialiser::StreamPtr BinarySerialiser::Initialise( StreamPtr s, const Type*, const void* )
{
	return s;
}

BinarySerialiser::StreamPtr BinarySerialiser::Shutdown( StreamPtr s, const Type*, const void* )
{
	return s;
}

BinarySerialiser::StreamPtr BinarySerialiser::TraverseStream( StreamPtr s, const Char* path )
{
	(*(std::ostream*)s).write( path, strlen( path ) + 1 );
	return s;
}

BinarySerialiser::StreamPtr BinarySerialiser::OnContainer( StreamPtr s, Uint32 size )
{
	(*(std::ostream*)s).write( (Char*)(&size), sizeof( Uint32 ) );
	return s;
}

BinarySerialiser::StreamPtr BinarySerialiser::OnType( StreamPtr s, const Type* type )
{
	(*(std::ostream*)s).write( (Char*)(&type->Name.Hash), sizeof( HashValue ) );
	return s;
}

BinarySerialiser::StreamPtr BinarySerialiser::OnValue( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr )
{
	if( type->ToString ) {
		String str;
		type->ToString( str, type, obj, attr );

		bool isStr = type->Name == cbl::TypeCName<String>();
		if( isStr ) {
			cbl::Uint32 len = str.length();
			(*(std::ostream*)s).write( ((const Char*)&len), sizeof(Uint32) );
			(*(std::ostream*)s).write( str.c_str(), str.length() );
		} else {
			// Output the byte indicating whether the next value is read as a string or bytes.
			Uchar useStr = str.length() < type->Size ? 1 : 0;
			(*(std::ostream*)s).write( (Char*)(&useStr), sizeof( Uchar ) );
			if( useStr ) {
				// Write the string version. Add the \0 character to it.
				(*(std::ostream*)s).write( str.c_str(), str.length()+1 );
			} else {
				(*(std::ostream*)s).write( (Char*)(obj), type->Size );
			}
		}
		// We've handled the data.
		return NULL;
	}

	return s;
}

void BinarySerialiser::OnStreamSet( void )
{
}
