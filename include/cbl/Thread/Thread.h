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
 * @file Thread.h
 * @brief Threading utility class.
 */

#ifndef __CBL_THREAD_H_
#define __CBL_THREAD_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Thread/ThreadData.h"

#if CBL_PLATFORM == CBL_PLATFORM_WIN32
#include "Win32/ThreadImpl.h"
#undef Yield
#else
#pragma error Unsupported platform.
#endif

namespace cbl
{
	//! Threading class. Implementation is encapsulated within the privately inherited ThreadImpl class.
	//! The default function callback function signature is void (*func)( void *).
	//! Note: This class was referenced from the Poco library (http://pocoproject.org/).
	class CBL_API Thread :
		Noncopyable,
		private ThreadImpl
	{
	/***** Public Members  *****/
	public:
		ThreadData						Data;

	/***** Types *****/
	public:
		typedef ThreadImpl::Callable	Callable;	//!< Callable type.
		typedef ThreadImpl::ThreadID	ThreadID;	//!< Thread ID type.
		typedef ThreadImpl::Entry		Entry;		//!< Entry point function type.

	/***** Static Methods *****/
	public:
		//! Thread sleep.
		//! @param	seconds			Time to sleep thread (in seconds).
		static void Sleep( cbl::Real seconds );
		//! Thread sleep.
		//! @param	milliseconds	Time to sleep thread (in milliseconds).
		static void Sleep( cbl::Uint32 milliseconds );
		//! Yield the CPU to other threads.
		static void Yield( void );
		//! Returns the thread object for the current active thread.
		//! 0 is returned if this is called from the main thread.
		//! @return					Pointer to thread object.
		static Thread * GetCurrent();
		//! Returns the current active thread's ID.
		//! @return					Current thread ID.
		static ThreadID GetCurrentID( void );

	/***** Properties *****/
	public:
		//! Get the thread object's ID.
		ThreadID GetID( void ) const;
		//! Check if thread is still running.
		bool IsRunning( void ) const;

	/***** Public Methods *****/
	public:
		//! Constructor.
		Thread();
		//! Destructor.
		~Thread();
		//! Run a thread with the supplied Runnable object.
		//! @param	target		Object entry point for thread.
		void Start( Runnable & target );
		//! Run a thread with the supplied arguments.
		//! @param	target		Function pointer to use to spawn a thread.
		//! @param	data		Pointer to thread argument data.
		void Start( Callable target, void * data = 0 );
		//! Waits for a thread to complete infinitely.
		void Join();
		//! Waits for at most the given interval for the thread
		//! to complete. Returns true if thread completes.
		//! @param	ms			Timeout length in milliseconds.
		//! @return				True if thread has completed.
		bool TryJoin( cbl::Uint32 milliseconds );
	};
}

#include "Thread.inl"

#endif // __CBL_THREAD_H_
