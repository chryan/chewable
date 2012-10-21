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
 * @file ObjectPartTable.inl
 * @brief Object component table template methods.
 */

#include "cbl/Util/FileSystem.h"
#include "cbl/Reflection/Typing.h"

namespace cbl
{
	template< typename PART_TYPE >
	inline PART_TYPE* ObjectPartTable::Add( bool init )
	{
		// Force a compile-time type test.
		static_cast< ObjectPart* >( static_cast< PART_TYPE* >( NULL ) );
		return static_cast<PART_TYPE*>( Add( TypeCName<PART_TYPE>(), init ) );
	}

	template< typename PART_TYPE >
	inline PART_TYPE* ObjectPartTable::Get( void ) const
	{
		// Force a compile-time type test.
		static_cast< ObjectPart* >( static_cast< PART_TYPE* >( NULL ) );
		return static_cast<PART_TYPE*>( Get( TypeCName<PART_TYPE>() ) );
	}

	template< typename PART_TYPE >
	inline void ObjectPartTable::Remove( void ) {
		Remove( TypeCName<PART_TYPE>() );
	}
}
