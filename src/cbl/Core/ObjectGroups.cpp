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
 * @file ObjectGroups.cpp
 * @brief Object groups definitions.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/ObjectGroups.h"
#include "cbl/Core/Object.h"
#include "cbl/Core/ObjectManager.h"
#include "cbl/Debug/Logging.h"

using namespace cbl;

ObjectGroups::ObjectGroups()
: mObjectMgr( NULL )
{
}

ObjectGroups::~ObjectGroups()
{
}

void ObjectGroups::Add( const Hash& groupName, const CName& objName )
{
	if( !mObjectMgr ) return; Add( groupName, mObjectMgr->Get( objName ) );
}

void ObjectGroups::Add( const Hash& groupName, Object* obj )
{
	if( !mObjectMgr ) return;

	// Make sure the objects are the same and that the object exists in the mgr.
	ObjectID id = obj->GetID();
	if( mObjectMgr->Get( id ) == obj ) {
		GroupTable::iterator result = mGroups.find( groupName );
		if( result == mGroups.end() )
			result = mGroups.insert( std::make_pair( groupName, ObjectIDList() ) ).first;

		for( size_t i = 0; i < result->second.size(); ++i ) {
			if( result->second[i] == id ) {
				LOG_WARNING( "Object " << obj->GetName() << " is already in group: " << groupName.GetText() );
				return;
			}
		}
		result->second.push_back( id );
		obj->mGroups.insert( CName( result->first ) );
	}
}

void ObjectGroups::Add( const Hash& groupName, ObjectID id )
{
	if( !mObjectMgr ) return; Add( groupName, mObjectMgr->Get( id ) );
}

void ObjectGroups::Remove( const Hash& groupName, const CName& objName )
{
	if( !mObjectMgr ) return; Add( groupName, mObjectMgr->Get( objName ) );
}

void ObjectGroups::Remove( const Hash& groupName, Object* obj )
{
	if( !mObjectMgr ) return;

	GroupTable::iterator findit = mGroups.find( groupName );
	if( findit == mGroups.end() )
		return;

	ObjectID id = obj->GetID();
	if( mObjectMgr->Get( id ) == obj ) {
		obj->mGroups.erase( CName( findit->first ) );
		for( size_t i = 0; i < findit->second.size(); ++i ) {
			if( findit->second[i] == id ) {
				findit->second[i] = findit->second[findit->second.size()-1];
				findit->second.pop_back();
				break;
			}
		}
	}
}

void ObjectGroups::Remove( const Hash& groupName, ObjectID id )
{
	if( !mObjectMgr ) return; Add( groupName, mObjectMgr->Get( id ) );
}

const ObjectIDList& ObjectGroups::Get( const Hash& groupName ) const
{
	return mGroups[ groupName ];
}

void ObjectGroups::Ungroup( const CName& objName )
{
	if( !mObjectMgr ) return; Ungroup( mObjectMgr->Get( objName ) );
}

void ObjectGroups::Ungroup( Object* obj )
{
	if( !mObjectMgr ) return;

	ObjectID id = obj->GetID();
	// Make sure the object exists.
	if( mObjectMgr->Get( id ) == obj ) {
		CBL_FOREACH( Object::GroupNames, it, obj->mGroups ) {
			ObjectIDList& idlist = mGroups[*it];
			for( size_t i = 0; i < idlist.size(); ++i ) {
				if( idlist[i] == id ) {
					idlist[i] = idlist[idlist.size()-1];
					idlist.pop_back();
					break;
				}
			}
		}

		obj->mGroups.clear();
	}
}

void ObjectGroups::Ungroup( ObjectID id )
{
	if( !mObjectMgr ) return; Ungroup( mObjectMgr->Get( id ) );
}

void ObjectGroups::Clear( void )
{
	CBL_FOREACH( GroupTable, it, mGroups ) {
		for( size_t i = 0; i < it->second.size(); ++i ) {
			if( ObjectPtr obj = mObjectMgr->Get( it->second[i] ) )
				obj->mGroups.clear();
		}
		it->second.clear();
	}
	mGroups.clear();
}

void ObjectGroups::Clear( const Hash& groupName )
{
	GroupTable::iterator findit = mGroups.find( groupName );
	if( findit == mGroups.end() )
		return;

	ObjectIDList& idlist = findit->second;
	CName gname = CName( groupName );
	for( size_t i = 0; i < idlist.size(); ++i ) {
		if( ObjectPtr obj = mObjectMgr->Get( idlist[i] ) )
			obj->mGroups.erase( gname );
	}
	idlist.clear();
}
