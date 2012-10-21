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
 * @file ObjectPartTable.h
 * @brief Object component table.
 */

#ifndef __CBL_OBJECTPARTTABLE_H_
#define __CBL_OBJECTPARTTABLE_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Debug/Logging.h"

// External Libraries //
#include <vector>

namespace cbl
{
	//! @brief Object component table.
	//! See ObjectManager for usage example.
	class CBL_API ObjectPartTable :
		Noncopyable
	{
	/***** Private Types *****/
	private:
		typedef std::vector< ObjectPart* >		Parts;

	/***** Types *****/
	public:
		typedef Parts::iterator					iterator;				//!< Table iterator.
		typedef Parts::const_iterator			const_iterator;			//!< Table const iterator.
		typedef Parts::reverse_iterator			reverse_iterator;		//!< Table reverse iterator.
		typedef Parts::const_reverse_iterator	const_reverse_iterator;	//!< Table reverse const iterator.

	/***** Public Methods *****/
	public:
		//! Constructor.
		ObjectPartTable( Parts& parts );
		//! Destructor.
		~ObjectPartTable();
		//! Add a new part type to the table.
		//! @tparam	PART_TYPE	Part type.
		//! @param	init		Initialise part.
		//! @return				Pointer to new component.
		template< typename PART_TYPE >
		PART_TYPE* Add( bool init = true );
		//! Add a new part type to the table.
		//! @param	type		Part type.
		//! @param	init		Initialise part.
		//! @return				Pointer to new component. NULL if unable to add component.
		ObjectPart* Add( const CName& type, bool init = true );
		//! Get an existing part from the table.
		//! @tparam	PART_TYPE	Part type.
		//! @return				Pointer to object part. NULL if not found.
		template< typename PART_TYPE >
		PART_TYPE* Get( void ) const;
		//! Get an existing part from the table.
		//! @param	type		Part type.
		//! @return				Pointer to object component. NULL if not found.
		ObjectPart* Get( const CName& type ) const;
		//! Removes an existing part from the table.
		//! Logs an error if type doesn't exist in the table.
		//! @tparam	PART_TYPE	Part type.
		template< typename PART_TYPE >
		void Remove( void );
		//! Removes an existing part from the table.
		//! Logs an error if type doesn't exist in the table.
		//! @param	type		Part type.
		void Remove( const CName& type );
		//! Initialises all components. Does nothing for components that are already initialised.
		void Initialise( void );

		//! Part table size.
		//! @return				Number of parts.
		inline const size_t size( void ) const { return mParts.size(); }
		//! Table reverse begin iterator.
		inline reverse_iterator rbegin( void ) { return mParts.rbegin(); }
		//! Table begin iterator.
		inline iterator begin( void ) { return mParts.begin(); }
		//! Table reverse begin const iterator.
		inline const_reverse_iterator rbegin( void ) const { return mParts.rbegin(); }
		//! Table begin const iterator.
		inline const_iterator begin( void ) const { return mParts.begin(); }
		//! Table reverse end iterator.
		inline reverse_iterator rend( void ) { return mParts.rend(); }
		//! Table end iterator.
		inline iterator end( void ) { return mParts.end(); }
		//! Table reverse end const iterator.
		inline const_reverse_iterator rend( void ) const { return mParts.rend(); }
		//! Table end const iterator.
		inline const_iterator end( void ) const { return mParts.end(); }
		//! Clear all object components.
		void clear( void );

	/***** Static Public Methods *****/
	public:
		//! Initialise an object component. Does nothing if already initialised.
		static void InitPart( ObjectPart* part );

	/***** Private Methods *****/
	private:
		//! Add an externally constructed object to the object table.
		bool Add( ObjectPart* objPart );

	/***** Private Members *****/
	private:
		Parts&			mParts;			//!< Parts.
		Object*			mParent;		//!< Holding parent object.
		friend class	Object;			//!< Befriend Object.
		friend class	ObjectPart;		//!< Befriend ObjectPart.
	};
}

#include "ObjectPartTable.inl"

CBL_TYPE( cbl::ObjectPartTable, ObjectPartTable );

#endif // __CBL_OBJECTPARTTABLE_H_
