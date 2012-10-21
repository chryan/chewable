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

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/Object.h"
#include "cbl/Core/ObjectPart.h"

using namespace cbl;

ObjectPart::ObjectPart()
: Object( NULL )
, mInitialised( false )
{
}

ObjectPart::~ObjectPart()
{
}

void ObjectPart::OnObjectRenamed( const CName&, const CName& )
{
}

void ObjectPart::Initialise( void )
{
}

void ObjectPart::Shutdown( void )
{
}

Entity::OPTIONS ObjectPart::OnPreChanged( void )
{
	return Entity::O_NORMAL;
}

void ObjectPart::OnChanged( void )
{
}

Entity::OPTIONS ObjectPart::OnPreSaved( void ) const
{
	return Entity::O_NORMAL;
}

void ObjectPart::OnSaved( void ) const
{
}
