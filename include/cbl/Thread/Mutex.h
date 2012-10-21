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
 * @file Mutex.h
 * @brief Mutex utility class.
 */

#ifndef __CBL_MUTEX_H_
#define __CBL_MUTEX_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Noncopyable.h"

#if CBL_PLATFORM == CBL_PLATFORM_WIN32
#include "Win32/MutexImpl.h"
#else
#pragma error Unsupported platform.
#endif

namespace cbl
{
	class CBL_API Mutex :
		Noncopyable,
		private MutexImpl
	{
	public:
		Mutex();
		~Mutex();

		void Lock( void );
		bool TryLock( cbl::Uint32 milliseconds = 0 );
		void Unlock( void );

	public:
		class ScopedLock :
			Noncopyable 
		{
		public:
			ScopedLock( Mutex & mtx );
			~ScopedLock();
		private:
			Mutex & mMutex;
		};
	};
}

#if CBL_THREAD_SAFE == CBL_ENABLED
	#define CBL_MUTEX_DECLARE( name )		mutable cbl::Mutex name
	#define CBL_MUTEX_LOCK( name )			name.Lock()
	#define CBL_MUTEX_TRYLOCK( name )		name.TryLock()
	#define CBL_MUTEX_UNLOCK( name )		name.Unlock()
	#define CBL_MUTEX_SCOPEDLOCK( name )	cbl::Mutex::ScopedLock CBL_ScopedLock( name )
#else
	#define CBL_MUTEX_DECLARE( name )
	#define CBL_MUTEX_LOCK( name )
	#define CBL_MUTEX_TRYLOCK( name )
	#define CBL_MUTEX_UNLOCK( name )
	#define CBL_MUTEX_SCOPEDLOCK( name )
#endif

#include "Mutex.inl"

#endif // __CBL_MUTEX_H_
