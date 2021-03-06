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
 * @file BinaryDeserialiser.h
 * @brief Binary deserialiser class.
 */

#ifndef __CBL_BINARYDESERIALISER_H_
#define __CBL_BINARYDESERIALISER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Serialisation/LinearDeserialiser.h"

namespace cbl
{
	//! Binary deserialiser class.
	class CBL_API BinaryDeserialiser :
		public LinearDeserialiser 
	{
	/***** Types *****/
	private:
		using cbl::Deserialiser::StreamPtr;
		
	/***** Public Methods *****/
	public:
		//! Check if the stream has ended.
		virtual bool IsStreamEnded( void ) const;
		//! Get the next type that the deserialiser will be deserialising.
		HashValue GetNextType( void ) const;
		
	/***** Protected Methods *****/
	protected:
		//! Initialise the stream (implementation specific).
		virtual StreamPtr Initialise( StreamPtr s, const Type* type, void* obj );
		//! Shutdown the stream (implementation specific).
		virtual StreamPtr Shutdown( StreamPtr s, const Type* type, void* obj );
		//! Traverse the stream specified by the path.
		virtual StreamPtr TraverseStream( StreamPtr s, const Char* path );
		//! Called just before a container is serialised.
		virtual StreamPtr OnContainer( StreamPtr s, Uint32& size );
		//! Virtual method to append a type to the stream.
		virtual StreamPtr OnType( StreamPtr s, HashValue& type );
		//! Virtual method to write data of a type.
		virtual StreamPtr OnValue( StreamPtr s, const Type* type, void* obj, const FieldAttr* attr );
		//! Called when the stream has been set.
		virtual void OnStreamSet( void );
	};
}

#endif // __CBL_BINARYDESERIALISER_H_
