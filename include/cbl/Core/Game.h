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
 * @file Game.h
 * @brief Game application class.
 */

#ifndef __CBL_GAME_H_
#define __CBL_GAME_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/TimeSpan.h"
#include "cbl/Util/Stopwatch.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/VectorSet.h"
#include "cbl/Core/GameComponentCollection.h"
#include "cbl/Core/Services.h"
#include "cbl/Core/GameTime.h"
#include "cbl/Core/ObjectManager.h"
#include "cbl/Core/GameStateManager.h"

namespace cbl
{
	//! @brief Provides basic game application class.
	class CBL_API Game :
		Noncopyable
	{
	/***** Properties *****/
	public:
		GETTER_AUTO_CREF( GameTime, GameTime );
		GETTER_AUTO_CREF( GameTime, DrawTime );
		GETTER_AUTO_CREF( cbl::String, Name );

	public:
		inline static Game& Instance() { return *sInstance; }

	/***** Public Members *****/
	public:
		bool						Active;					//!< Indicates whether the game is currently the active application.
		bool						IsFixedTimeStep;		//!< Is the game fixed time-step?
		bool						DropFrames;				//!< Drop frames if it is lagging behind badly.
		bool						LimitDrawRate;			//!< Limit the draw frame rate.
		Real						UpdateTimeScale;		//!< Update time scale.
		TimeSpan					TargetElapsedTime;		//!< The targetted time between frames. Defaults to 60FPS.
		TimeSpan					TargetElapsedDrawTime;	//!< The targetted time between draw frames. Defaults to 60FPS.
		TimeSpan					InactiveSleepTime;		//!< The time to sleep when the game is inactive.

		Services					Services;				//!< Game services
		GameComponentCollection		Components;				//!< The collection of GameComponents owned by the game.
		ObjectManager				Objects;				//!< Game objects.
		GameStateManager			States;					//!< Game states.

	/***** Public Static Members *****/
	public:
		static const Int64			sDropFrameLimit;		//!< Limit to drop frames.

	/***** Public Methods *****/
	public:
		//! Constructor.
		//! @param	name	Game name.
		explicit Game( const Char* name );
		//!  Destructor.
		virtual ~Game();
		//!  Start the game application.
		void Run( void );
		//!  End the game application.
		void Exit( void );
		//! Add an IUpdatable object to the game.
		void AddUpdatable( IUpdatable * updatable );
		//! Remove an IUpdatable object from the game.
		void RemoveUpdatable( IUpdatable * updatable );
		//! Add an IDrawable object to the game.
		void AddDrawable( IDrawable * drawable );
		//! Remove an IDrawable object from the game.
		void RemoveDrawable( IDrawable * drawable );

	/***** Protected Methods *****/
	protected:
		//! Initialise game and all attached game components.
		//! Called before starting game loop.
		virtual void Initialise( void );
		//! Update the game.
		//! @param	time	Elapsed time.
		virtual void Update( const GameTime & time );
		//! Shut down the game application.
		//! Called after stopping game loop.
		//! Shuts down all components in the component collection.
		virtual void Shutdown( void );
		//! Called after all components are initialized but before the first update in the game loop.
		virtual void BeginRun( void );
		//! Called after the game loop has stopped running before exiting.
		virtual void EndRun( void );
		//! Starts the drawing of a frame. This method is followed by calls to Draw and EndDraw.
		virtual bool BeginDraw( void );
		//! Called when the game determines it is time to draw a frame.
		//! @param	time	Elapsed time.
		virtual void Draw( const GameTime & time );
		//! Ends the drawing of a frame. This method is preceeded by calls to Draw and BeginDraw.
		virtual void EndDraw( void );

	/***** Events *****/
	public:
		//! OnComponentAdded event handler.
		void OnComponentAdded( GameComponent * updatable );
		//! OnComponentRemoved event handler.
		void OnComponentRemoved( GameComponent * updatable );
		//! OnDrawableAdded event handler.
		void OnDrawableAdded( DrawableGameComponent * drawable );
		//! OnDrawableRemoved event handler.
		void OnDrawableRemoved( DrawableGameComponent * drawable );

	/***** Private Methods *****/
	private:
		//!  Updates the game's clock and calls Update and Draw.
		void Tick( void );

	/***** Internal Types *****/
	private:
		//! Game component sort predicate.
		struct ListSort {
			bool operator () ( IUpdatable* lhs, IUpdatable* rhs ) {
				return lhs->UpdateOrder < rhs->UpdateOrder;
			}
			bool operator () ( IDrawable* lhs, IDrawable* rhs ) {
				return lhs->DrawOrder < rhs->DrawOrder;
			}
		};

		typedef VectorSet<IUpdatable*>		UpdatableList;
		typedef VectorSet<IDrawable*>		DrawableList;
		typedef std::vector<IUpdatable*>	UpdatableRunList;
		typedef std::vector<IDrawable*>		DrawableRunList;

	/***** Private Static Members *****/
	private:
		static Game* sInstance;

	/***** Private Members *****/
	private:
		UpdatableList		mUpdatables;			//!< Update list.
		DrawableList		mDrawables;				//!< Drawable list.
		UpdatableRunList	mUpdatableRuns;			//!< Update run list.
		DrawableRunList		mDrawableRuns;			//!< Draw run list.
		String				mName;					//!< Game name.
		GameTime			mGameTime;				//!< Current application time.
		GameTime			mDrawTime;				//!< Current draw time.
		TimeSpan			mAccumTime;				//!< Accumulative frame time.
		TimeSpan			mDrawAccumTime;			//!< Accumulative frame time.
		Stopwatch			mStopwatch;				//!< Game stopwatch to measure time between frames.
		bool				mShutdown;				//!< Shut down flag.
	};
}

#include "cbl/Reflection/Typing.h"
CBL_TYPE( cbl::Game, Game );

#define CBL_GAME\
	::cbl::Game::Instance()

#endif // __CBL_GAME_H_
