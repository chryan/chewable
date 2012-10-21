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
 * @file Field.h
 * @brief Type field information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_FIELD_H_
#define __CBL_FIELD_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/CName.h"
#include "cbl/Util/SharedPtr.h"
#include "cbl/Reflection/FieldContainer.h"

namespace cbl
{
#pragma warning( push )
// Disable the unnamed struct warnings.
#pragma warning( disable : 4201 )

	//! Field attributes.
	class CBL_API FieldAttr
	{
	/***** Types *****/
	public:
		enum {
			F_READONLY		= 0x01,
			F_TRANSIENT		= 0x02,
			F_INLINE		= 0x04,
			F_HEX			= 0x08,
			F_CHANGEREFRESH	= 0x10,
		};
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		FieldAttr() : Group(NULL), Value( 0 ) {}
		//! Constructor.
		//! @param	val		Attribute values.
		FieldAttr( Uint32 val ) : Group(NULL), Value( val ) {}
		//! Constructor.
		//! @param	group	Field group.
		//! @param	val		Attribute values.
		FieldAttr( const Char* group, Uint32 val ) : Group(group), Value( val ) {}
		
	/***** Public Members *****/
	public:
		const Char* Group;
		union {
			struct {
				Uint32 ReadOnly			: 1;	//!< Read-only field.
				Uint32 Transient		: 1;	//!< Transient field (not serialisable).
				Uint32 Inline			: 1;	//!< Inline output field.
				Uint32 Hex				: 1;	//!< Hex value field.
				Uint32 ChangeRefresh	: 1;	//!< Indicates if editor needs to be refreshed when this value is set.
				Uint32 Unused			: 27;	//!< Unused flags.
			};
			Uint32 Value;	//! Field attribute value.
		};
	};
#pragma warning( pop ) 

	/***** Forward Declarations *****/
	class Type;

	//! Type field.
	class CBL_API Field
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		//! @tparam	ENTITY_TYPE	Member class type.
		//! @tparam	FIELD_TYPE	Field type.
		//! @param	name		Field name.
		//! @param	type		Field type.
		//! @param	attrs		Field attributes.
		//! @param	group		Field grouping.
		//! @param	desc		Field description.
		template< typename ENTITY_TYPE, typename FIELD_TYPE >
		Field( const CName& name, const cbl::Type* type, FIELD_TYPE ENTITY_TYPE::*field, FieldAttr attrs,
			const Char* group = NULL, const Char* desc = NULL );

		//! Get pointer to field data.
		//! @param	ent		Base object.
		//! @return			Field object address.
		inline void* GetPtr( const void* ent ) const { return (Char*)ent + Offset; }
		
	/***** Public Members *****/
	public:
		const cbl::Type*			Type;		//!< Field type.
		bool						IsPointer;	//!< Is field pointer?
		size_t						Offset;		//!< Field memory offset.
		SharedPtr<FieldContainer>	Container;	//!< Field container. NULL if this is not a container.
		CName						Name;		//!< Field name.
		CName						Group;		//!< Field grouping.
		CName						Desc;		//!< Field description.
		mutable FieldAttr			Attributes;	//!< Field attributes.
	};
}

#include "Field.inl"

#endif // __CBL_FIELD_H_
