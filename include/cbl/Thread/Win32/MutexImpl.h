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
 * @file MutexImpl.h
 * @brief Windows 32bit mutex implementation class.
 */

#ifndef __CBL_WIN32MUTEXIMPL_H_
#define __CBL_WIN32MUTEXIMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"

// External Libraries //
#include <windows.h>

namespace cbl
{
	class CBL_API MutexImpl
	{
	/***** Protected Methods *****/
	protected:
		MutexImpl();
		~MutexImpl();
		void Lock_Impl();
		bool TryLock_Impl();
		bool TryLock_Impl( cbl::Uint32 milliseconds );
		void Unlock_Impl();
		
	/***** Private Members *****/
	private:
		CRITICAL_SECTION	mCS;
	};

	/***** Inline Methods *****/
	inline void MutexImpl::Lock_Impl()
	{
		EnterCriticalSection( &mCS );
	}

	inline bool MutexImpl::TryLock_Impl()
	{
		return TryEnterCriticalSection( &mCS ) != 0;
	}

	inline void MutexImpl::Unlock_Impl()
	{
		LeaveCriticalSection( &mCS );
	}
}

#endif // __CBL_WIN32MUTEXIMPL_H_
