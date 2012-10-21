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
 * @file Services.inl
 * @brief Services template definitions.
 */

#include "cbl/Reflection/Typing.h"

namespace cbl
{
	/***** Template definitions *****/
	template< typename SERVICE_TYPE >
	void Services::Add( SERVICE_TYPE* service )
	{
		CBL_ASSERT_TRUE( service );
		CBL_ASSERT( mServices.find( TypeCName<SERVICE_TYPE>() ) == mServices.end(), "Service type already exists." );

		mServices.insert( std::make_pair( TypeCName<SERVICE_TYPE>(), static_cast< void * >( service ) ) );
	}
	
	template< typename SERVICE_TYPE >
	void Services::Remove()
	{
		ServiceMap::iterator eraseIt = mServices.find( TypeCName<SERVICE_TYPE>() );
		CBL_ASSERT( eraseIt != mServices.end(), "Service type does not exist!" );
		mServices.erase( eraseIt );
	}

	template< typename SERVICE_TYPE >
	inline SERVICE_TYPE* Services::Get( void ) const
	{
		ServiceMap::const_iterator findIt = mServices.find( TypeCName<SERVICE_TYPE>() );
		return findIt != mServices.end() ? static_cast< SERVICE_TYPE * >( findIt->second ) : NULL;
	}
}
