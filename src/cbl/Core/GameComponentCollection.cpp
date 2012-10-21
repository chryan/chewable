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
 * @file GameComponentCollection.h
 * @brief Container class for game components.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Core/GameComponentCollection.h"
#include "cbl/Core/GameComponent.h"
#include "cbl/Core/DrawableGameComponent.h"
#include "cbl/Debug/Assert.h"

using namespace cbl;

GameComponentCollection::GameComponentCollection()
{
}

GameComponentCollection::~GameComponentCollection()
{
}

void GameComponentCollection::Add( GameComponent * const component, bool init )
{
	CBL_ASSERT_TRUE( component );
	mComponentList.push_back( component );
	
	// Raise component added event.
	OnComponentAdded( component );

	if( init )
		component->Initialise();
}

void GameComponentCollection::Add( DrawableGameComponent * const component, bool init )
{
	CBL_ASSERT_TRUE( component );
	mComponentList.push_back( component );
	
	// Raise component added event.
	OnComponentAdded( component );
	// Raise drawable component added event.
	OnDrawableAdded( component );

	if( init )
		component->Initialise();
}

void GameComponentCollection::Remove( GameComponent * const component, bool shutdown )
{
	if( shutdown )
		component->Shutdown();

	CBL_ASSERT_TRUE( component );
	mComponentList.remove( component );

	// Raise component removed event.
	OnComponentRemoved( component );
}

void GameComponentCollection::Remove( DrawableGameComponent * const component, bool shutdown )
{
	if( shutdown )
		component->Shutdown();

	CBL_ASSERT_TRUE( component );
	mComponentList.remove( component );

	// Raise component removed event.
	OnComponentRemoved( component );
	// Raise drawable component removed event.
	OnDrawableRemoved( component );
}

//! @brief Clear the component collection of all components.
void GameComponentCollection::clear( void )
{
	mComponentList.clear();
}
