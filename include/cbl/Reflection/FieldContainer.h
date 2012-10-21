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
 * @file FieldContainer.h
 * @brief Field container information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_FIELDCONTAINER_H_
#define __CBL_FIELDCONTAINER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Noncopyable.h"

namespace cbl
{
	//! Field container read iterator.
	//! Abstract class used to read container values.
	struct CBL_API FieldReadIterator :
		Noncopyable
	{
	/***** Public Methods *****/
	public:
		virtual ~FieldReadIterator() {}
		virtual const void* GetKey( void ) const	= 0;
		virtual const void* GetValue( void ) const	= 0;
		virtual bool IncNext( void ) const			= 0;
		virtual bool IsValid( void ) const			= 0;
		virtual Uint32 Count( void ) const			= 0;
	};

	//! Field container write iterator.
	//! Abstract class used to write container values.
	struct CBL_API FieldWriteIterator :
		Noncopyable
	{
	/***** Public Methods *****/
	public:
		virtual ~FieldWriteIterator() {}
		virtual bool Add( void* obj )				= 0;
		virtual bool Add( void* key, void* obj )	= 0;
		virtual void* AddEmpty( void )				= 0;
		virtual void* AddEmpty( void* key )			= 0;
	};

	//! Field container information.
	class CBL_API FieldContainer
	{
	/***** Public Members *****/
	public:
		const Type*		KeyType;		//!< Container key type.
		const Type*		ValueType;		//!< Container value type.
		bool			IsKeyPointer;	//!< Is key pointer?
		bool			IsValuePointer;	//!< Is value pointer?
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		FieldContainer()
		: KeyType( NULL ), ValueType( NULL )
		, IsKeyPointer( false ), IsValuePointer( false ) {}
		//! Get read iterator allocation size.
		virtual Uint32 GetReadItAllocSize( void ) const		= 0;
		//! Get write iterator allocation size.
		virtual Uint32 GetWriteItAllocSize( void ) const	= 0;
		//! Allocate a new read iterator.
		//! @param	dest		Allocation address.
		//! @param	container	Pointer to container.
		//! @return				New read iterator.
		virtual FieldReadIterator* CreateReadIt( void* dest, const void* container ) const		= 0;
		//! Allocate a new write iterator.
		//! @param	dest		Allocation address.
		//! @param	container	Pointer to container.
		//! @return				New write iterator.
		virtual FieldWriteIterator* CreateWriteIt( void* dest, const void* container ) const	= 0;
		//! Deallocate an existing field read iterator.
		//! @param	it			Read iterator to delete.
		virtual void DestructIt( FieldReadIterator* it )	= 0;
		//! Deallocate an existing field write iterator.
		//! @param	it			Write iterator to delete.
		virtual void DestructIt( FieldWriteIterator* it )	= 0;
	};

	namespace detail
	{
		//! Wrapper class used to automatically determine container types.
		template< typename TYPE, typename READ_IT, typename WRITE_IT >
		class FieldContainer_Impl :
			public FieldContainer
		{
		/***** Public Methods *****/
		public:
			Uint32 GetReadItAllocSize( void ) const { return sizeof( READ_IT ); }
			Uint32 GetWriteItAllocSize( void ) const { return sizeof( WRITE_IT ); }
			FieldReadIterator* CreateReadIt( void* dest, const void* container ) const { return new (dest) READ_IT((TYPE*)container); }
			FieldWriteIterator* CreateWriteIt( void* dest, const void* container ) const { return new (dest) WRITE_IT((TYPE*)container); }
			void DestructIt( FieldReadIterator* it ) { ((READ_IT*)it)->READ_IT::~READ_IT(); }
			void DestructIt( FieldWriteIterator* it ) { ((WRITE_IT*)it)->WRITE_IT::~WRITE_IT(); }
		};

		// No container factory is created by default for all field types
		template< typename TYPE >
		inline FieldContainer* CreateContainer( TYPE& )
		{
			return NULL;
		}
	}
}

#include "FieldContainer.inl"

//! Create a new read iterator on the stack.
//! Use CBL_DEL_FIELD_IT to delete.
#define CBL_NEW_FIELD_READIT( field_cont, container )\
	field_cont->CreateReadIt( _alloca( field_cont->GetReadItAllocSize() ), container )

//! Create a new write iterator on the stack.
//! Use CBL_DEL_FIELD_IT to delete.
#define CBL_NEW_FIELD_WRITEIT( field_cont, container )\
	field_cont->CreateWriteIt( _alloca( field_cont->GetWriteItAllocSize() ), container )

//! Delete an existing field iterator.
#define CBL_DEL_FIELD_IT( field_cont, it )\
	field_cont->DestructIt( it )

//! Create a loop for reading field container values.
#define CBL_FOREACH_READ_FIELD_BEGIN( field_cont, name, container )\
	{ cbl::FieldReadIterator* name = CBL_NEW_FIELD_READIT( field_cont, container );\
	for( ; name->IsValid(); name->IncNext() )

//! End for loop.
#define CBL_FOREACH_FIELD_END( field_cont, name )\
	CBL_DEL_FIELD_IT( field_cont, name ); }

#endif // __CBL_FIELDCONTAINER_H_
