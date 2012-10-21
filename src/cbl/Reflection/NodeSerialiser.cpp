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
 * @file NodeSerialiser.cpp
 * @brief Abstract node serialiser class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Reflection/NodeSerialiser.h"

using namespace cbl;

NodeSerialiser& NodeSerialiser::Output( const Char* filename )
{
	OnOutput( mStream, filename );
	return *this;
}

NodeSerialiser::StreamPtr NodeSerialiser::DoSerialise( StreamPtr s, const Type* type, const void* obj, const FieldAttr* attr, bool outputType )
{
	Entity::OPTIONS opt = Entity::O_NORMAL;

	if( type->IsEntity ) {
		opt = ((EntityPtr)obj)->OnPreSaved();
		if( opt == Entity::O_SKIP )
			return s;
	}

	// Serialise the object.
	StreamPtr b_val = BeginValue( s, type, obj, attr, opt, outputType );

	std::stack<const Type::Fields*> fieldStack = type->GetAllFields();

	if( b_val && !fieldStack.empty() && ( opt != Entity::O_IGNORE_FIELDS ) ) {
		// Begin field serialisation.
		if( StreamPtr b_fields = BeginFields( b_val ) ) {
			while( !fieldStack.empty() )
			{
				for( size_t i = 0; i < fieldStack.top()->size(); ++i ) {
					const Field& field = (*fieldStack.top())[i];
					// Don't serialise if transient.
					if( field.Attributes.Transient != 0 )
						continue;
			
					if( StreamPtr b_field = BeginField( b_fields, &field ) ) {
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
							bool keyDerived = false,
								valDerived = false;

							CBL_FOREACH_READ_FIELD_BEGIN( field.Container, it, dataPtr ) {
								if( keyType ) {
									keyPtr			= field.Container->IsKeyPointer ? *(const void**)it->GetKey() : it->GetKey();
									keyEntryType	= keyEntity && &((EntityPtr)keyPtr)->GetType() ? &((EntityPtr)keyPtr)->GetType() : keyType;
									keyDerived		= field.Container->IsKeyPointer && keyEntryType != keyType;
								}
								valPtr			= field.Container->IsValuePointer ? *(const void**)it->GetValue() : it->GetValue();
								valEntryType	= valEntity && &((EntityPtr)valPtr)->GetType() ? &((EntityPtr)valPtr)->GetType() : valType;
								valDerived		= field.Container->IsValuePointer && valEntryType != valType;

								StreamPtr b_cont_entry = BeginContainerEntry( b_field, keyEntryType, valEntryType );

								if( keyType ) {
									DoSerialise(
										BeginContainerKey( b_cont_entry, keyEntryType ), keyEntryType, keyPtr, &field.Attributes, keyDerived
									);
									EndContainerKey( b_cont_entry, keyEntryType );
								}

								DoSerialise(
									BeginContainerValue( b_cont_entry, keyEntryType, valEntryType ), valEntryType, valPtr, &field.Attributes, valDerived
								);
								EndContainerValue( b_cont_entry, keyEntryType, valEntryType );

								EndContainerEntry( b_field, keyEntryType, valEntryType );

							} CBL_FOREACH_FIELD_END( field.Container, it );

						} else { // Otherwise just serialize as per normal.
							const Type* ftype = field.Type->IsEntity && &((EntityPtr)dataPtr)->GetType() ? &((EntityPtr)dataPtr)->GetType() : field.Type;
							DoSerialise( b_field, ftype, dataPtr, &field.Attributes, field.IsPointer && field.Type != ftype );
						}
					} EndField( b_fields, &field );
				}
				fieldStack.pop();
			}
		} EndFields( b_val );
	}

	EndValue( s, type, obj, attr, opt, outputType );

	if( type->IsEntity )
		((EntityPtr)obj)->OnSaved();

	return s;
}
