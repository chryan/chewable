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
 * @file test_Hash.cpp
 * @brief Unit testing for hash class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Core/GameStateManager.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

namespace cbl
{
	struct DummyAccessStates {};
	template<>
	DummyAccessStates* EntityManager::New<DummyAccessStates>( void ) const
	{
		this->EntityManager::~EntityManager();
		this->EntityManager::EntityManager();
		CblRegistrar::RegisterCblTypes();
		return NULL;
	}
}
void ForceReconstructEntityManager_States( void )
{
	EntityManager* em = const_cast<EntityManager*>( EntityManager::InstancePtr() );
	em->New<DummyAccessStates>();
}

class TestGameState : public GameState
{
protected:
	TestGameState() {}

public:
	virtual void Activate( void )
	{
		++actCount;
	}

	virtual void Deactivate( void )
	{
		++deactCount;
	}

	virtual void Pause( void )
	{
		++pauseCount;
	}

	virtual void Resume( void )
	{
		++resumeCount;
	}

	static cbl::Uint32 actCount;
	static cbl::Uint32 deactCount;
	static cbl::Uint32 pauseCount;
	static cbl::Uint32 resumeCount;

	CBL_GAMESTATE_FRIENDS;
};

CBL_TYPE( TestGameState, TestGameState );

cbl::Uint32 TestGameState::actCount		= 0;
cbl::Uint32 TestGameState::deactCount	= 0;
cbl::Uint32 TestGameState::pauseCount	= 0;
cbl::Uint32 TestGameState::resumeCount	= 0;

class GameStateManagerFixture : public ::testing::Test
{
private:
	void SetUp( void )
	{
		TestGameState::actCount		= 0;
		TestGameState::deactCount	= 0;
		TestGameState::pauseCount	= 0;
		TestGameState::resumeCount	= 0;

		CBL_ENT.Types.Create<TestGameState>();
	}

	void TearDown( void )
	{
		States.Update();
		ForceReconstructEntityManager_States();
	}

public:
	GameStateManager	States;
};

TEST_F( GameStateManagerFixture, StateIndividualTest )
{
	States.Push<TestGameState>();
	ASSERT_EQ( TestGameState::actCount, 0 );
	ASSERT_EQ( TestGameState::deactCount, 0 );
	ASSERT_EQ( TestGameState::pauseCount, 0 );
	ASSERT_EQ( TestGameState::resumeCount, 0 );
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 1 );
	ASSERT_EQ( TestGameState::deactCount, 0 );
	ASSERT_EQ( TestGameState::pauseCount, 0 );
	ASSERT_EQ( TestGameState::resumeCount, 1 );

	States.Push( "TestGameState" );
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 2 );
	ASSERT_EQ( TestGameState::deactCount, 0 );
	ASSERT_EQ( TestGameState::pauseCount, 1 );
	ASSERT_EQ( TestGameState::resumeCount, 2 );

	States.Push<TestGameState>();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 3 );
	ASSERT_EQ( TestGameState::deactCount, 0 );
	ASSERT_EQ( TestGameState::pauseCount, 2 );
	ASSERT_EQ( TestGameState::resumeCount, 3 );
	
	States.Pop();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 3 );
	ASSERT_EQ( TestGameState::deactCount, 1 );
	ASSERT_EQ( TestGameState::pauseCount, 3 );
	ASSERT_EQ( TestGameState::resumeCount, 4 );

	States.Add<TestGameState>( "TestPersistent" );
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 4 );
	ASSERT_EQ( TestGameState::deactCount, 1 );
	ASSERT_EQ( TestGameState::pauseCount, 3 );
	ASSERT_EQ( TestGameState::resumeCount, 5 );

	States.Pop();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 4 );
	ASSERT_EQ( TestGameState::deactCount, 2 );
	ASSERT_EQ( TestGameState::pauseCount, 4 );
	ASSERT_EQ( TestGameState::resumeCount, 6 );

	States.Push<TestGameState>();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 5 );
	ASSERT_EQ( TestGameState::deactCount, 2 );
	ASSERT_EQ( TestGameState::pauseCount, 5 );
	ASSERT_EQ( TestGameState::resumeCount, 7 );
	
	States.Remove( "TestPersistent" );
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 5 );
	ASSERT_EQ( TestGameState::deactCount, 3 );
	ASSERT_EQ( TestGameState::pauseCount, 6 );
	ASSERT_EQ( TestGameState::resumeCount, 7 );
	
	States.Remove( "TestPersistent" );
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 5 );
	ASSERT_EQ( TestGameState::deactCount, 3 );
	ASSERT_EQ( TestGameState::pauseCount, 6 );
	ASSERT_EQ( TestGameState::resumeCount, 7 );
	
	States.Pop();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 5 );
	ASSERT_EQ( TestGameState::deactCount, 4 );
	ASSERT_EQ( TestGameState::pauseCount, 7 );
	ASSERT_EQ( TestGameState::resumeCount, 8 );

	States.Pop();
	States.Update();
	ASSERT_EQ( TestGameState::actCount, 5 );
	ASSERT_EQ( TestGameState::deactCount, 5 );
	ASSERT_EQ( TestGameState::pauseCount, 8 );
	ASSERT_EQ( TestGameState::resumeCount, 8 );
}

TEST_F( GameStateManagerFixture, StateMultiTest )
{
	States.Push<TestGameState>();
	States.Push<TestGameState>();
	States.Push<TestGameState>();
	States.Pop();
	States.Pop();
	States.Push<TestGameState>();
	States.Push<TestGameState>();
	States.Add( "TestGameState", "TestPersistent" );
	States.Pop();
	States.Pop();
	States.Remove( "TestPersistent" );
	//! Test empty persistent state removal
	States.Remove( "TestPersistent" );
	States.Remove( "TestPersistent" );
	States.Pop();
	// Test empty popping
	States.Pop();
	States.Pop();
	States.Pop();
	States.Push<TestGameState>();
	States.Pop();

	States.Update();
	ASSERT_EQ( TestGameState::actCount, 7 );
	ASSERT_EQ( TestGameState::deactCount, 7 );
	ASSERT_EQ( TestGameState::pauseCount, 11 );
	ASSERT_EQ( TestGameState::resumeCount, 11 );
}
