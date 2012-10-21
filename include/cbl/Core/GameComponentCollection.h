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

#ifndef __CBL_GAMECOMPONENTCOLLECTION_H_
#define __CBL_GAMECOMPONENTCOLLECTION_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Core/Event.h"

// External Dependencies //
#include <list>

namespace cbl
{
	namespace E
	{
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
		typedef Event< void( GameComponent * ) >			Component;		//!< Component changed event.
		typedef Event< void( DrawableGameComponent * ) >	DrawComponent;	//!< Drawable component changed event.
#else
		typedef Event0<void, GameComponent *>				Component;		//!< Component changed event.
		typedef Event0<void, DrawableGameComponent *>		DrawComponent;	//!< Drawable component changed event.
#endif
	}

	//! @brief GameComponent container which provides an interface to add and remove game components.
	//! See http://msdn.microsoft.com/en-us/library/microsoft.xna.framework.gamecomponentcollection.aspx
	//!
	//! GameComponent::OnComponentAdded and GameComponent::OnComponentRemoved are called respectively when
	//! a game component object is added to and removed from the container and the local GameComponentCollection.OnComponentAdded
	//! and GameComponentCollection.OnComponentRemoved events are raised.
	class CBL_API GameComponentCollection :
		Noncopyable
	{
	/***** Private Types *****/
	private:
		//! Game component sort predicate.
		struct GameComponentSort {
			bool operator () ( GameComponent* lhs, GameComponent* rhs ) {
				return lhs->UpdateOrder < rhs->UpdateOrder;
			}
		};
	/***** Types *****/
	public:
		typedef std::list< GameComponent * >					ComponentList;			//!< Component list type.
		typedef ComponentList::iterator							iterator;				//!< List iterator.
		typedef ComponentList::const_iterator					const_iterator;			//!< List const iterator.
		typedef ComponentList::reverse_iterator					reverse_iterator;		//!< List iterator.
		typedef ComponentList::const_reverse_iterator			const_reverse_iterator;	//!< List const iterator.

	/***** Events *****/
	public:
		E::Component			OnComponentAdded;	//!< Component added event.
		E::Component			OnComponentRemoved;	//!< Component removed event.
		E::DrawComponent		OnDrawableAdded;	//!< Component added event.
		E::DrawComponent		OnDrawableRemoved;	//!< Component added event.

	/***** Public Methods *****/
	public:
		//! Default constructor.
		GameComponentCollection();
		//! Destructor.
		~GameComponentCollection();
		//! @brief Add a component to the collection.
		//! Local OnComponentAdded event is raised.
		//! @param	component	Component to add.
		void Add( GameComponent * const component, bool init = false );
		//! @brief Add a drawable component tzo the collection.
		//! Local OnDrawableAdded event is raised.
		//! @param	component	Drawable component to add.
		void Add( DrawableGameComponent * const component, bool init = false );
		//! @brief Remove a component from the collection.
		//! Local OnComponentRemoved event is raised.
		//! @param	component	Component to remove.
		void Remove( GameComponent * const component, bool shutdown = false );
		//! @brief Remove a drawable component to the collection.
		//! Local OnDrawableRemoved event is raised.
		//! @param	component	Drawable component to remove.
		void Remove( DrawableGameComponent * const component, bool shutdown = false );
		//! @brief Clear the component collection of all components.
		void clear( void );
		//! Component list size.
		//! @return	Size of the component collection.
		const size_t size( void ) const;
		//! Reverse begin component collection iterator.
		//! @return	Component collection reverse begin iterator.
		reverse_iterator rbegin( void );
		//! Begin component collection iterator.
		//! @return	Component collection begin iterator.
		iterator begin( void );
		//! Reverse begin component collection constant iterator.
		//! @return	Component collection reverse begin const iterator.
		const_reverse_iterator rbegin( void ) const;
		//! Begin component collection constant iterator.
		//! @return	Component collection begin const iterator.
		const_iterator begin( void ) const;
		//! Reverse end component collection constant iterator.
		//! @return	Component collection reverse end iterator.
		reverse_iterator rend( void );
		//! End component collection constant iterator.
		//! @return	Component collection end iterator.
		iterator end( void );
		//! Reverse end component collection constant iterator.
		//! @return	Component collection reverse end const iterator.
		const_reverse_iterator rend( void ) const;
		//! End component collection constant iterator.
		//! @return	Component collection end const iterator.
		const_iterator end( void ) const;
		
	/***** Private Members *****/
	private:
		ComponentList		mComponentList;	//!< Internal component list.
	};
}

#include "GameComponentCollection.inl"

#endif // __CBL_GAMECOMPONENTLIST_H_
