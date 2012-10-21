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
 * @file ObjectPart.h
 * @brief Base object component class.
 */

#ifndef __CBL_OBJECTPART_H_
#define __CBL_OBJECTPART_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Property.h"

namespace cbl
{
	//! @brief Base object component class.
	//! Inherit from this class to implement new object functionality.
	class CBL_API ObjectPart :
		public Entity,
		Noncopyable
	{
	/***** Properties *****/
	public:
		GETTER_AUTO( bool, Initialised );

	/***** Public Members *****/
	public:
		ObjectPtr		Object;

	/***** Public Methods *****/
	public:
		//! Called when the holding object has been renamed.
		virtual void OnObjectRenamed( const CName& oldName, const CName& newName );

	/***** Protected Methods *****/
	protected:
		//! Constructor.
		//! @param	object		Parent object.
		//! @param	game		Game reference.
		ObjectPart();
		//! Destructor.
		virtual ~ObjectPart();
		//! Object component initialisation method.
		//! Called by the component table when added.
		virtual void Initialise( void );
		//! Object component shutdown method.
		//! Called by the component table when removed.
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

	/***** Private Members *****/
	private:
		bool			mInitialised;		//!< Checks if object component has already been initialised.
		friend class	ObjectPartTable;	//!< Befriend component collection.
		friend class	TypeDB;				//!< Befriend type DB.
		friend class	EntityManager;		//!< Befriend the entity manager.
	};
}

//! Declare the object component's friends
#define CBL_OBJECT_PART_FRIENDS\
	friend class ::cbl::ObjectPartTable;\
	friend class ::cbl::TypeDB;

CBL_TYPE( cbl::ObjectPart, ObjectPart );

#endif // __CBL_OBJECTPART_H_
