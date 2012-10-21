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
 * @file Serialiser.cpp
 * @brief Abstract serialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Serialisation/Serialiser.h"

using namespace cbl;

std::vector<String> Serialiser::SplitStreamPath( const Char* path )
{
	while( *path == '/' ) { ++path; }

	const Char* m = path;

	std::vector<String> result;

	while( *m ) {
		if( *m == '/' ) {
			// If we're not at the same position.
			if( path != m ) result.push_back( String( path, m - path ) );
			// We move the pointer forward until no more slashes are encountered.
			while( *m == '/' ) { ++m; }
			path = m;
		} else {
			++m;
		}
	}

	if( path != m )
		result.push_back( String( path, m - path ) );

	return result;
}

Serialiser::Serialiser()
: mStream( NULL )
{
}

Serialiser::~Serialiser()
{
}

Serialiser& Serialiser::SetStream( StreamPtr stream, const Char* start_path )
{
	mStream = stream;
	// Handle the stream paths.
	if( mStream ) {
		if( start_path ) {
			std::vector<String> spaths = SplitStreamPath( start_path );
			for( size_t i = 0; i < spaths.size(); ++i ) {
				StreamPtr s = TraverseStream( mStream, spaths[i].c_str() );
				if( s == NULL )
					break;
				mStream = s;
			}
		}
		OnStreamSet();
	}

	return *this;
}

Serialiser& Serialiser::Serialise( const Type* type, const void* obj )
{
	if( !mStream ) {
		LOG_ERROR( "No stream to serialise to." );
		return *this;
	}
	if( !type ) {
		LOG_ERROR( "No type specified." );
		return *this;
	}
	if( !obj ) {
		LOG_ERROR( "No object to serialise to." );
		return *this;
	}

	if( type->IsEntity && &((EntityPtr)obj)->GetType() )
		type = &((EntityPtr)obj)->GetType();

	mStream = DoSerialise(
		Initialise( mStream, type, obj ), type, obj, NULL, true );

	mStream = Shutdown( mStream, type, obj );

	return *this;
}
