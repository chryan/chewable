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
 * @file Entity.h
 * @brief Base entity for all entities that require typing.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_ENTITY_H_
#define __CBL_ENTITY_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/Type.h"

namespace cbl
{
	//! Base entity for all serialisable game objects.
	class CBL_API Entity
	{
	/***** Types *****/
	public:
		//! Pre-saved options.
		enum OPTIONS
		{
			O_NORMAL,
			O_SKIP,
			O_IGNORE_FIELDS,

			O_COUNT,
		};

	/***** Properties *****/
	public:
		//! Get entity type. Always assumes that mType was set.
		inline const Type& GetType( void ) const { return *mType; }

	/***** Public Members *****/
	public:
		//! Inline constructor.
		inline Entity() : mType( NULL ) {}
		//! Virtual destructor.
		virtual ~Entity() {}
		//! Called just before the internal representation of the entity changes.
		//! e.g. Before deserialisation.
		virtual OPTIONS OnPreChanged( void ) = 0;
		//! Called when the internal representation of the entity changes.
		//! e.g. After deserialisation.
		virtual void OnChanged( void ) = 0;
		//! Called when the entity is about to be saved.
		//! e.g. Before serialisation.
		virtual OPTIONS OnPreSaved( void ) const = 0;
		//! Called after the entity is saved.
		//! e.g. After serialisation.
		virtual void OnSaved( void ) const = 0;

	/***** Private Members *****/
	private:
		const Type*		mType;			//!< Pointer to type.
		friend class	EntityManager;	//!< Befriend entity manager.
	};

	//! Entity pointer type.
	typedef Entity*	EntityPtr;
}

//! Entity type test macro. Used to test for type dependencies at compile-time.
#define CBL_ENTITY_TYPETEST( baseType, childType )\
	static_cast< baseType* >( static_cast< childType* >( NULL ) )

#endif // __CBL_ENTITY_H_
