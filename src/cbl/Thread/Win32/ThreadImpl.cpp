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
 * @file ThreadImpl.cpp
 * @brief Windows 32bit threading implementation class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Thread/Win32/ThreadImpl.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

using namespace cbl;

ThreadImpl::CurrentThreadHolder ThreadImpl::sCurrentThreadHolder;

ThreadImpl::ThreadImpl()
: mRunTarget( NULL )
, mThread( NULL )
, mThreadID( 0 )
{
}

ThreadImpl::~ThreadImpl()
{
	if( mThread ) ::CloseHandle( mThread );
}

void ThreadImpl::Start_Impl( Runnable & target )
{
	if( IsRunning_Impl() )
	{
		LOG_ERROR( "Thread already running." );
		return;
	}

	mRunTarget = &target;
	Create( RunnableEntry, this );
}

void ThreadImpl::Start_Impl( Callable target, void * data = 0 )
{
	if( IsRunning_Impl() )
	{
		LOG_ERROR( "Thread already running." );
		return;
	}

	mCallbackTarget.Callback	= target;
	mCallbackTarget.Data		= data;
	Create( CallableEntry, this );
}

void ThreadImpl::Join_Impl( void )
{
	if( !mThread ) return;

	switch( WaitForSingleObject( mThread, INFINITE ) )
	{
	case WAIT_OBJECT_0:
		Cleanup();
		return;
	default:
		LOG_ERROR( "Cannot join thread." );
		break;
	}
}

bool ThreadImpl::TryJoin_Impl( cbl::Uint32 milliseconds )
{
	if( !mThread ) return true;

	switch( WaitForSingleObject( mThread, DWORD( milliseconds + 1 ) ) )
	{
	case WAIT_TIMEOUT:
		LOG( LogLevel::Warning << "Thread did not complete in specified time." );
		return false;
	case WAIT_OBJECT_0:
		Cleanup();
		return true;
	}

	LOG_ERROR( "Cannot join thread." );
	return false;
}

bool ThreadImpl::IsRunning_Impl( void ) const
{
	if( mThread )
	{
		DWORD exitCode = 0;
		return ::GetExitCodeThread( mThread, &exitCode ) && ( exitCode == STILL_ACTIVE );
	}
	return false;
}

void ThreadImpl::Create( Entry ent, void * data )
{
	mThread = ::CreateThread(NULL, 0, ent, data, 0, &mThreadID );

	CBL_ASSERT_TRUE( mThread );
}

void ThreadImpl::Cleanup( void )
{
	if( !mThread )
		return;
	if( ::CloseHandle( mThread ) )
		mThread = NULL;
}

ThreadImpl * ThreadImpl::GetCurrent_Impl()
{
	return sCurrentThreadHolder.Get();
}

ThreadImpl::ThreadID ThreadImpl::GetCurrentID_Impl( void )
{
	return ::GetCurrentThreadId();
}

DWORD WINAPI ThreadImpl::RunnableEntry( LPVOID lpParam )
{
	sCurrentThreadHolder.Set(reinterpret_cast<ThreadImpl*>(lpParam));

	ThreadImpl * pthread = reinterpret_cast<ThreadImpl*>(lpParam);
	CBL_ASSERT_TRUE( pthread );
	pthread->mRunTarget->Run();

	return 0;
}

DWORD WINAPI ThreadImpl::CallableEntry( LPVOID lpParam )
{
	sCurrentThreadHolder.Set(reinterpret_cast<ThreadImpl*>(lpParam));

	ThreadImpl * pthread = reinterpret_cast<ThreadImpl*>(lpParam);
	CBL_ASSERT_TRUE( pthread );
	pthread->mCallbackTarget.Callback( pthread->mCallbackTarget.Data );

	return 0;
}