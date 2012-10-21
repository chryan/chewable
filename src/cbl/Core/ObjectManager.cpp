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
 * @file ObjectManager.cpp
 * @brief Object factory class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/ObjectManager.h"
#include "cbl/Util/FileSystem.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

// Using 'this' is fine because the object groups only needs it to store the reference.
#pragma warning( disable : 4355 )

using namespace cbl;

const Char* ObjectManager::sDefaultObjectName = "NewObject";

ObjectManager::ObjectManager()
: mDestroyAll( false )
{
	Groups.mObjectMgr = this;
}

ObjectManager::~ObjectManager()
{
	ForceFullPurge();
}

ObjectPtr ObjectManager::Create( const CName& type, const CName& name, bool init )
{
	EntityPtr newEnt = (EntityPtr)CBL_ENT.New( type );
	if( !newEnt ) {
		LOG_ERROR( "Cannot create object (" << name << "): Invalid type (" << type << ")." );
		return NULL;
	}

	ObjectPtr newObj = static_cast<ObjectPtr>(newEnt);
	newObj->mName = name.Hash == 0 ? sDefaultObjectName : name;

	if( !Add( newObj ) ) {
		CBL_ENT.Delete( newEnt );
		return NULL;
	}

	if( init ) InitObject( newObj );
	return newObj;
}

void ObjectManager::Destroy( ObjectID id )
{
	if( id >= mObjectList.size() || mObjectList[id] == NULL ) {
		LOG_ERROR( "Object ID not found: " << id );
		return;
	}
	mObjectsToDestroy.push_back( id );
}

void ObjectManager::DestroyAll( void )
{
	mDestroyAll = true;
}

bool ObjectManager::Rename( const Hash& oldName, const Hash& newName )
{
	if( oldName == newName ) {
		LOG_ERROR( "Object not renamed. Same name supplied." );
		return false;
	}

	ObjectNameTable::iterator findit = mObjectNameTable.find( CName( oldName ) );
	if( findit == mObjectNameTable.end() ) {
		LOG_ERROR( "Object (" << oldName << ") not found." );
		return false;
	}

	if( mObjectNameTable.find( CName( newName ) ) != mObjectNameTable.end() ) {
		LOG_ERROR( "Object (" << newName << ") name already exists." );
		return false;
	}

	// Trigger the object renaming events.
	ObjectPtr obj = mObjectList[findit->second];

	CBL_FOREACH( ObjectPartTable, it, obj->Parts )
		(*it)->OnObjectRenamed( CName( oldName ), CName( newName ) );
	OnObjectRenamed( CName( oldName ), CName( newName ) );

	// Remove and re-add the object from the table.
	mObjectNameTable.erase( findit );
	// Reassign the object's name.
	obj->mName = newName;
	//! Reinsert object into the table.
	mObjectNameTable.insert( std::make_pair( CName( obj->mName ), obj->GetID() ) );

	return true;
}

void ObjectManager::InitObject( ObjectPtr obj )
{
	if( !obj ) return;

	if( !obj->mInitialised ) {
		obj->Initialise();
		obj->mInitialised = true;
	}
	
	obj->Parts.Initialise();
}

void ObjectManager::Purge( void )
{
	if( mDestroyAll ) {
		ForceFullPurge();
	}
	else {
		for( size_t i = 0; i < mObjectsToDestroy.size(); ++i ) {
			ObjectID id = mObjectsToDestroy[i];
			if( id < mObjectList.size() && mObjectList[id] != NULL ) {
				ObjectPtr del = mObjectList[id];
				OnObjectDestroy( del );
				// Ungroup object.
				Groups.Ungroup( del );
				// Remove it from the object name table.
				mObjectNameTable.erase( CName( del->mName ) );
				// Delete the object.
				del->Parts.clear();
				del->Shutdown();
				CBL_ENT.Delete( (EntityPtr)del );
				// Put the ID in the unused list.
				mUnusedIDs.push_back( id );
				mObjectList[id] = NULL;
			}
		}
		mObjectsToDestroy.clear();
	}
}

