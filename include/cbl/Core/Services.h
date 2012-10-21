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
 * @file Services.h
 * @brief Game services.
 */

#ifndef __CBL_SERVICES_H_
#define __CBL_SERVICES_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Singleton.h"
#include "cbl/Debug/Assert.h"

// External Libraries //
#include <unordered_map>

namespace cbl
{
	//! Services provide registration and retrieval of game services.
	//! They stored and accessible through a unique hashed string ID.
	//! 
	//! Usage:
	//! @code
	//! class TheService
	//! {
	//! public:
	//!     CBL_SERVICE_TYPE( TheService );  // Declare a service type for TheService.
	//! };
	//! 
	//! TheService		      object;
	//! 
	//! cbl::Services::Instance().Add< TheService >( &object ); // services.Add( &object ); works as well.
	//! TheService * getService = cbl::Services::Instance().Find< TheService >(); // Returns NULL if service is not found.
	//! cbl::Services::Instance().Remove< TheService >(); // Service is now removed.
	//! @endcode
	class CBL_API Services : 
		Noncopyable
	{
	/***** Types *****/
	public:
		typedef std::unordered_map<CName,void*>	ServiceMap;		//!< Service table type.

	/***** Public Methods *****/
	public:
		//! Add service to container.
		//! @see CBL_SERVICE_TYPE
		//! @param	type	Service class type.
		//! @param	service	Service to object add.
		template< typename SERVICE_TYPE >
		void Add( SERVICE_TYPE* service );
		//! Remove service from container.
		//! @param	type	Service class type.
		template< typename SERVICE_TYPE >
		void Remove( void );
		//! Get service from container.
		//! @tparam	T		Type to return.
		//! @param	type	Type to search for.
		//! @return			Pointer to object of type T or NULL if service doesn't exist.
		template< typename SERVICE_TYPE >
		SERVICE_TYPE* Get( void ) const;

	/***** Private Members *****/
	private:
		ServiceMap				mServices;	//!< List of services.
	};
}

#include "Services.inl"

#endif // __CBL_SERVICES_H_
