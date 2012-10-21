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
 * @file Type.h
 * @brief Type information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_TYPE_H_
#define __CBL_TYPE_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/Field.h"
#include "cbl/Reflection/EnumConst.h"
#include "cbl/Util/CName.h"

// External Libraries //
#include <vector>
#include <stack>

namespace cbl
{
	/***** Forward Declarations *****/
	class TypeDB;

	//! String serialisation methods
	struct CBL_API Stringifiers
	{
		typedef void (*ToString)( String&, const Type*, const void*, const FieldAttr* );	//!< Type to string function pointer type.
		typedef void (*FmString)( const String&, const Type*, void*, const FieldAttr* );	//!< String to type function pointer type.

		template< typename INTEGRAL_TYPE >
		static void ToStringDef( String& str, const Type* type, const void* obj, const FieldAttr* attr );
		template< typename INTEGRAL_TYPE >
		static void FromStringDef( const String& str, const Type* type, void* obj, const FieldAttr* attr );
		static void ToStringEnum( String& str, const Type* type, const void* obj, const FieldAttr* attr );
		static void FromStringEnum( const String& str, const Type* type, void* obj, const FieldAttr* attr );
	};

	//! Basic type representation for any game entity.
	class CBL_API Type
	{
	/***** Types *****/
	public:
		typedef void (*ConstructFunc)( void* );			//!< Constructor function pointer type.
		typedef void (*DestructFunc)( void* );			//!< Destructor function pointer type.
		typedef std::vector< cbl::Field >		Fields;	//!< Field list type.
		typedef std::vector< cbl::EnumConst >	Enums;	//!< Enum list type.
		
	/***** Properties *****/
	public:
		//! Get type fields.
		inline const Fields& GetFields( void ) const { return mFields; }
		//! Get type enums.
		inline const Enums& GetEnums( void ) const { return mEnums; }
		//! Get enum by value if it exists.
		const EnumConst* GetEnum( cbl::Uint32 value ) const;
		//! Get enum by name if it exists.
		const EnumConst* GetEnum( const CName& name ) const;
		//! Get specific field.
		const Field* GetField( const CName& name ) const;

	/***** Public Methods *****/
	public:
		//! Declare new field to for type.
		//! e.g. Field( "X", &Vector3f::X );
		//! @param	name		Field name.
		//! @param	field		Pointer to member.
		template< typename ENTITY_TYPE, typename FIELD_TYPE >
		Type& Field( const Char* name, FIELD_TYPE ENTITY_TYPE::*field, FieldAttr attrs = FieldAttr() );
		//! Declare a base type.
		//! e.g. Base<ParentType>();
		template< typename BASE_TYPE >
		Type& Base( void );
		//! Declare an enum constant for this type.
		Type& Enum( const Char* name, Uint32 value );
		//! Define default serialisers for this type.
		//! See the StreamSerialise struct.
		template< typename TYPE >
		Type& DefaultSerialisers( void );
		//! Define the serialisers for this type.
		Type& DefineSerialisers( Stringifiers::ToString tostr, Stringifiers::FmString fmstr );
		//! Comparison operator.
		bool operator == ( const Type& rhs ) const;
		//! Less-than operator.
		bool operator < ( const Type& rhs ) const;
		//! Check if type is child of specified parent type.
		template< typename PARENT >
		bool IsType( void ) const;
		//! Check if type is child of specified parent type.
		bool IsType( const CName& parent ) const;
		//! Does this type have any fields? Includes base type fields.
		bool HasFields( void ) const;
		//! Newly allocated object of this type.
		void* New( void ) const;
		//! Delete existing allocated object of this type.
		void Delete( void* obj ) const;
		//! Get all fields.
		std::stack<const Fields*> GetAllFields( void ) const;

	/***** Private Methods *****/
	private:
		//! Private constructor. Only TypeDB should be creating this.
		inline Type( const CName& name, size_t size, ConstructFunc cfunc, DestructFunc dfunc, TypeDB* typeDB, bool entType )
			: DB( typeDB ), Constructor( cfunc ), Destructor( dfunc )
			, ToString( NULL ), FromString( NULL )
			, Size( size ), BaseType( NULL ), IsEntity( entType ), Name( name ) {}

	/***** Public Members *****/
	public:
		TypeDB*					DB;				//!< Parent type database
		ConstructFunc			Constructor;	//!< Pointers to the constructor function
		DestructFunc			Destructor;		//!< Pointers to the destructor function
		Stringifiers::ToString	ToString;		//!< Type to string function pointer.
		Stringifiers::FmString	FromString;		//!< String to type function pointer.
		size_t					Size;			//!< Result of sizeof(type) operation
		const Type*				BaseType;		//!< Base type.
		bool					IsEntity;		//!< Is this type derived from Entity.
		CName					Name;			//!< Type name.

	/***** Private Members *****/
	private:
		Fields				mFields;		//!< List of fields.
		Enums				mEnums;			//!< List of enum constants.
		friend class TypeDB;				//!< Befriend type DB.
	};
	template<>
	CBL_API void Stringifiers::FromStringDef<bool>( const String& stream, const Type*, void* obj, const FieldAttr* );
}

#include "Type.inl"

#define CBL_FIELD( fieldName, className )\
	Field( #fieldName, &className::fieldName )

#define CBL_FIELDM( fieldName, className )\
	Field( #fieldName, &className::m##fieldName )

#define CBL_FIELD_ATTR( fieldName, className, attr )\
	Field( #fieldName, &className::fieldName, attr )

#define CBL_FIELDM_ATTR( fieldName, className, attr )\
	Field( #fieldName, &className::m##fieldName, attr )

#define CBL_ENUM( enumName, enumType )\
	Enum( #enumName, enumType::enumName )

#endif // __CBL_TYPE_H_