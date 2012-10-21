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
 * @file test_ObjectGroups.cpp
 * @brief Unit testing for the object grouping system.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/Game.h>
#include <cbl/Core/ObjectManager.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

namespace cbl
{
	struct DummyAccessObjGrp {};
	template<>
	DummyAccessObjGrp* EntityManager::New<DummyAccessObjGrp>( void ) const
	{
		this->EntityManager::~EntityManager();
		this->EntityManager::EntityManager();
		CblRegistrar::RegisterCblTypes();
		return NULL;
	}
}
void ForceReconstructEntityManager_ObjGrp( void )
{
	EntityManager* em = const_cast<EntityManager*>( EntityManager::InstancePtr() );
	em->New<DummyAccessObjGrp>();
}

class TestObject :
	public Object
{
public:
	virtual void Initialise( void ) {}
	virtual void Shutdown( void ) {}
	virtual void Serialise( const cbl::FileInfo & ) const {}
	virtual void Deserialise( const cbl::FileInfo & ) {}

	int		Integer;

	TestObject() : Integer(1) {}

	CBL_OBJECT_FRIENDS;
};

CBL_TYPE( TestObject, TestObject );

class ObjectGroupsTestFixture :
	public ::testing::Test
{
public:
	ObjectGroupsTestFixture()
		: game( "Game" ), objManager( game.Objects ) {
	}

protected:
	void SetUp() {
		CBL_ENT.Types.Create<TestObject>()
			.Base<cbl::Object>();
	}

	void TearDown() {
		objManager.ForceFullPurge();
		ForceReconstructEntityManager_ObjGrp();
	}
	
	Game			game;
	ObjectManager	& objManager;
};

TEST_F( ObjectGroupsTestFixture, AddRemoveGroupTest )
{
	const char* objNames[] = {
		"Object1",
		"Object2",
		"Object3",
		"Object4",
		"Object5"
	};

	TestObject* objs[] = {
		objManager.Create<TestObject>( objNames[0] ),
		objManager.Create<TestObject>( objNames[1] ),
		objManager.Create<TestObject>( objNames[2] ),
		objManager.Create<TestObject>( objNames[3] ),
		objManager.Create<TestObject>( objNames[4] )
	};

	const ObjectIDList& group1 = objManager.Groups.Get( "Group1" );
	const ObjectIDList& group2 = objManager.Groups.Get( "Group2" );

	ASSERT_EQ( group1.size(), 0 );
	ASSERT_EQ( group2.size(), 0 );

	TestObject* obj = objManager.Get<TestObject>( "Object1" );
	
	objManager.Groups.Add( "Group1", objNames[0] );
	objManager.Groups.Add( "Group2", objNames[0] );
	objManager.Groups.Add( "Group1", objNames[1] );
	objManager.Groups.Add( "Group2", objNames[2] );

	ASSERT_EQ( objManager.Get<TestObject>( objNames[0] )->GetGroups().size(), 2 );
	ASSERT_EQ( objManager.Get<TestObject>( objNames[1] )->GetGroups().size(), 1 );
	ASSERT_EQ( objManager.Get<TestObject>( objNames[2] )->GetGroups().size(), 1 );
	
	ASSERT_EQ( objManager.Groups.Get( "Group1" ).size(), 2 );
	ASSERT_EQ( objManager.Groups.Get( "Group2" ).size(), 2 );

	objManager.Groups.Ungroup( "Object1" );
	ASSERT_TRUE( objManager.Get<TestObject>( objNames[0] )->GetGroups().size() == 0 );

	ASSERT_EQ( objManager.Groups.Get( "Group1" ).size(), 1 );
	ASSERT_EQ( objManager.Groups.Get( "Group2" ).size(), 1 );

	objManager.Groups.Clear( "Group1" );
	ASSERT_EQ( objManager.Get<TestObject>( objNames[1] )->GetGroups().size(), 0 );
	ASSERT_EQ( objManager.Groups.Get( "Group2" ).size(), 1 );
}

/*
TEST_F( ObjectGroupsTestFixture, DestroyObjectsInGroupTest )
{
	objManager.Create<TestObject>( "Object1" );
	objManager.Create<TestObject>( "Object2" );
	objManager.Create<TestObject>( "Object3" );

	const ObjectNameSet& names = objManager.Groups.Get( "DestroyGroup" );
	objManager.Groups.Add( "DestroyGroup", "Object1" );
	objManager.Groups.Add( "DestroyGroup", "Object2" );
	objManager.Groups.Add( "DestroyGroup", "Object3" );

	ASSERT_EQ( names.size(), 3 );
	objManager.Groups.DestroyObjectsInList( "DestroyGroup" );
	objManager.Purge();
	ASSERT_EQ( objManager.Groups.Get( "DestroyGroup" )->Size(), 0 );
	ASSERT_TRUE( objManager.Get( "Object1" ) == NULL );
	ASSERT_TRUE( objManager.Get( "Object2" ) == NULL );
	ASSERT_TRUE( objManager.Get( "Object3" ) == NULL );
}
*/