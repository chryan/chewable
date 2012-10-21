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
 * @file Object.h
 * @brief Object class.
 */

#ifndef __CBL_OBJECT_H_
#define __CBL_OBJECT_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/CName.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Property.h"
#include "cbl/Core/ObjectPartTable.h"
#include "cbl/Reflection/Entity.h"

// External Dependencies //
#include <unordered_set>

namespace cbl
{
	typedef Uint32 ObjectID;
	//! @brief Base object class.
	//! See ObjectManager for usage example.
	class CBL_API Object :
		public Entity,
		Noncopyable
	{
	public:
		typedef std::unordered_set< CName >	GroupNames;

	/***** Properties *****/
	public:
		GETTER_AUTO( ObjectID, ID );			//!< Get object's ID.
		GETTER_AUTO( bool, Initialised );		//!< Get object initialised.
		GETTER_AUTO_CREF( GroupNames, Groups );	//!< Get object groups.
		//! Get object's name.
		inline const String& GetName( void ) const { return mName.GetText(); }
		//! Get object's hashed name value.
		inline HashValue GetHashValue( void ) const { return mName.GetHash(); }

	/***** Public Members *****/
	public:
		ObjectPartTable		Parts;		//!< Component collection.
		
	/***** Protected Methods *****/
	protected:
		//! Protected constructor.
		//! We only want the ObjectManager instantiating this.
		//! @param	hashName	Object's hash name.
		Object();
		// Destructor.
		virtual ~Object();
		//! Object initialisation method.
		//! Called by the object manager when created.
		virtual void Initialise( void );
		//! Object shutdown method.
		//! Called by the object manager when destroyed.
		virtual void Shutdown( void );
		//! Called just before the internal representation of the entity changes.
		//! e.g. Before deserialisation.
		virtual Entity::OPTIONS OnPreChanged( void );
		//! Called when the internal representation of the entity changes.
		//! e.g. After deserialisation.
		virtual void OnChanged( void );
		//! Called when the entity is about to be saved.
		//! e.g. Before serialisation.
		virtual Entity::OPTIONS OnPreSaved( void ) const;
		//! Called after the entity is saved.
		//! e.g. After serialisation.
		virtual void OnSaved( void ) const;

	private:
		typedef std::vector< ObjectPart* >	PartList;
		
	/***** Private Members *****/
	private:
		bool			mInitialised;		//!< Checks if object has already been initialised.
		ObjectID		mID;				//!< Object ID. Assigned by the object manager.
		ObjectManager*	mObjectManager;		//!< Parent object manager.
		Hash			mName;				//!< Name. Set when object factory instantiates this object.
		PartList		mParts;				//!< Actual object part list.
		GroupNames		mGroups;			//!< Object's groups.
		friend class	CblRegistrar;		//!< Befriend the registrar.
		friend class	ObjectManager;		//!< Befriend object factory.
		friend class	ObjectGroups;		//!< Befriend object groups.
		friend class	TypeDB;				//!< Befriend the type DB.
		friend class	EntityManager;		//!< Befriend the entity manager.
	};
}

//! Declare the object's friends
#define CBL_OBJECT_FRIENDS\
	friend class ::cbl::ObjectManager;\
	friend class ::cbl::ObjectGroups;\
	friend class ::cbl::TypeDB;

CBL_TYPE( cbl::Object, Object );

#endif // __CBL_OBJECT_H_
