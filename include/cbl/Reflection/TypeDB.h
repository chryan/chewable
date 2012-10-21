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
 * @file TypeDB.h
 * @brief Type information database.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_TYPEDB_H_
#define __CBL_TYPEDB_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/Type.h"
#include "cbl/Util/CName.h"
#include "cbl/Util/Noncopyable.h"

// External Libraries //
#include <unordered_map>

namespace cbl
{
	/***** Forward Declarations *****/
	class Type;

	//! Type database.
	class CBL_API TypeDB :
		Noncopyable
	{
	/***** Types *****/
	public:
		//! Entity construction function signature.
		template< typename TYPE >
		static void ConstructEntity( void* ent );
		//! Entity destruction function signature.
		template< typename TYPE >
		static void DestructEntity( void* ent );
		
	/***** Public Methods *****/
	public:
		//! Constructor.
		TypeDB();
		//! Destructor.
		~TypeDB();
		//! Create new type (returns existing type if already exists).
		//! @return				Reference to type info structure.
		template< typename TYPE >
		Type& Create( void );
		//! Gets an existing type.
		//! @tparam	TYPE		Type.
		//! @return				Pointer to type info structure.
		template< typename TYPE >
		const Type* Get( void ) const;
		//! Gets an existing type.
		//! @param	name		Type name.
		//! @return				Pointer to type info structure.
		const Type* Get(const CName& name ) const;
		
	/***** Private Methods *****/
	private:
		//! Create type implementation.
		//! @tparam	Type		Type.
		//! @return				Pointer to type info structure.
		template< typename TYPE >
		Type* CreateImpl( void );

	/***** Private Types *****/
	private:
		typedef std::unordered_map<CName, Type*>	TypeMap;			//!< Type map.

	/***** Private Members *****/
	private:
		TypeMap			mTypes;				//!< Type map.
	};
}

#include "TypeDB.inl"

#endif // __CBL_TYPEDB_H_