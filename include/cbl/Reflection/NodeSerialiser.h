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
 * @file NodeSerialiser.h
 * @brief Abstract serialiser class.
 */

#ifndef __CBL_NODESERIALISER_H_
#define __CBL_NODESERIALISER_H_

// Chewable Headers//
#include "cbl/Chewable.h"
#include "cbl/Reflection/Serialiser.h"

namespace cbl
{
	//! Base serialiser class.
	class CBL_API NodeSerialiser :
		public Serialiser
	{
	/***** Types *****/
	public:
		typedef void*		StreamPtr;	//!< Stream pointer type.
		
	/***** Public Methods *****/
	public:
		//! Serialiser output to file.
		//! @return					This.
		NodeSerialiser& Output( const Char* filename );
		
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
		virtual void EndContainerEntry( StreamPtr s, const Type* keyType, const Type* valType ) = 0;
		//! Virtual method to begin writing a key for a container.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container key type.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginContainerKey( StreamPtr s, const Type* keyType ) = 0;
		//! Virtual method to end writing a key for a container.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container key type.
		virtual void EndContainerKey( StreamPtr s, const Type* keyType ) = 0;
		//! Virtual method to begin writing a value for a container.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container value type.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginContainerValue( StreamPtr s, const Type* keyType, const Type* valType ) = 0;
		//! Virtual method to end writing a value for a container.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container value type.
		virtual void EndContainerValue( StreamPtr s, const Type* keyType, const Type* valType ) = 0;
		//! Virtual method to start writing data of a type.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container value type.
		//! @param	obj		Object to serialise.
		//! @param	attr	Optional field attributes.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr BeginValue( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, Entity::OPTIONS opt, bool outputType ) = 0;
		//! Virtual method to end writing data of a type.
		//! @param	s		Stream pointer.
		//! @param	keyType	Container value type.
		//! @param	obj		Object to serialise.
		//! @param	attr	Optional field attributes.
		virtual void EndValue( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, Entity::OPTIONS opt, bool outputType ) = 0;
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
		//! Output method.
		//! @param	s			Stream pointer.
		//! @param	filename	File name.
		virtual void OnOutput( StreamPtr s, const Char* filename ) = 0;
		
	/***** Private Methods *****/
	private:
		//! Recursive serialise method.
		//! @param	s		Stream pointer.
		//! @param	type	Type to serialise.
		//! @param	obj		Object to serialise.
		//! @param	attr	Optional field attributes.
		//! @return			Adjusted stream pointer.
		virtual StreamPtr DoSerialise( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, bool outputType );
	};
}

#endif // __CBL_NODESERIALISER_H_
