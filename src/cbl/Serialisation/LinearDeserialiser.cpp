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
 * @file LinearDeserialiser.cpp
 * @brief Linear deserialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Serialisation/LinearDeserialiser.h"

using namespace cbl;

typedef cbl::Serialiser::StreamPtr StreamPtr;

#define INCREMENT_STREAM_PTR\
	if( next ) current = next

StreamPtr LinearDeserialiser::DoDeserialise( StreamPtr s, const Type* type, void *& obj, const FieldAttr* attr, bool inferType )
{
	if( !type ) {
		LOG_ERROR( "Type not specified." );
		return s;
	}

	StreamPtr	current = s,
				next = s;
	
	// New the object if it doesn't exist.
	if( inferType ) {
		HashValue typeHash;
		// If no type was entered, we don't do anything.
		// Otherwise we check if it's a valid type to be inferred.
		next = OnType(current, typeHash);
		INCREMENT_STREAM_PTR;

		const Type* t = CBL_ENT.Types.Get( CName( typeHash ) );
		if( !t ) {
			LOG_ERROR( "Unable to determine type for " << type->Name.Text << "." );
			type = NULL;
		} else if( !t->IsType( type->Name.Text ) ) {
			LOG_ERROR( t->Name.Text << " is not a type of " << type->Name.Text );
			type = NULL;
		} else {
			type = t;
		}
	}
	if( type && !obj ) obj = CBL_ENT.New( type );
	if( !obj ) {
		LOG_ERROR( "Unable to create type: " << type->Name.Text );
		return NULL;
	}

	Entity::OPTIONS opt = Entity::O_NORMAL;
	if( type->IsEntity ) {
		opt = ((EntityPtr)obj)->OnPreChanged();
		if( opt == Entity::O_SKIP )
			return s;
	}

	next = OnValue( current, type, obj, attr );
	if( !next ) // We handled the value.
		return NULL;
	current = next;

	std::stack<const Type::Fields*> fieldStack = type->GetAllFields();

	while( !fieldStack.empty() && ( opt != Entity::O_IGNORE_FIELDS ) )
	{
		for( size_t i = 0; i < fieldStack.top()->size(); ++i ) {
			const Field& field = (*fieldStack.top())[i];
			// Serialize container.
			if( field.Attributes.Transient != 0 )
				continue;

			// Get a pointer to the data member.
			void* dataPtr = field.IsPointer ? *((void**)field.GetPtr( obj )) : field.GetPtr( obj );

			if( field.Container ) { // Try to serialize if container
				const Type* keyType = field.Container->KeyType;
				const Type* valType = field.Container->ValueType;
				cbl::Uint32 size = 0;

				if( cbl::FieldWriteIterator* it = CBL_NEW_FIELD_WRITEIT( field.Container, dataPtr ) ) {
					next = OnContainer( current, size );
					INCREMENT_STREAM_PTR;
					bool keyInferType = field.Container->IsKeyPointer && keyType && keyType->IsEntity;
					bool valInferType = field.Container->IsValuePointer && valType->IsEntity;

					for( cbl::Uint32 j = 0; j < size; ++j ) {
						void	*newKey = NULL,
								*newVal = NULL;

						if( keyType ) {
							next = DoDeserialise( current, keyType, newKey, &field.Attributes, keyInferType );
							INCREMENT_STREAM_PTR;
						}
						next = DoDeserialise( current, valType, newVal, &field.Attributes, valInferType );
						INCREMENT_STREAM_PTR;

						if( newKey && newVal ) {
							it->Add(
								field.Container->IsKeyPointer ? (void*)(&newKey) : newKey,
								field.Container->IsValuePointer ? (void*)(&newVal) : newVal
								);
						} else {
							it->Add( field.Container->IsValuePointer ? (void*)(&newVal) : newVal );
						}

						if( newKey && !field.Container->IsKeyPointer ) {
							if( keyType->IsEntity )	CBL_ENT.Delete( (EntityPtr)newKey );
							else					keyType->Delete( newKey );
						}
						if( newVal && !field.Container->IsValuePointer ) {
							if( valType->IsEntity )	CBL_ENT.Delete( (EntityPtr)newVal );
							else					valType->Delete( newVal );
						}
					}
					CBL_DEL_FIELD_IT( field.Container, it );
				}
			} else {
				// Otherwise just deserialize as per normal.
				if( field.IsPointer ) {
					void* newObj = NULL;
					next = DoDeserialise( current, field.Type, newObj, &field.Attributes, field.Type->IsEntity );
					INCREMENT_STREAM_PTR;
					*((void**)field.GetPtr( obj )) = newObj;
				}
				else {
					next = DoDeserialise( current, field.Type, dataPtr, &field.Attributes, false );
					INCREMENT_STREAM_PTR;
				}
			}
		}
		fieldStack.pop();
	}

	if( type->IsEntity )
		((EntityPtr)obj)->OnChanged();

	return s;
}
