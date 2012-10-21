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
 * @file Deserialiser.h
 * @brief Abstract deserialiser class.
 */

#ifndef __CBL_DESERIALISER_H_
#define __CBL_DESERIALISER_H_

// Chewable Headers//
#include "cbl/Chewable.h"

namespace cbl
{
	//! Base deserialiser class.
	class CBL_API Deserialiser
	{
	/***** Types *****/
	public:
		typedef void*		StreamPtr;	//!< Stream pointer type.
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		Deserialiser();
		//! Destructor.
		virtual ~Deserialiser();
		//! Set the deserialiser's stream. Convenience function.
		//! @tparam	DESERIALISER_TYPE	Deserialise stream type.
		//! @param	stream				Deserialiser stream reference.
		//! @param	start_path			Deserialiser start path.
		//! @return						This.
		template< typename DESERIALISER_TYPE >
		Deserialiser& SetStream( DESERIALISER_TYPE& stream, const Char* start_path = NULL );
		//! Set the deserialiser's stream.
		//! @param	stream				Deserialiser stream pointer.
		//! @param	start_path			Deserialiser start path.
		//! @return						This.
		Deserialiser& SetStream( StreamPtr stream, const Char* start_path = NULL );
		//! Deserialisation method.
		//! @tparam	OBJECT_TYPE			Deserialise object type.
		//! @param	obj					Deserialise object reference.
		//! @return						Flag to indicate if deserialisation was successful.
		template< typename OBJECT_TYPE >
		bool Deserialise( OBJECT_TYPE& obj );
		//! Deserialisation method.
		//! @tparam	OBJECT_TYPE			Deserialise object type.
		//! @param	obj					Deserialise object reference.
		//! @return						Flag to indicate if deserialisation was successful.
		template< typename OBJECT_TYPE >
		bool DeserialisePtr( OBJECT_TYPE*& obj );
		//! Deserialisation method.
		//! @param	type				Deserialise object type.
		//! @param	obj					Deserialise object reference.
		//! @return						Flag to indicate if deserialisation was successful.
		bool Deserialise( const Type* type, void *& obj );
		//! Check if the stream has ended.
		virtual bool IsStreamEnded( void ) const = 0;
		
	/***** Protected Methods *****/
	protected:
		//! Initialise the stream (implementation specific).
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr Initialise( StreamPtr s, const Type* type, void* obj ) = 0;
		//! Shutdown the stream (implementation specific).
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr Shutdown( StreamPtr s, const Type* type, void* obj ) = 0;
		//! Traverse the stream specified by the path.
		//! @param	s		Stream pointer.
		//! @param	path	Traversal path.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr TraverseStream( StreamPtr s, const Char* path ) = 0;
		//! Called when the stream has been set.
		virtual void OnStreamSet( void ) = 0;
		
	/***** Protected Methods *****/
	protected:
		//! Recursive deserialise method.
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @param	attr	Optional field attributes.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr DoDeserialise( StreamPtr s, const Type* type, void *& obj, const FieldAttr* attr, bool inferType ) = 0;
		
	/***** Protected Members *****/
	protected:
		StreamPtr mStream;	//!< Stream pointer.
	};

	template< typename DESERIALISER_TYPE >
	inline Deserialiser& Deserialiser::SetStream( DESERIALISER_TYPE& stream, const Char* start_path )
	{
		return SetStream( &stream, start_path );
	}

	template< typename OBJECT_TYPE >
	inline bool Deserialiser::Deserialise( OBJECT_TYPE& obj )
	{
		CBL_STATIC_ASSERT( IsPtr<OBJECT_TYPE>::Value == false );
		void* o = &obj;
		return Deserialise( CBL_ENT.Types.Get<OBJECT_TYPE>(), o );
	}

	template< typename OBJECT_TYPE >
	inline bool Deserialiser::DeserialisePtr( OBJECT_TYPE*& obj )
	{
		CBL_STATIC_ASSERT( IsPtr<OBJECT_TYPE>::Value == false );
		void* o = obj;
		if( Deserialise( CBL_ENT.Types.Get<OBJECT_TYPE>(), o ) ) {
			obj = static_cast<OBJECT_TYPE*>(o);
			return true;
		}
		return false;
	}
}

#endif // __CBL_DESERIALISER_H_
