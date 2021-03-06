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
 * @file Object.cpp
 * @brief Object class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/Object.h"
#include "cbl/Debug/Assert.h"

using namespace cbl;

Object::Object()
: Parts( mParts )
, mInitialised( false )
, mID(UINT_MAX)
, mObjectManager( NULL )
{
	Parts.mParent = this;
}

Object::~Object() 
{
	Parts.clear();
}

void Object::Initialise( void )
{
}

void Object::Shutdown( void )
{
}

Entity::OPTIONS Object::OnPreChanged( void )
{
	if( mObjectManager ) mObjectManager->PreRename( this );
	return Entity::O_NORMAL;
}

void Object::OnChanged( void )
{
	for( size_t i = 0; i < mParts.size(); ++i )
		mParts[i]->Object = this;

	if( mObjectManager ) mObjectManager->PostRename( this );
}

Entity::OPTIONS Object::OnPreSaved( void ) const
{
	return Entity::O_NORMAL;
}

void Object::OnSaved( void ) const
{
}
