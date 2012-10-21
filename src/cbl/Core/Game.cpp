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
 * @file Game.cpp
 * @brief Game application class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Core/Game.h"
#include "cbl/Core/GameComponent.h"
#include "cbl/Core/DrawableGameComponent.h"
#include "cbl/Core/IDrawable.h"
#include "cbl/Core/IUpdatable.h"
#include "cbl/Core/GameStateManager.h"
#include "cbl/Debug/Logging.h"
#include "cbl/Debug/FileLogger.h"
#include "cbl/Debug/Profiling.h"
#include "cbl/Thread/Thread.h"

// Using 'this' is fine because the object factory only needs it to store the reference.
#pragma warning( disable : 4355 )

using namespace cbl;

const Int64	Game::sDropFrameLimit	= 10;
Game*		Game::sInstance			= NULL;

Game::Game( const Char * name )
: Active( true )
, IsFixedTimeStep( true )
, DropFrames( true )
, LimitDrawRate( true )
, UpdateTimeScale( 1.0f )
, TargetElapsedTime( TimeSpan::TicksPerSecond/60 )
, TargetElapsedDrawTime( TimeSpan::TicksPerSecond/60 )
, InactiveSleepTime( 20 )
, mName( name )
, mShutdown( false )
{
	// Ensure only 1 instance of game.
	CBL_ASSERT_FALSE( sInstance );

	sInstance = this;
#if CBL_FILE_LOGGER_ENABLED == CBL_ENABLED
	LOG_ADDLOGGER( "Default", 
		new FileLogger( ( mName + "_Log.log" ).c_str(), mName.c_str() ) );
#endif
	LOG( "Creating game." );

	Components.OnComponentAdded		+= E::Component::Method<Game, &Game::OnComponentAdded>(this);
	Components.OnDrawableAdded		+= E::DrawComponent::Method<Game, &Game::OnDrawableAdded>(this);
	Components.OnComponentRemoved	+= E::Component::Method<Game, &Game::OnComponentRemoved>(this);
	Components.OnDrawableRemoved	+= E::DrawComponent::Method<Game, &Game::OnDrawableRemoved>(this);
}

//!  Destructor.
Game::~Game()
{
	// Ensure only 1 instance of game.
	CBL_ASSERT_TRUE( sInstance == this );
	sInstance = NULL;
	
	Components.OnDrawableRemoved	-= E::DrawComponent::Method<Game, &Game::OnDrawableRemoved>(this);
	Components.OnComponentRemoved	-= E::Component::Method<Game, &Game::OnComponentRemoved>(this);
	Components.OnDrawableAdded		-= E::DrawComponent::Method<Game, &Game::OnDrawableAdded>(this);
	Components.OnComponentAdded		-= E::Component::Method<Game, &Game::OnComponentAdded>(this);

	LOG( "Destroying game." );
	
#if CBL_FILE_LOGGER_ENABLED == CBL_ENABLED
	LOG_REMOVELOGGER( "Default" );
#endif
}

void Game::Run( void )
{
	Initialise();
	BeginRun();

	mStopwatch.Reset();
	mStopwatch.Start();
	while( !mShutdown )
	{
		Tick();
	}
	mStopwatch.Stop();

	EndRun();
	Shutdown();
}

void Game::Exit( void )
{
	LOG( "Exit called." );
	mShutdown = true;
}

void Game::AddUpdatable( IUpdatable * updatable )
{
	mUpdatables.insert( updatable );
}

void Game::RemoveUpdatable( IUpdatable * updatable )
{
	mUpdatables.erase( updatable );
}

void Game::AddDrawable( IDrawable * drawable )
{
	mDrawables.insert( drawable );
}

void Game::RemoveDrawable( IDrawable * drawable )
{
	mDrawables.erase( drawable );
}

void Game::Initialise( void )
{
	LOG( LogLevel::Info << "Initialising game." );

	CBL_FOREACH_CONST( GameComponentCollection, it, Components ) {
		( *it )->Initialise();
	}

	LOG( LogLevel::Info << "Components initialised." );
}

bool SortUpdates( IUpdatable * lhs, IUpdatable * rhs ) {
	return lhs->UpdateOrder < rhs->UpdateOrder;
}

void Game::Update( const GameTime & time )
{
	CBL_PROFILE_FUNCTION;
	mUpdatableRuns.clear();

	size_t size = mUpdatables.size();
	for( cbl::Uint32 i = 0; i < size; ++i ) {
		if( mUpdatables[i]->Enabled )
			mUpdatableRuns.push_back( mUpdatables[i] );
	}

	size = mUpdatableRuns.size();
	std::sort( mUpdatableRuns.begin(), mUpdatableRuns.end(), SortUpdates );
	for( cbl::Uint32 i = 0; i < size; ++i ) {
		mUpdatableRuns[i]->Update( time );
	}
}

