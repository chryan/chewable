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
 * @file VectorSet.h
 * @brief Fast set class.
 */

#ifndef __CBL_VECTORSET_H_
#define __CBL_VECTORSET_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! Drop-in replacement for std::set.
	//! Uses a sorted vector to improve seek/iteration performance.
	template<typename Key, typename Compare = std::less<Key> >
	class VectorSet
	{
	/***** Public Types *****/
	public:
		typedef typename std::vector<Key>::iterator					iterator;				//!< Forward iterator.
		typedef typename std::vector<Key>::const_iterator			const_iterator;			//!< Const forward iterator.
		typedef typename std::vector<Key>::reverse_iterator			reverse_iterator;		//!< Reverse iterator
		typedef typename std::vector<Key>::const_reverse_iterator	const_reverse_iterator;	//!< Const reverse iterator.

	/***** Public Members *****/
	public:
		bool auto_sort;

	/***** Public Methods *****/
	public:
		//! Constructor.
		//! @param	size	Initial allocation size.
		VectorSet(cbl::Uint32 size=32, bool auto_sort=true);
		//! Destructor.
		~VectorSet();
		//! Resort the set.
		void resort( void );
		//! Insert a pair into the set.
		//! @param	_key	Key to insert.
		//! @return			Flag indicating if operation was successful.
		bool insert( const Key& _key);
		//! Erase a value from the set.
		//! @param	_key	Key to remove.
		//! @return			Flag indicating if operation was successful.
		bool erase( const Key& _key );
		//! Erase a value from the set using an iterator.
		//! @param	_key	Iterator.
		void erase( const iterator& del );
		//! Get current container size.
		//! @return			Size of container.
		const size_t size( void ) const;
		//! Forward iterator.
		typename iterator begin( void );
		//! Const forward iterator.
		typename const_iterator begin( void ) const;
		//! End foward iterator.
		typename iterator end( void );
		//! Const end forward iterator.
		typename const_iterator end( void ) const;
		//! Reverse iterator.
		typename reverse_iterator rbegin( void );
		//! Const reverse iterator.
		typename const_reverse_iterator rbegin( void ) const;
		//! Reverse end iterator.
		typename reverse_iterator rend( void );
		//! Const reverse end iterator.
		typename const_reverse_iterator rend( void ) const;
		//! Search for an element in the set.
		//! @param	_key	Key to search for.
		//! @return			Returns a valid iterator if key was found. Otherwise, return points to end().
		typename iterator find( const Key& _key );
		//! Search for an element in the set.
		//! @param	_key	Key to search for.
		//! @return			Returns a valid iterator if key was found. Otherwise, return points to end().
		typename const_iterator find( const Key& _key ) const;
		//! Random-access to iterate through set.
		//! @param	index	Set index.
		//! @return			Returns the value of the key. Will crash if out of bounds.
		Key& operator[] (size_t index);
		//! Random-access to iterate through set.
		//! @param	index	Set index.
		//! @return			Returns the value of the key. Will crash if out of bounds.
		const Key& operator[] (size_t index) const;
		//! Clear set.
		void clear( void );

	/***** Private Members *****/
	private:
		std::vector<Key>	mSet;	//!< The vector set.
		bool				mSorted;
	};
}

#include "VectorSet.inl"

#endif // __CBL_FASTSET_H_
