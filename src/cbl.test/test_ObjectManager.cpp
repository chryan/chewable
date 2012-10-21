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
 * @file test_ObjectManager.cpp
 * @brief Unit testing for the object manager.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Core/Game.h>
#include <cbl/Core/ObjectManager.h>
#include <cbl/Core/Object.h>
#include <cbl/Core/ObjectPart.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

namespace cbl
{
	struct DummyAccessObjMgr {};
	template<>
	DummyAccessObjMgr* EntityManager::New<DummyAccessObjMgr>( void ) const
	{
		this->EntityManager::~EntityManager();
		this->EntityManager::EntityManager();
		CblRegistrar::RegisterCblTypes();
		return NULL;
	}
}
void ForceReconstructEntityManager_ObjMgr( void )
{
	EntityManager* em = const_cast<EntityManager*>( EntityManager::InstancePtr() );
	em->New<DummyAccessObjMgr>();
}

class TestObject :
	public Object
{
public:
	virtual void Serialise( const cbl::FileInfo & ) const {}
	virtual void Deserialise( const cbl::FileInfo & ) {}

	int		Integer;

protected:
	TestObject() {}

	virtual void Initialise( void ) {
		Integer = -99;
	}

	virtual void Shutdown( void ) {
	}

	CBL_OBJECT_FRIENDS;
};

class TestObjectPart :
	public cbl::ObjectPart
{
public:
	virtual ~TestObjectPart()
	{
		std::cout << "Deleted TestObjectPart.\n";
	}

	virtual void Serialise( const cbl::FileInfo & ) const {}
	virtual void Deserialise( const cbl::FileInfo & ) {}

	int GetNumber20( void ) const { return 20; }

protected:
	TestObjectPart()
	{
		std::cout << "Created TestObjectPart.\n";
	}

	virtual void Initialise( void ) {
	}

	virtual void Shutdown( void ) {
	}

	CBL_OBJECT_PART_FRIENDS;
};

CBL_TYPE( TestObject, TestObject );
CBL_TYPE( TestObjectPart, TestObjectPart );

class ObjectManagerTestFixture :
	public ::testing::Test
{
public:
	ObjectManagerTestFixture()
		: game( "Game" )
		, objFactory( game.Objects )
	{
	}

protected:
	void SetUp()
	{
		CBL_ENT.Types.Create<TestObject>();
		CBL_ENT.Types.Create<TestObjectPart>();
	}

	void TearDown()
	{
		game.Objects.ForceFullPurge();
		ForceReconstructEntityManager_ObjMgr();
	}
	
	Game			game;
	ObjectManager&	objFactory;
};

TEST_F( ObjectManagerTestFixture, CreateDestroyTemplated )
{
	Object * obj = NULL;
	// Test for when string name goes out of scope
	{
		String objName = "Awesome";
		// Test if object creates.
		obj = objFactory.Create<TestObject>( objName.c_str() );
	}

	ASSERT_TRUE( objFactory.Get<TestObject>( "Awesome" ) != NULL );
	ASSERT_TRUE( objFactory.Get<TestObject>( "Doesn't Exist!" ) == NULL );

	TestObject * testObj = objFactory.Get<TestObject>( "Awesome" );
	testObj->Integer = 10;
	ASSERT_EQ( objFactory.Get<TestObject>( "Awesome" )->Integer, 10 );

	// Test if object deletes.
	objFactory.Destroy( "Awesome" );
	ASSERT_TRUE( objFactory.IsDestroying( "Awesome" ) );
	ASSERT_TRUE( objFactory.IsDestroying( obj ) );
	objFactory.Purge();

	ASSERT_TRUE( objFactory.Get<TestObject>( "Awesome" ) == NULL );
	ASSERT_FALSE( objFactory.IsDestroying( "Awesome" ) );
}

TEST_F( ObjectManagerTestFixture, ComponentCreateDestroyTemplated )
{
	Object * o = NULL;
	// Test for when string name goes out of scope
	{
		String objName = "Awesome";
		// Test if component exists.
		o = objFactory.Create<TestObject>( objName.c_str() );
	}

	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() == NULL );
	o->Parts.Add<TestObjectPart>();
	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() != NULL );

	// Test component functionality.
	ASSERT_EQ( o->Parts.Get<TestObjectPart>()->GetNumber20(), 20 );

	o->Parts.Remove<TestObjectPart>();
	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() == NULL );
}