void Game::Shutdown( void )
{
	States.Clear();
	States.Update();

	Objects.ForceFullPurge(); // Destroy all the objects before we de-init system components.

	LOG( "Shutting down game." );

	CBL_FOREACH_REV_CONST( GameComponentCollection, it, Components ) {
		( *it )->Shutdown();
	}

	LOG( "Components shut down." );
}

void Game::BeginRun( void )
{
}

void Game::EndRun( void )
{
}

bool Game::BeginDraw( void )
{
	return true;
}

bool SortDraws( IDrawable * lhs, IDrawable * rhs ) {
	return lhs->DrawOrder < rhs->DrawOrder;
}

void Game::Draw( const GameTime & time )
{
	CBL_PROFILE_FUNCTION;
	mDrawableRuns.clear();

	size_t size = mDrawables.size();
	for( cbl::Uint32 i = 0; i < size; ++i ) {
		if( mDrawables[i]->Visible )
			mDrawableRuns.push_back( mDrawables[i] );
	}

	size = mDrawableRuns.size();
	std::sort( mDrawableRuns.begin(), mDrawableRuns.end(), SortDraws );
	for( cbl::Uint32 i = 0; i < size; ++i ) {
		mDrawableRuns[i]->Draw( time );
	}
}

void Game::EndDraw( void )
{
}

void Game::OnComponentAdded( GameComponent * updatable )
{
	CBL_ASSERT_TRUE( updatable );
	mUpdatables.insert( updatable );
}

void Game::OnComponentRemoved( GameComponent * updatable )
{
	mUpdatables.erase( updatable );
}

void Game::OnDrawableAdded( DrawableGameComponent * drawable )
{
	CBL_ASSERT_TRUE( drawable );
	mDrawables.insert( drawable );
}

void Game::OnDrawableRemoved( DrawableGameComponent * drawable )
{
	mDrawables.erase( drawable );
}

void Game::Tick( void )
{
	TimeSpan elapsed 	= mStopwatch.GetLapTime();
	// Game is updating too fast. Wait 1 millisecond.
	if( elapsed.Ticks() <= 0 )
		return;
	
	mAccumTime += elapsed;
	mDrawAccumTime += elapsed;

	mGameTime.ElapsedReal += elapsed;
	mGameTime.TotalReal += elapsed;
	mDrawTime.ElapsedReal += elapsed;
	mDrawTime.TotalReal += elapsed;

	if( mAccumTime >= TargetElapsedTime )
	{
		if( IsFixedTimeStep )
		{
			cbl::Int64 noOfUpdates = mAccumTime.Ticks() / TargetElapsedTime.Ticks();
			if( noOfUpdates > sDropFrameLimit && DropFrames ) {
				mAccumTime = TargetElapsedTime;
			}

			while( mAccumTime >= TargetElapsedTime )
			{
				mAccumTime -= TargetElapsedTime;
				mGameTime.IsRunningSlowly = ( mAccumTime >= TargetElapsedTime );

				TimeSpan scaled = TargetElapsedTime * UpdateTimeScale;
				mGameTime.Total += scaled;
				mGameTime.Elapsed = scaled;

				States.Update();
				Update( mGameTime );
				Objects.Purge();
			}
			mGameTime.ElapsedReal = mAccumTime;
		}
		else
		{
			mGameTime.Elapsed	= mAccumTime;
			mGameTime.Total		+= mAccumTime;

			States.Update();
			Update( mGameTime );
			Objects.Purge();

			mGameTime.Elapsed = 0;
			mGameTime.ElapsedReal = 0;
			mAccumTime = 0;
		}
	}
	
	if( !LimitDrawRate || mDrawAccumTime >= TargetElapsedDrawTime )
	{
		if( BeginDraw() )
		{
			mDrawTime.Elapsed = mDrawAccumTime;
			mDrawTime.ElapsedReal = mDrawAccumTime;
			Draw( mGameTime );
			EndDraw();
			mDrawTime.Elapsed = 0;
			mDrawTime.ElapsedReal = 0;
			mDrawAccumTime = 0;
		}
	}

	//Thread::Sleep( Active ? Uint32(1) : cbl::Uint32( InactiveSleepTime.Milliseconds() ) );
}
