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
 * @file ThreadImpl.h
 * @brief Windows 32bit threading implementation class.
 */

#ifndef __CBL_WIN32THREADIMPL_H_
#define __CBL_WIN32THREADIMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Thread/Runnable.h"

// External Libraries //
#include <windows.h>

namespace cbl
{
	//! Win32 Threading implementation class.
	//! TODO: Implement exception throwing when it's supported by the framework.
	//! Note: This class was referenced from the Poco library (http://pocoproject.org/).
	class CBL_API ThreadImpl
	{
	/***** Types *****/
	public:
		typedef void (*Callable)(void*);
		typedef DWORD ThreadID;
		typedef DWORD (WINAPI *Entry)(LPVOID);
		
		struct CallableData
		{
			CallableData(): Callback(0), Data(0) {}
			Callable	Callback;
			void		* Data; 
		};

	/***** Properties *****/
	public:
		ThreadID GetID_Impl( void ) const;

	/***** Public Methods *****/
	public:
		ThreadImpl();
		~ThreadImpl();
		void Start_Impl( Runnable & target );
		void Start_Impl( Callable target, void * data );
		void Join_Impl( void );
		bool TryJoin_Impl( cbl::Uint32 milliseconds );
		bool IsRunning_Impl( void ) const;
		
	/***** Static Methods *****/
	public:
		static void Sleep_Impl( cbl::Uint32 ms );
		static void Yield_Impl( void );
		static ThreadImpl * GetCurrent_Impl();
		static ThreadID GetCurrentID_Impl( void );

	/***** Proctected Methods *****/
	protected:
		void Create( Entry ent, void * data );
		void Cleanup( void );

		static DWORD WINAPI RunnableEntry( LPVOID lpParam );
		static DWORD WINAPI CallableEntry( LPVOID lpParam );

	/***** Private Members *****/
	private:
		class CurrentThreadHolder
		{
		public:
			CurrentThreadHolder() : mSlot( TlsAlloc() )
			{
				CBL_ASSERT( mSlot != TLS_OUT_OF_INDEXES, "Cannot allocate thread context key." );
			}
			~CurrentThreadHolder()
			{
				TlsFree( mSlot );
			}
			ThreadImpl * Get() const
			{
				return reinterpret_cast<ThreadImpl*>( TlsGetValue( mSlot ) );
			}
			void Set( ThreadImpl* thread )
			{
				TlsSetValue( mSlot, thread );
			}
		private:
			DWORD mSlot;
		};
		Runnable			* mRunTarget;
		CallableData		mCallbackTarget;
		HANDLE				mThread;	//!< Win32 thread handle.
		ThreadID			mThreadID;	//!< This thread's ID.

		static CurrentThreadHolder sCurrentThreadHolder;
	};

	/***** Inline Methods *****/
	inline void ThreadImpl::Sleep_Impl( cbl::Uint32 ms )
	{
		::Sleep( DWORD(ms + 1) );
	}

	inline void ThreadImpl::Yield_Impl( void )
	{
		::Sleep( 0 );
	}

	inline ThreadImpl::ThreadID ThreadImpl::GetID_Impl( void ) const
	{
		return mThreadID;
	}
}

#endif // __CBL_WIN32THREADIMPL_H_
