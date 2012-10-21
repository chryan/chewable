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
 * @file NodeDeserialiser.cpp
 * @brief Abstract deserialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers//
#include "cbl/Reflection/NodeDeserialiser.h"
#include "cbl/Reflection/Serialiser.h"

using namespace cbl;

NodeDeserialiser::StreamPtr NodeDeserialiser::DoDeserialise( StreamPtr s, const Type* type, void*& obj, const FieldAttr* attr, bool inferType )
{
	if( !type ) {
		LOG_ERROR( "Type not specified." );
		return s;
	}

	// New the object if it doesn't exist.
	if( !obj ) {
		String typeStr = type->Name.Text;
		if( inferType ) {
			// If no type was entered, we don't do anything.
			// Otherwise we check if it's a valid type to be inferred.
			if( GetValueType(s, typeStr) && typeStr.length() > 0 ) {
				const Type* t = CBL_ENT.Types.Get( CName( typeStr.c_str() ) );
				if( !t ) {
					LOG_ERROR( typeStr << " is not a valid type" );
					type = NULL;
				} else if( !t->IsType( type->Name.Text ) ) {
					LOG_ERROR( t->Name.Text << " is not a type of " << type->Name.Text );
					type = NULL;
				} else {
					type = t;
				}
			}
		}
		if( type ) obj = CBL_ENT.New( type );
		if( !obj ) {
			LOG_ERROR( "Unable to create type: " << typeStr );
			return s;
		}
	}

	Entity::OPTIONS opt = Entity::O_NORMAL;
	if( type->IsEntity ) {
		opt = ((EntityPtr)obj)->OnPreChanged();
		if( opt == Entity::O_SKIP )
			return s;
	}

	StreamPtr b_val = BeginValue( s, type, obj, attr );

	// Check if the value was read.
	if( !b_val )
		return s;

	std::stack<const Type::Fields*> fieldStack = type->GetAllFields();

	if( !fieldStack.empty() && ( opt != Entity::O_IGNORE_FIELDS ) ) {
		// Begin field serialisation.
		StreamPtr b_fields = BeginFields( b_val );
		while( !fieldStack.empty() )
		{
			for( size_t i = 0; i < fieldStack.top()->size(); ++i ) {
				const Field& field = (*fieldStack.top())[i];
				// Serialize container.
				if( field.Attributes.Transient != 0 )
					continue;

				StreamPtr b_field = BeginField( b_fields, &field );
				// Check if the field is in there.
				if( !b_field )
					continue;

				// Get a pointer to the data member.
				void* dataPtr = field.IsPointer ? *((void**)field.GetPtr( obj )) : field.GetPtr( obj );

				if( field.Container ) { // Try to serialize if container
					const Type* keyType = field.Container->KeyType;
					const Type* valType = field.Container->ValueType;

					String keyStr, valStr;

					if( cbl::FieldWriteIterator* it = CBL_NEW_FIELD_WRITEIT( field.Container, dataPtr ) ) {
						while( StreamPtr b_cont_entry = BeginContainerEntry( b_field, keyType, valType ) ) {
							void *newKey = NULL,
								 *newVal = NULL;

							StreamPtr	key_stream = keyType ? GetContainerKeyStream( b_cont_entry ) : NULL,
										val_stream = GetContainerValueStream( b_cont_entry, keyType != NULL );

							const Type* actualKey = NULL;
							const Type* actualVal = NULL;

							if( key_stream )
								actualKey = GetValueType( key_stream, keyStr ) && keyStr.length() > 0 ? CBL_ENT.Types.Get( CName( keyStr.c_str() ) ) : keyType;
							actualVal = GetValueType( val_stream, valStr ) && valStr.length() > 0 ? CBL_ENT.Types.Get( CName( valStr.c_str() ) ) : valType;

							if( !actualVal ) {
								LOG_ERROR( valStr << " is not a valid type" );
							} else if( !actualVal->IsType( valType->Name ) ) {
								LOG( LogLevel::Warning << actualVal->Name.Text << " is not a type of " << valType->Name.Text );
							} else {
								if( keyType ) {
									if( !actualKey ) {
										LOG_ERROR( keyStr << " is not a valid type" );
									} else if( !actualKey->IsType( keyType->Name ) ) {
										LOG( LogLevel::Warning << actualKey->Name.Text << " is not a type of " << keyType->Name.Text );
									} else {
										DoDeserialise( key_stream, actualKey, newKey, &field.Attributes, false );
										DoDeserialise( val_stream, actualVal, newVal, &field.Attributes, false );
										if( newKey && newVal ) {
											it->Add(
												field.Container->IsKeyPointer ? (void*)(&newKey) : newKey,
												field.Container->IsValuePointer ? (void*)(&newVal) : newVal
												);
										}
									}
								} else {
									DoDeserialise( val_stream, actualVal, newVal, &field.Attributes, false );
									if( newVal )
										it->Add( field.Container->IsValuePointer ? (void*)(&newVal) : newVal );
								}
							}

							if( newKey && !field.Container->IsKeyPointer ) {
								if( actualKey->IsEntity )	CBL_ENT.Delete( (EntityPtr)newKey );
								else						actualKey->Delete( newKey );
							}
							if( newVal && !field.Container->IsValuePointer ) {
								if( actualVal->IsEntity )	CBL_ENT.Delete( (EntityPtr)newVal );
								else						actualVal->Delete( newVal );
							}
							EndContainerEntry( b_field, keyType, valType );
						}
						CBL_DEL_FIELD_IT( field.Container, it );
					}
				} else { // Otherwise just deserialize as per normal.
					if( field.IsPointer ) {
						void* newObj = NULL;
						DoDeserialise( b_field, field.Type, newObj, &field.Attributes, true );
						*((void**)field.GetPtr( obj )) = newObj;
					}
					else {
						DoDeserialise( b_field, field.Type, dataPtr, &field.Attributes, false );
					}
				}

				EndField( b_fields, &field );
			}
			fieldStack.pop();
		}

		EndFields( b_val );
	}

	EndValue( s, type, obj, attr );

	if( type->IsEntity )
		((EntityPtr)obj)->OnChanged();

	return s;
}
