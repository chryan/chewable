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
 * @file Serialiser.h
 * @brief Abstract serialiser class.
 */

#ifndef __CBL_SERIALISER_H_
#define __CBL_SERIALISER_H_

// Chewable Headers//
#include "cbl/Chewable.h"

namespace cbl
{
	//! Base serialiser class.
	class CBL_API Serialiser
	{
	/***** Types *****/
	public:
		typedef void*		StreamPtr;	//!< Stream pointer type.
		
	/***** Public Static Methods *****/
	public:
		//! Split the specified traversal path separated by slashes (/).
		//! Passing in Lorem/Ipsum will push Lorem and Ipsum onto the returning vector.
		//! @param	path	Stream path.
		//! @return			Vector of path strings.
		static std::vector<String> SplitStreamPath( const Char* path );
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		Serialiser();
		//! Destructor.
		virtual ~Serialiser();
		//! Set serialiser stream.
		//! @tparam	SERIALISER_TYPE	Serialise stream type.
		//! @param	stream			Serialiser stream reference.
		//! @param	start_path		Serialiser start path.
		//! @return					This.
		template< typename SERIALISER_TYPE >
		Serialiser& SetStream( SERIALISER_TYPE& stream, const Char* start_path = NULL );
		//! Set serialiser stream.
		//! @param	stream			Serialiser stream pointer.
		//! @param	start_path		Serialiser start path.
		//! @return					This.
		Serialiser& SetStream( StreamPtr stream, const Char* start_path = NULL );
		//! Serialise object of specified type.
		//! @tparam	OBJECT_TYPE		Serialise object type.
		//! @param	obj				Serialise object reference.
		//! @return					This.
		template< typename OBJECT_TYPE >
		Serialiser& Serialise( const OBJECT_TYPE& obj );
		//! Serialise object of specified type.
		//! @param	type			Serialise object type.
		//! @param	obj				Serialise object reference.
		//! @return					This.
		Serialiser& Serialise( const Type* type, const void* obj );
		
	/***** Protected Methods *****/
	protected:
		//! Initialise the stream (implementation specific).
		//! @param	s		Stream pointer.
		//! @param	type	Type to serialise.
		//! @param	obj		Object to serialise.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr Initialise( StreamPtr s, const Type* type, const void* obj ) = 0;
		//! Shutdown the stream (implementation specific).
		//! @param	s		Stream pointer.
		//! @param	type	Type to serialise.
		//! @param	obj		Object to serialise.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr Shutdown( StreamPtr s, const Type* type, const void* obj ) = 0;
		//! Traverse the stream specified by the path.
		//! @param	s		Stream pointer.
		//! @param	path	Traversal path.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr TraverseStream( StreamPtr s, const Char* path ) = 0;
		//! Called when the stream has been set.
		virtual void OnStreamSet( void ) = 0;
		
	/***** Protected Methods *****/
	protected:
		//! Actual serialise method.
		//! @param	s		Stream pointer.
		//! @param	type	Type to serialise.
		//! @param	obj		Object to serialise.
		//! @param	attr	Optional field attributes.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr DoSerialise( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, bool outputType ) = 0;
		
	/***** Protected Members *****/
	protected:
		StreamPtr	mStream;	//!< Stream pointer.
	};

	template< typename SERIALISER_TYPE >
	inline Serialiser& Serialiser::SetStream( SERIALISER_TYPE& stream, const Char* start_path ) {
		return SetStream( &stream, start_path );
	}

	template< typename OBJECT_TYPE >
	inline Serialiser& Serialiser::Serialise( const OBJECT_TYPE& obj ) {
		CBL_STATIC_ASSERT( IsPtr<OBJECT_TYPE>::Value == false );
		return Serialise( CBL_ENT.Types.Get<OBJECT_TYPE>(), &obj );
	}
}

#endif // __CBL_SERIALISER_H_
