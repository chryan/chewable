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
 *	@file ObjectGroups.h
 *  @brief Object grouping system.
 */
 
#ifndef __CBL_OBJECTGROUPS_H_
#define __CBL_OBJECTGROUPS_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Hash.h"

// External Libraries //
#include <unordered_map>
#include <unordered_set>

namespace cbl
{
	/***** Types *****/
	typedef std::vector<Uint32>	ObjectIDList;	//!< Group name (hash) list.

	//! Object grouping system.
	//! New objects added from the ObjectManager are automatically added to the default group (sDefaultGroupName).
	//!
	//! Usage Example:
	//! @code
	//! 
	//! @endcode
	class CBL_API ObjectGroups :
		Noncopyable
	{
	/***** Public Methods *****/
	public:
		//! Constructor.
		ObjectGroups();
		//! Destructor.
		~ObjectGroups();
		//! Add object to group by name.
		void Add( const Hash& groupName, const CName& objName );
		//! Add object to group.
		void Add( const Hash& groupName, Object* obj );
		//! Add object to group by ID.
		void Add( const Hash& groupName, ObjectID id );
		//! Remove object from group by name.
		void Remove( const Hash& groupName, const CName& objName );
		//! Remove object from group.
		void Remove( const Hash& groupName, Object* obj );
		//! Remove object from group by ID.
		void Remove( const Hash& groupName, ObjectID id );
		//! Ungroup object by name.
		void Ungroup( const CName& objName );
		//! Ungroup object.
		void Ungroup( Object* obj );
		//! Ungroup object by ID.
		void Ungroup( ObjectID id );
		//! Get group. Creates the group if it does not exist.
		const ObjectIDList& Get( const Hash& groupName ) const;
		//! Clear all groups.
		void Clear( void );
		//! Clear specific group.
		void Clear( const Hash& groupName );

	/***** Private Types *****/
	private:
		typedef std::unordered_map<Hash, ObjectIDList> GroupTable;	//!< Object group table.

	/***** Private Members *****/
	private:
		ObjectManager*			mObjectMgr;		//!< Used to destroy object lists.
		mutable GroupTable		mGroups;		//!< Object groups table.
		friend class			ObjectManager;
	};
}

#endif // __CBL_OBJECTGROUPS_H_
