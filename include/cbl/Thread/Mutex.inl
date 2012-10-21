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
 * @file Mutex.inl
 * @brief Mutex inline methods.
 */

namespace cbl
{
	inline void Mutex::Lock( void )
	{
		Lock_Impl();
	}
	
	inline bool Mutex::TryLock( cbl::Uint32 milliseconds )
	{
		if( milliseconds > 0 )
			return TryLock_Impl( milliseconds );

		return TryLock_Impl();
	}
	
	inline void Mutex::Unlock( void )
	{
		Unlock_Impl();
	}

	inline Mutex::ScopedLock::ScopedLock( Mutex & mtx )
		: mMutex( mtx )
	{
		mMutex.Lock();
	}

	inline Mutex::ScopedLock::~ScopedLock()
	{
		mMutex.Unlock();
	}
}