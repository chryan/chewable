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
 * @file LinearSerialiser.cpp
 * @brief Linear serialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Serialisation/LinearSerialiser.h"

using namespace cbl;

typedef cbl::Serialiser::StreamPtr StreamPtr;

#define INCREMENT_STREAM_PTR\
	if( next ) mStream = next


StreamPtr LinearSerialiser::DoSerialise( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, bool outputType )
{
	Entity::OPTIONS opt = Entity::O_NORMAL;

	if( type->IsEntity ) {
		opt = ((EntityPtr)obj)->OnPreSaved();
		if( opt == Entity::O_SKIP )
			return s;
	}

	StreamPtr	next = s;
	mStream = s;

	if( outputType ) {
		next = OnType( mStream, type );
		INCREMENT_STREAM_PTR;
	}

	next = OnValue( mStream, type, obj, attr );
	if( !next ) // We handled the value.
		return NULL;
	mStream = next;

	std::stack<const Type::Fields*> fieldStack = type->GetAllFields();

	while( !fieldStack.empty() && ( opt != Entity::O_IGNORE_FIELDS ) )
	{
		for( size_t i = 0; i < fieldStack.top()->size(); ++i ) {
			const Field& field = (*fieldStack.top())[i];
			// Serialize container.
			if( field.Attributes.Transient != 0 )
				continue;

			// Get a pointer to the data member.
			const void* dataPtr = field.IsPointer ? *((const void**)field.GetPtr( obj )) : field.GetPtr( obj );

			if( field.Container ) { // Try to serialize if container
				const Type* keyType = field.Container->KeyType;
				const Type* valType = field.Container->ValueType;

				bool keyEntity = keyType ? keyType->IsEntity : false;
				bool valEntity = valType->IsEntity;

				const void
					*keyPtr = NULL,
					*valPtr = NULL;
				const Type
					*keyEntryType	= NULL,
					*valEntryType	= NULL;

				// Work on the container.
				{
					cbl::FieldReadIterator* it = CBL_NEW_FIELD_READIT( field.Container, dataPtr );
					next = OnContainer( mStream, it->Count() );
					INCREMENT_STREAM_PTR;
					bool keyOutType = field.Container->IsKeyPointer && keyType && keyType->IsEntity;
					bool valOutType = field.Container->IsValuePointer && valType->IsEntity;

					for( ; it->IsValid(); it->IncNext() ) {
						if( keyType ) {
							keyPtr			= field.Container->IsKeyPointer ? *(const void**)it->GetKey() : it->GetKey();
							keyEntryType	= keyEntity && &((EntityPtr)keyPtr)->GetType() ? &((EntityPtr)keyPtr)->GetType() : keyType;
						}
						valPtr			= field.Container->IsValuePointer ? *(const void**)it->GetValue() : it->GetValue();
						valEntryType	= valEntity && &((EntityPtr)valPtr)->GetType() ? &((EntityPtr)valPtr)->GetType() : valType;

						if( keyType ) {
							next = DoSerialise( mStream, keyEntryType, keyPtr, &field.Attributes, keyOutType );
							INCREMENT_STREAM_PTR;
						}

						next = DoSerialise( mStream, valEntryType, valPtr, &field.Attributes, valOutType );
						INCREMENT_STREAM_PTR;

					} CBL_DEL_FIELD_IT( field.Container, it );
				} 
			} else {
				const Type* ftype = field.Type->IsEntity && &((EntityPtr)dataPtr)->GetType() ? &((EntityPtr)dataPtr)->GetType() : field.Type;
				next = DoSerialise( mStream, ftype, dataPtr, &field.Attributes, field.IsPointer && field.Type->IsEntity );
			}
		}
		fieldStack.pop();
	}

	if( type->IsEntity )
		((EntityPtr)obj)->OnSaved();

	return s;
}
