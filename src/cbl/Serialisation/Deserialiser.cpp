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
 * @file Deserialiser.cpp
 * @brief Abstract deserialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers//
#include "cbl/Serialisation/Deserialiser.h"
#include "cbl/Serialisation/Serialiser.h"

using namespace cbl;

Deserialiser::Deserialiser()
: mStream( NULL )
{
}

Deserialiser::~Deserialiser()
{
}

Deserialiser& Deserialiser::SetStream( StreamPtr stream, const Char* start_path )
{
	mStream = stream;

	// Handle the stream paths.
	if( mStream ) {
		if( start_path ) {
			std::vector<String> spaths = Serialiser::SplitStreamPath( start_path );
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

bool Deserialiser::Deserialise( const Type* type, void*& obj )
{
	if( !mStream ) {
		LOG_ERROR( "No stream to serialise to." );
		return false;
	}
	if( !type ) {
		LOG_ERROR( "No type specified." );
		return false;
	}

	if( obj && type->IsEntity && &((EntityPtr)obj)->GetType() )
		type = &((EntityPtr)obj)->GetType();

	if( StreamPtr s = Initialise( mStream, type, obj ) ) {
		s = DoDeserialise( s, type, obj, NULL, true );
		mStream = Shutdown( mStream, type, obj );
		return true;
	}

	return false;
}