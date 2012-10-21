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
 * @file Type.cpp
 * @brief Type information.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Reflection/Type.h"

using namespace cbl;

const EnumConst* Type::GetEnum( cbl::Uint32 value ) const
{
	for( size_t i = 0; i < mEnums.size(); ++i )
		if( mEnums[i].Value == value )
			return &mEnums[i];
	return NULL;
}

const EnumConst* Type::GetEnum( const CName& name ) const 
{
	for( size_t i = 0; i < mEnums.size(); ++i )
		if( mEnums[i].Name == name )
			return &mEnums[i];
	return NULL;
}

const Field* Type::GetField( const CName& name ) const
{
	for( size_t i = 0; i < mFields.size(); ++i )
		if( mFields[i].Name == name )
			return &mFields[i];
	return NULL;
}

Type& Type::Enum( const Char* name, Uint32 value )
{
	mEnums.push_back( EnumConst( name, value ) );

	if( ToString == NULL )
		ToString = &Stringifiers::ToStringEnum;
	if( FromString == NULL )
		FromString = &Stringifiers::FromStringEnum;

	return *this;
}

bool Type::HasFields( void ) const
{
	const Type* type = this;
	while( type ) {
		if( type->mFields.size() > 0 )
			return true;
		type = type->BaseType;
	}
	return false;
}

std::stack<const Type::Fields*> Type::GetAllFields( void ) const
{
	std::stack<const Type::Fields*> fieldStack;
	const cbl::Type* type = this;
	while( type ) {
		if( type->GetFields().size() > 0 )
			fieldStack.push( &(type->GetFields()) );
		type = type->BaseType;
	}
	return fieldStack;
}

void Stringifiers::ToStringEnum( String& str, const Type* type, const void* obj, const FieldAttr* attr )
{
	if( attr && attr->Hex != 0 ) {
		std::ostringstream o;
		o << std::hex << std::showbase << *(const Uint32*)obj;
		str = o.str();
		return;
	}

	if( *(const Uint32*)obj == 0 ) {
		str = "0";
		return;
	}

	if( const EnumConst* e = type->GetEnum( (*(Uint32*)obj) ) )
		str = e->Name.Text;
	else
		str = "";
}

void Stringifiers::FromStringEnum( const String& str, const Type* type, void* obj, const FieldAttr* attr )
{
	if( attr && attr->Hex != 0 ) {
		std::istringstream i( str );
		i >> std::hex >> (*(Uint32*)obj);
		return;
	}

	if( str == "0" ) {
		*(Uint32*)obj = 0;
		return;
	}

	if( const EnumConst* e = type->GetEnum( CName(str.c_str()) ) )
		*(Uint32*)obj = e->Value;
}

template<>
void Stringifiers::FromStringDef<bool>( const String& str, const Type*, void* obj, const FieldAttr* )
{
	if( str.length() > 0 ) {
		if( str.length() == 1 ) {
			switch( str[0] ) {
			case '1':
				(*(bool*)obj) = true;
				break;
			case '0':
				(*(bool*)obj) = false;
				break;
			}
			return;
		}

		String tstr = str;
		std::transform( tstr.begin(), tstr.end(), tstr.begin(), tolower );
		if( tstr == "true" )
			(*(bool*)obj) = true;
		else if( tstr == "false" )
			(*(bool*)obj) = false;
	}
}
