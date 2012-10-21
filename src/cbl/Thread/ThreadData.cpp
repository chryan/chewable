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
 * @file ThreadData.cpp
 * @brief Thread data class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Thread/ThreadData.h"
#include "cbl/Debug/Assert.h"

using namespace cbl;

void ThreadData::Add( const char * name, void * arg )
{
	CBL_ASSERT_TRUE( name );
	CBL_MUTEX_SCOPEDLOCK( mtxData );

	cbl::HashValue hash = cbl::Hash::Generate( name );
	CBL_ASSERT( mDataList.find( hash ) == mDataList.end(), "Data name already exists!" );

	mDataList.insert( DataListEntry( hash, arg ) );
}

void ThreadData::Remove( const char * name )
{
	CBL_ASSERT_TRUE( name );
	CBL_MUTEX_SCOPEDLOCK( mtxData );

	cbl::HashValue hash = cbl::Hash::Generate( name );
	DataList::iterator findIt = mDataList.find( hash );

	if( findIt != mDataList.end() )
		mDataList.erase( findIt );
}

void * ThreadData::Find( const cbl::Char * name )
{
	CBL_MUTEX_SCOPEDLOCK( mtxData );

	DataList::iterator find = mDataList.find( cbl::Hash::Generate( name ) );
	if( find != mDataList.end() )
		return find->second;

	return NULL;
}

void ThreadData::Clear( void )
{
	CBL_MUTEX_SCOPEDLOCK( mtxData );

	mDataList.clear();
}

Uint32 ThreadData::Size( void ) const
{
	CBL_MUTEX_SCOPEDLOCK( mtxData );

	return mDataList.size();
}
