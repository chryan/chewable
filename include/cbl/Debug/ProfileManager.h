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
 * @file ProfileManager.h
 * @brief Profile manager class.
 */

#ifndef __CBL_PROFILEMANAGER_H_
#define __CBL_PROFILEMANAGER_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_PROFILING_ENABLED == CBL_ENABLED

// Chewable Headers //
#include "cbl/Debug/Assert.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Singleton.h"
#include "cbl/Thread/Mutex.h"
#include "cbl/Util/Hash.h"

namespace cbl
{
	//! @brief Profile management class.
	struct Profile;

	class CBL_API ProfileManager
	{
	public:
		struct Scope {
			inline Scope(const Char* id) { ProfileManager::Instance().Enter( id ); }
			inline ~Scope() { ProfileManager::Instance().Exit(); }
		};

	/***** Public Methods *****/
	public:
		~ProfileManager();

		void Enter( const Char* id );
		void Exit( void );
		void GenerateStatistics(const Char* filename);

	/***** Private Methods *****/
	private:
		ProfileManager();
		void dumpNode( std::ostream & stream, Profile * profile, Int32 spacing );

	private:
		Profile *		mRoot;
		Profile *		mCurrent;
		Uint32			mLongestLine;
		Int32			mStackCount;
		CBL_DECL_SINGLETON( ProfileManager );
	};
}

#endif // CBL_PROFILING_ENABLED == CBL_ENABLED

#endif // __CBL_PROFILEMANAGER_H_
