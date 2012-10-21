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
 * @file ThreadData.h
 * @brief Thread data class.
 */

#ifndef __CBL_THREADDATA_H_
#define __CBL_THREADDATA_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Hash.h"
#include "cbl/Thread/Mutex.h"

// External Libraries //
#include <list>

namespace cbl
{
	//! Thread local data container.
	class CBL_API ThreadData
	{
	public:
		void Add( const cbl::Char * name, void * arg );
		void Remove( const cbl::Char * name );
		void * Find( const cbl::Char * name );
		void Clear( void );
		Uint32 Size( void ) const;
		
		template< typename T >
		T * Find( const cbl::Char * name );

	private:
		typedef std::map<cbl::HashValue, void *>	DataList;
		typedef std::pair< cbl::HashValue, void * >	DataListEntry;

	private:
		DataList			mDataList;
		CBL_MUTEX_DECLARE( mtxData );
	};

	template< typename T >
	T * ThreadData::Find( const cbl::Char * name )
	{
		return reinterpret_cast< T * >( Find( name ) );
	}
}

#endif // __CBL_THREADDATA_H_