void ObjectManager::ForceFullPurge( void )
{
	Groups.Clear();

	for( size_t i = 0; i < mObjectList.size(); ++i ) {
		if( mObjectList[i] != NULL ) {
			OnObjectDestroy( mObjectList[i] );
			mObjectList[i]->Parts.clear();
			mObjectList[i]->Shutdown();
			CBL_ENT.Delete( (EntityPtr)mObjectList[i] );
			mObjectList[i] = NULL;
		}
	}

	mObjectList.clear();
	mUnusedIDs.clear();
	mObjectsToDestroy.clear();
	mObjectNameTable.clear();
	mDestroyAll = false;
}

void ObjectManager::AssignAvailableObjectName( Hash& name ) const
{
	ObjectNameTable::const_iterator findit = mObjectNameTable.find( CName( name ) );
	if( findit == mObjectNameTable.end() && (name.GetText().length() > 0) ) return;

	String origName = name.GetText().length() > 0 ? name.GetText() : sDefaultObjectName;
	Int32 postfix = 0;

	if( origName.back() >= '0' && origName.back() <= '9' ) {
		const Char* endPt = origName.c_str() + origName.length() - 1;
		// Get the point where the object's number starts
		while( endPt >= origName.c_str() - 1 ) {
			if( endPt >= origName.c_str() && *endPt >= '0' && *endPt <= '9' ) {
				--endPt;
			} else {
				std::istringstream ss( endPt+1 );
				ss >> postfix;
				++postfix;
				origName = String( origName.c_str(), endPt+1 - origName.c_str() );
				break;
			}
		}
	}

	while( findit != mObjectNameTable.end() ) {
		std::stringstream newName;
		newName << origName << postfix++;
		name = newName.str().c_str();
		findit = mObjectNameTable.find( CName( name ) );
	}
}

bool ObjectManager::Add( ObjectPtr obj )
{
	// Assign an unused ID if there is one.
	if( mUnusedIDs.size() > 0 ) {
		obj->mID = mUnusedIDs.back();
		mUnusedIDs.pop_back();
		mObjectList[obj->mID] = obj;
	} else { // Otherwise assign a new ID.
		mObjectList.push_back( obj );
		obj->mID = mObjectList.size()-1;
	}

	AssignAvailableObjectName( obj->mName );

	obj->mObjectManager = this;
	mObjectNameTable.insert( std::make_pair( CName( obj->mName ), obj->GetID() ) );
	OnObjectCreate( obj );

	return true;
}

void ObjectManager::PreRename( ObjectPtr obj )
{
	mObjectNameTable.erase( CName( obj->mName ) );
}

void ObjectManager::PostRename( ObjectPtr obj )
{
	mObjectNameTable.insert( std::make_pair( CName( obj->mName ), obj->GetID() ) );
}

template<> 
ObjectPtr ObjectManager::LoadObjectFromFile<BinaryDeserialiser>( const cbl::Char* file, const cbl::Char* name, bool init )
{
	std::ifstream fs;
	fs.open( file, std::ios_base::binary );

	if( !fs.is_open() ) {
		LOG_ERROR( "Unable to open object file for reading: " << file );
		return NULL;
	}

	BinaryDeserialiser bd;
	bd.SetStream( fs );

	ObjectPtr newObj = NULL;
	bool success = bd.DeserialisePtr( newObj );
	if( success ) {
		if( name ) newObj->mName = name;
		success = Add( newObj );
		if( !success ) {
			CBL_ENT.Delete( newObj );
			newObj = NULL;
		}
	}

	if( success ) {
		LOG( "Object (" << newObj->GetName() << ") loaded from file: " << file );
	} else {
		LOG_ERROR( "Unable to deserialise from binary file: " << file );
	}

	fs.close();

	if( init )
		InitObject( newObj );
	return newObj;
}

template<> 
void ObjectManager::SaveObjectToFile<BinarySerialiser>( const cbl::Char* file, ObjectPtr obj ) const
{
	if( !obj ) {
		LOG_ERROR( "No object to write to binary file: " << file );
		return;
	}

	std::ofstream fs;
	fs.open( file, std::ios_base::binary );

	if( !fs.is_open() ) {
		LOG_ERROR( "Unable to open object file for writing: " << file );
		return;
	}

	BinarySerialiser bs;
	bs
		.SetStream( fs )
		.Serialise( *obj );

	LOG( "Object (" << obj->GetName() << ") saved to file: " << file );

	fs.close();
}
