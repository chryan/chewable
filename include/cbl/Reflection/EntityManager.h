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
 * @file EntityManager.h
 * @brief Entity type manager. Handles type registrations, news and deletes.
 */

#ifndef __CBL_ENTITYMANAGER_H_
#define __CBL_ENTITYMANAGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Singleton.h"
#include "cbl/Reflection/TypeDB.h"
#include "cbl/Reflection/Entity.h"

namespace cbl
{
	class CBL_API EntityManager :
		Noncopyable
	{
	/***** Types *****/
	public:
		//! Declare as singleton.
		CBL_DECL_SINGLETON( EntityManager );
		
	/***** Public Members *****/
	public:
		TypeDB Types;
		
	/***** Public Methods *****/
	public:
		//! Destructor.
		~EntityManager();
		//! Create new entity of a specific type.
		//! @tparam	TYPE	Entity type.
		//! @return			Pointer to new entity.
		template< typename TYPE >
		TYPE* New( void ) const;
		//! Create new entity of a specific type.
		//! @param	type	Entity type.
		//! @param	parent	Parent object pointer. Used by Entity::OnCreate
		//! @return			Pointer to new entity.
		void* New( const CName& type ) const;
		//! New entity implementation.
		//! @param	type	Entity type.
		//! @param	parent	Parent object pointer. Used by Entity::OnCreate
		//! @return			Pointer to new entity.
		void* New( const Type* type ) const;
		//! Delete an entity.
		//! @param	entity	Entity to delete.
		void Delete( EntityPtr entity ) const;
		
	/***** Private Methods *****/
	private:
		//! Constructor. Set as private to prevent instantiation.
		EntityManager();
	};
}

#include "EntityManager.inl"

#define CBL_ENT\
	::cbl::EntityManager::Instance()

#endif // __CBL_ENTITYMANAGER_H_
