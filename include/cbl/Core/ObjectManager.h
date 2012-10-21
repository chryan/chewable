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
 * @file ObjectManager.h
 * @brief Object factory class.
 */

#ifndef __CBL_OBJECTMANAGER_H_
#define __CBL_OBJECTMANAGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Core/Object.h"
#include "cbl/Core/Services.h"
#include "cbl/Core/ObjectGroups.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/SharedPtr.h"
#include "cbl/Util/WeakPtr.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Singleton.h"
#include "cbl/Serialisation/BinaryDeserialiser.h"
#include "cbl/Serialisation/BinarySerialiser.h"

// External Dependencies //
#include <map>
#include <unordered_map>

namespace cbl
{
	/***** Types *****/
	typedef Object * ObjectPtr;

	namespace E
	{
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
		typedef cbl::Event<void(ObjectPtr)>					ObjectChange;		//!< params: object pointer
		typedef cbl::Event<void(const Hash&, const Hash&)>	ObjectRenamed;		//!< params: old name, new name
#else
		typedef cbl::Event1<void,ObjectPtr>					ObjectChange;		//!< params: object pointer
		typedef cbl::Event2<void,const Hash&,const Hash&)>	ObjectRenamed;		//!< params: old name, new name
#endif
		typedef ObjectChange ObjectCreate;
		typedef ObjectChange ObjectDestroy;
	}

	//! Object manager. 
	class CBL_API ObjectManager :
		Noncopyable
	{
	/***** Public Static Constants *****/
	public:
		static const Char* sDefaultObjectName;

	/***** Public Members *****/
	public:
		ObjectGroups		Groups;		//!< Object groups.
		
	/***** Events *****/
	public:
		E::ObjectCreate		OnObjectCreate;		//!< Triggered when an object is created (before initialisation).
		E::ObjectDestroy	OnObjectDestroy;	//!< Triggered when an object is destroyed (before shutdown).
		E::ObjectRenamed	OnObjectRenamed;	//!< Triggered when an object is renamed.

	/***** Public Methods *****/
	public:
		//! Constructor.
		ObjectManager();
		//! Destructor.
		~ObjectManager();
		//! Create an uninitialised object (used for custom object manipulation before initialisation).
		//! @tparam	OBJECT_TYPE	Uninitialised object type.
		//! @param	name		Object name.
		//! @param	init		Initialise object.
		//! @return				Pointer to the newly created object. NULL if error creating object.
		template< typename OBJECT_TYPE >
		OBJECT_TYPE* Create( const CName& name, bool init = true );
		//! Create an uninitialised object (used for custom object manipulation before initialisation).
		//! @param	type		Object type.
		//! @param	name		Object name.
		//! @param	init		Initialise object.
		//! @return				Pointer to the newly created object. NULL if error creating object.
		ObjectPtr Create( const CName& type, const CName& name, bool init = true );
		//! Deserialise an object from a file.
		//! @param	name		Object name.
		//! @param	file		Object file.
		//! @return				Pointer to newly created and deserialised object. NULL if error creating.
		template< typename DESERIALISER_TYPE >
		ObjectPtr LoadObjectFromFile( const Char* file, const Char* name = NULL, bool init = true );
		//! Save an object to a file using an object name.
		//! @param	name		Object name.
		//! @param	file		Object file.
		template< typename SERIALISER_TYPE >
		void SaveObjectToFile( const Char* file, const CName& name ) const;
		//! Save an object to a file using an object ID.
		//! @param	name		Object name.
		//! @param	file		Object file.
		template< typename SERIALISER_TYPE >
		void SaveObjectToFile( const Char* file, ObjectID id ) const;
		//! Save an object to a file using an object pointer.
		//! @param	name		Object name.
		//! @param	file		Object file.
		template< typename SERIALISER_TYPE >
		void SaveObjectToFile( const Char* file, ObjectPtr obj ) const;
		//! Get an existing object by its name.
		//! @tparam	OBJECT_TYPE	Object type.
		//! @param	name		Object name.
		//! @return				Pointer to the existing object (NULL if non-existent).
		template< typename OBJECT_TYPE >
		OBJECT_TYPE* Get( const CName& name ) const;
		//! Get an existing object by its name.
		//! @tparam	OBJECT_TYPE	Object type.
		//! @param	name		Object name.
		//! @return				Pointer to the existing object (NULL if non-existent).
		template< typename OBJECT_TYPE >
		OBJECT_TYPE* Get( ObjectID id ) const;
		//! Get an existing object by its name.
		//! @param	name		Object name.
		//! @return				Pointer to the existing object (NULL if non-existent).
		ObjectPtr Get( const CName& name ) const;
		//! Get an existing object by its name.
		//! @param	name		Object name.
		//! @return				Pointer to the existing object (NULL if non-existent).
		ObjectPtr Get( ObjectID id ) const;

		//! Destroy an existing object by its hashed name. Logs an error if object does not exist.
		//! @param	name		Object name.
		void Destroy( const CName& name );
		//! Destroy an existing object by its ID. Logs an error if object does not exist.
		//! @param	name		Object name.
		void Destroy( ObjectID id );
		//! Destroy an object by its pointer. Logs an error if object does not exist.
		//! @param	obj			Object pointer.
		void Destroy( const ObjectPtr obj );
		//! Destroy ALL objects.
		void DestroyAll( void );
		//! Check if an object is to be destroyed on next purge.
		//! @param	name		Object name.
		bool IsDestroying( const CName& name ) const;
		//! Check if an object is to be destroyed on next purge.
		bool IsDestroying( ObjectID id ) const;
		//! Check if an object is to be destroyed on next purge.
		bool IsDestroying( const ObjectPtr obj ) const;
		//! Rename object.
		//! @param	oldName		Old object name.
		//! @param	newName		New object name.
		bool Rename( const Hash& oldName, const Hash& newName );
		//! Rename object.
		//! @param	obj			Object to rename.
		//! @param	newName		New object name.
		bool Rename( const ObjectPtr obj, const Hash& newName );
		//! Perform the actual destruction on objects to be destroyed.
		void Purge( void );
		//! Force a full object purge (REMOVES ALL OBJECTS FROM OBJECT MANAGER).
		void ForceFullPurge( void );
		//! Get an available object name.
		void AssignAvailableObjectName( Hash& name ) const;
		//! Deserialises a single object from a dserialiser.
		template< typename OBJECT_TYPE >
		OBJECT_TYPE* DeserialiseObject( Deserialiser& deserialiser, bool init = true );

	/***** Object Iteration Methods *****/
	public:
		typedef std::unordered_map<CName,Uint32>::iterator					iterator;
		typedef std::unordered_map<CName,Uint32>::const_iterator			const_iterator;
		typedef std::unordered_map<CName,Uint32>::reverse_iterator			reverse_iterator;
		typedef std::unordered_map<CName,Uint32>::const_reverse_iterator	const_reverse_iterator;

		inline iterator begin( void ) { return mObjectNameTable.begin(); }
		inline iterator end( void ) { return mObjectNameTable.end(); }
		inline const_iterator begin( void ) const { return mObjectNameTable.begin(); }
		inline const_iterator end( void ) const { return mObjectNameTable.end(); }
		inline reverse_iterator rbegin( void ) { return mObjectNameTable.rbegin(); }
		inline reverse_iterator rend( void ) { return mObjectNameTable.rend(); }
		inline const_reverse_iterator rbegin( void ) const { return mObjectNameTable.rbegin(); }
		inline const_reverse_iterator rend( void ) const { return mObjectNameTable.rend(); }


	/***** Static Public Methods *****/
	public:
		//! Initialise an object and its components. Does nothing if already initialised.
		//! Components will be initialised even if object has been initialised.
		static void InitObject( ObjectPtr object );
		//! Add an externally constructed object to the object table.
		bool Add( ObjectPtr obj );
		//! Called when an object has changed internally.
		void PreRename( ObjectPtr obj );
		//! Called when an object has changed internally.
		void PostRename( ObjectPtr obj );

	/***** Private Members *****/
	private:
		typedef std::vector<ObjectPtr>				ObjectList;
		typedef std::vector<Uint32>					IDList;
		typedef std::unordered_map<CName,Uint32>	ObjectNameTable;
		bool				mDestroyAll;		//!< Destroy all objects?
		ObjectList			mObjectList;		//!< Full object list.
		ObjectNameTable		mObjectNameTable;	//!< Object name to ID table.
		IDList				mUnusedIDs;			//!< Unused object ID list.
		IDList				mObjectsToDestroy;	//!< Objects to destroy.
		friend class		Game;
		friend class		Object;
	};

	//! Binary object deserialiser.
	template<> 
	CBL_API ObjectPtr ObjectManager::LoadObjectFromFile<BinaryDeserialiser>( const Char* file, const Char* name, bool init );
	//! Binary object serialiser.
	template<> 
	CBL_API void ObjectManager::SaveObjectToFile<BinarySerialiser>( const Char* file, ObjectPtr obj ) const;
}

#include "ObjectManager.inl"

#endif // __CBL_OBJECTMANAGER_H_
