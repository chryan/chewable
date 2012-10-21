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
 * @file NodeDeserialiser.h
 * @brief Abstract deserialiser class.
 */

#ifndef __CBL_NODEDESERIALISER_H_
#define __CBL_NODEDESERIALISER_H_

// Chewable Headers//
#include "cbl/Chewable.h"
#include "cbl/Reflection/Deserialiser.h"

namespace cbl
{
	//! Base deserialiser class.
	class CBL_API NodeDeserialiser :
		public Deserialiser
	{
	/***** Types *****/
	public:
		typedef void*		StreamPtr;	//!< Stream pointer type.
		
	/***** Protected Methods *****/
	protected:
		//! Virtual method to begin writing a container entry.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container key type.
		//! @param	valType	Container value type.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginContainerEntry( StreamPtr s, const Type* keyType, const Type* valType ) = 0;
		//! Virtual method to end writing a container entry.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container key type.
		//! @param	valType	Container value type.
		//! @return			Adjusted stream pointer.
		virtual void EndContainerEntry( StreamPtr s, const Type* keyType, const Type* valType ) = 0;
		//! Get the next container key stream.
		//! @param	s		Stream pointer.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr GetContainerKeyStream( StreamPtr s ) const = 0;
		//! Get the next container value stream.
		//! @param	s		Stream pointer.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr GetContainerValueStream( StreamPtr s, bool hasKey ) const = 0;
		//! Virtual method to start writing data of a type.
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginValue( StreamPtr s, const Type* type, void * obj, const FieldAttr* attr ) = 0;
		//! Virtual method to end writing data of a type.
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @return			Adjusted stream pointer.
		virtual void EndValue( StreamPtr s, const Type* type, void * obj, const FieldAttr* attr ) = 0;
		//! Virtual method to begin writing fields.
		//! @param	s		Stream pointer.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginFields( StreamPtr s ) = 0;
		//! Virtual method to end writing fields.
		//! @param	s		Stream pointer.
		virtual void EndFields( StreamPtr s ) = 0;
		//! Virtual method to begin writing a field.
		//! @param	s		Stream pointer.
		//! @param	field	Field type pointer.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginField( StreamPtr s, const Field* field ) = 0;
		//! Virtual method to end writing a field.
		//! @param	s		Stream pointer.
		//! @param	field	Field type pointer.
		virtual void EndField( StreamPtr s, const Field* field ) = 0;
		//! Get the current type in the stream.
		virtual bool GetValueType( StreamPtr s, String& type ) const = 0;
		
	/***** Private Methods *****/
	private:
		//! Recursive deserialise method.
		//! @param	s		Stream pointer.
		//! @param	type	Type to deserialise.
		//! @param	obj		Object to deserialise. Attempts to allocate memory for it if NULL is passed.
		//! @param	attr	Optional field attributes.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr DoDeserialise( StreamPtr s, const Type* type, void *& obj, const FieldAttr* attr, bool inferType );
	};
}

#endif // __CBL_NODEDESERIALISER_H_
