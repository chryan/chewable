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
 * @file Type.inl
 * @brief Type information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#include "cbl/Debug/Assert.h"

namespace cbl
{
	template< typename INTEGRAL_TYPE >
	inline void Stringifiers::ToStringDef( String& str, const Type*, const void* obj, const FieldAttr* attr )
	{
		std::ostringstream o;
		if( attr && attr->Hex != 0 ) o << std::hex << std::showbase;
		o << *(INTEGRAL_TYPE*)obj;
		str = o.str();
	}

	template< typename INTEGRAL_TYPE >
	inline void Stringifiers::FromStringDef( const String& stream, const Type*, void* obj, const FieldAttr* attr )
	{
		std::istringstream i( stream );
		if( attr && attr->Hex != 0 ) i >> std::hex;
		i >> (*(INTEGRAL_TYPE*)obj);
	}

	template<>
	inline void Stringifiers::ToStringDef<Int8>( String& str, const Type*, const void* obj, const FieldAttr* attr )
	{
		std::ostringstream o;
		if( attr && attr->Hex != 0 ) o << std::hex << std::showbase;
		o << Int32( *(Int8*)obj );
		str = o.str();
	}

	template<>
	inline void Stringifiers::FromStringDef<Int8>( const String& stream, const Type*, void* obj, const FieldAttr* attr )
	{
		Int32 t; std::istringstream i( stream );
		if( attr && attr->Hex != 0 ) i >> std::hex;
		i >> t; (*(Int8*)obj) = Int8( t );
	}

	template<>
	inline void Stringifiers::ToStringDef<bool>( String& str, const Type*, const void* obj, const FieldAttr* )
	{
		str = (*(bool*)obj) ? "true" : "false";
	}
	
	template<>
	inline void Stringifiers::ToStringDef<String>( String& str, const Type*, const void* obj, const FieldAttr* )
	{
		str = *(String*)obj;
	}

	template<>
	inline void Stringifiers::FromStringDef<String>( const String& stream, const Type*, void* obj, const FieldAttr* )
	{
		*(String*)obj = stream;
	}

	template< typename ENTITY_TYPE, typename FIELD_TYPE >
	inline Type& Type::Field( const Char* name, FIELD_TYPE ENTITY_TYPE::*field, FieldAttr attrs )
	{
		mFields.push_back( cbl::Field( CName( name ), DB->Get< StripPtr<FIELD_TYPE>::Type >(), field, attrs ) );
		return *this;
	}

	template< typename BASE_TYPE >
	inline Type& Type::Base( void )
	{
		BaseType = DB->Get< StripPtr<BASE_TYPE>::Type >();
		return *this;
	}

	template< typename TYPE >
	inline Type& Type::DefaultSerialisers( void )
	{
		ToString	= &Stringifiers::ToStringDef< StripPtr<TYPE>::Type >;
		FromString	= &Stringifiers::FromStringDef< StripPtr<TYPE>::Type >;

		return *this;
	}

	inline Type& Type::DefineSerialisers( Stringifiers::ToString tostr, Stringifiers::FmString fmstr )
	{
		ToString	= tostr;
		FromString	= fmstr;

		return *this;
	}

	inline bool Type::operator == ( const Type& rhs ) const
	{
		return Name == rhs.Name;
	}

	inline bool Type::operator < ( const Type& rhs ) const
	{
		return Name < rhs.Name;
	}

	template< typename PARENT >
	inline bool Type::IsType( void ) const
	{
		return IsType( TypeCName<PARENT>() );
	}

	//! Check if type is child of specified parent type.
	inline bool Type::IsType( const CName& parent ) const
	{
		if( parent == Name ) return true;
		const Type* p = BaseType;
		while( p ) {
			if( p->Name == parent ) return true;
			p = p->BaseType;
		}
		return false;
	}

	inline void* Type::New( void ) const
	{
		CBL_ASSERT( Size > 0, "Type not valid" );
		void* obj = malloc( Size );
		Constructor( obj );
		return obj;
	}

	inline void Type::Delete( void* obj ) const
	{
		Destructor( obj );
		free( obj );
	}
}