TEST_F( ObjectManagerTestFixture, ObjectRenaming )
{
	Object * o = objFactory.Create<TestObject>( "Awesome" );

	objFactory.Rename( "Awesome", "notSoAwesome" );

	ASSERT_TRUE( objFactory.Get( "notSoAwesome" ) != NULL );
	ASSERT_TRUE( objFactory.Get( "Awesome" ) == NULL );

	objFactory.Rename( o, "AwesomeAgain" );
	
	ASSERT_TRUE( objFactory.Get( "AwesomeAgain" ) != NULL );
	ASSERT_TRUE( objFactory.Get( "Awesome" ) == NULL );
	ASSERT_TRUE( objFactory.Get( "notSoAwesome" ) == NULL );
}

TEST_F( ObjectManagerTestFixture, CreateDestroyRegistry )
{	
	Object * obj = objFactory.Create( "TestObject", "Awesome" );
	ASSERT_TRUE( obj != NULL );
	ASSERT_TRUE( objFactory.Create( "NonExistantObject", "None!" ) == NULL );

	ASSERT_TRUE( objFactory.Get( "Awesome" ) != NULL );
	ASSERT_TRUE( objFactory.Get( "Doesn't Exist!" ) == NULL );

	TestObject * testObj = static_cast< TestObject * >( objFactory.Get( "Awesome" ) );
	testObj->Integer = 10;
	{
		TestObject * testObj2 = static_cast< TestObject * >( objFactory.Get( "Awesome" ) );
		ASSERT_EQ( testObj2->Integer, 10 );
	}
	
	// Test registry's reverse lookup.
	ASSERT_EQ( ((EntityPtr)obj)->GetType().Name, cbl::TypeCName<TestObject>() );

	// Test if object deletes.
	objFactory.Destroy( "Awesome" );
	ASSERT_TRUE( objFactory.IsDestroying( "Awesome" ) );
	ASSERT_TRUE( objFactory.IsDestroying( obj ) );
	objFactory.Purge();

	ASSERT_FALSE( objFactory.Get( "Awesome" ) );
	ASSERT_FALSE( objFactory.IsDestroying( "Awesome" ) );
}

TEST_F( ObjectManagerTestFixture, ComponentCreateDestroyRegistry )
{
	// Test if component exists.
	TestObject * o = objFactory.Create<TestObject>( "Awesome" );
	ASSERT_TRUE( o->Parts.Get( "TestObjectPart" ) == NULL );
	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() == NULL );
	o->Parts.Add( "TestObjectPart" );

	ASSERT_TRUE( o->Parts.Get( "TestObjectPart" ) != NULL );
	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() != NULL );

	// Test component functionality.
	ASSERT_EQ( static_cast< TestObjectPart * >( o->Parts.Get("TestObjectPart") )->GetNumber20(), 20 );
	ASSERT_EQ( o->Parts.Get<TestObjectPart>()->GetNumber20(), 20 );
	
	// Test object registry's reverse lookup
	//ASSERT_EQ( o->GetType().Name, cbl::TypeCName<TestObject>() );
	//ASSERT_EQ( o->Parts.Get<TestObjectPart>()->GetType().Name, cbl::TypeCName<TestObjectPart>() );

	o->Parts.Remove( "TestObjectPart" );
	ASSERT_TRUE( o->Parts.Get( "TestObjectPart" ) == NULL );
	ASSERT_TRUE( o->Parts.Get<TestObjectPart>() == NULL );
}


TEST_F( ObjectManagerTestFixture, NameDuplicate_Test )
{
	ObjectPtr o1 = objFactory.Create<Object>( "TestObject" );
	ObjectPtr o2 = objFactory.Create<Object>( "TestObject" );
	ObjectPtr o3 = objFactory.Create<Object>( "TestObject0" );
	ObjectPtr o4 = objFactory.Create<Object>( "TestObject1" );
	ASSERT_TRUE( o1 != NULL && o2 != NULL && o3 != NULL && o4 != NULL );

	ASSERT_STREQ( o1->GetName().c_str(), "TestObject" );
	ASSERT_STREQ( o2->GetName().c_str(), "TestObject0" );
	ASSERT_STREQ( o3->GetName().c_str(), "TestObject1" );
	ASSERT_STREQ( o4->GetName().c_str(), "TestObject2" );

	ObjectPtr noName1 = objFactory.Create<Object>( "" );
	ObjectPtr noName2 = objFactory.Create<Object>( "" );
	ASSERT_STREQ( noName1->GetName().c_str(), ObjectManager::sDefaultObjectName );
	ASSERT_STREQ( noName2->GetName().c_str(), ( String( ObjectManager::sDefaultObjectName ) + "0" ).c_str() );

	ObjectPtr numName1 = objFactory.Create<Object>( "0" );
	ObjectPtr numName2 = objFactory.Create<Object>( "0" );
	ASSERT_STREQ( numName1->GetName().c_str(), "0" );
	ASSERT_STREQ( numName2->GetName().c_str(), "1" );
}
