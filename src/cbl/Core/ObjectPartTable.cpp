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
 * @file ObjectPartTable.cpp
 * @brief Object component table.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/ObjectPartTable.h"
#include "cbl/Core/ObjectPart.h"
#include "cbl/Core/Object.h"
#include "cbl/Debug/Logging.h"
#include "cbl/Reflection/EntityManager.h"

using namespace cbl;

ObjectPartTable::ObjectPartTable( Parts& parts )
: mParts( parts )
, mParent( NULL )
{
}

ObjectPartTable::~ObjectPartTable()
{
}

ObjectPart* ObjectPartTable::Add( const CName& type, bool init )
{
	ObjectPart* part = Get( type );
	bool added = part != NULL;

	if( !part ) part = static_cast< ObjectPart* >( CBL_ENT.New( type ) );
	if( !part ) {
		LOG_ERROR( "Unable to create object part: " << type.Text << ". Type not registered." );
		return NULL;
	}

	part->Object = mParent;

	if( !added ) mParts.push_back( part );
	if( init ) InitPart( part );

	return part;
}

ObjectPart* ObjectPartTable::Get( const CName& type ) const
{
	for( size_t i = 0; i < mParts.size(); ++i ) {
		ObjectPart* part = mParts[i];
		if( part->GetType().Name == type )
			return part;
	}

	return NULL;
}

void ObjectPartTable::Remove( const CName& type )
{
	CBL_FOREACH( Parts, it, mParts ) {
		if( (*it)->GetType().Name == type ) {
			(*it)->Shutdown();
			CBL_ENT.Delete( *it );
			mParts.erase( it );
			return;
		}
	}

	LOG_ERROR( type << " does not exist in " << mParent->GetName() << "." );
}

void ObjectPartTable::Initialise( void )
{
	for( size_t i = 0; i < mParts.size(); ++i ) {
		if( !mParts[i]->mInitialised )
			InitPart( mParts[i] );
	}
}

void ObjectPartTable::InitPart( ObjectPart* part )
{
	if( !part ) return;

	if( !part->mInitialised ) {
		part->Initialise();
		part->mInitialised = true;
	}
}

bool ObjectPartTable::Add( ObjectPart* objPart )
{
	// Check if this object part type has already been added.
	if( Get( objPart->GetType().Name ) != NULL ) {
		LOG_ERROR( "Cannot add object part (" << objPart->GetType().Name << "): Already exists!" );
		return false;
	}

	objPart->Object = mParent;
	mParts.push_back( objPart );

	return true;
}

void ObjectPartTable::clear( void )
{
	for( size_t i = mParts.size(); i > 0; --i ) {
		ObjectPart* part = mParts[i-1];
		if( part->mInitialised ) {
			part->Shutdown();
			CBL_ENT.Delete( part );
		}
	}

	mParts.clear();
}
