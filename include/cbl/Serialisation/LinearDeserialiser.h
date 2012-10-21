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
 * @file LinearDeserialiser.h
 * @brief Linear deserialiser class.
 */

#ifndef __CBL_LINEARDESERIALISER_H_
#define __CBL_LINEARDESERIALISER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Serialisation/Deserialiser.h"

namespace cbl
{
	class CBL_API LinearDeserialiser :
		public Deserialiser
	{
	private:
		using cbl::Deserialiser::StreamPtr;

	public:
		//! Called just before a container is serialised.
		virtual StreamPtr OnContainer( StreamPtr s, Uint32& size ) = 0;
		//! Virtual method to append a type to the stream.
		virtual StreamPtr OnType( StreamPtr s, HashValue& type ) = 0;
		//! Virtual method to write data of a type.
		virtual StreamPtr OnValue( StreamPtr s, const Type* type, void* obj, const FieldAttr* attr ) = 0;

	/***** Protected Methods *****/
	protected:
		virtual StreamPtr DoDeserialise( StreamPtr s, const Type* type, void *& obj, const FieldAttr* attr, bool inferType );
	};
}

#endif // __CBL_LINEARDESERIALISER_H_
