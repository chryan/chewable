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
 * @file ProfileManager.cpp
 * @brief Profile manager class.
 */


// Precompiled Headers //
#include "cbl/StdAfx.h"

#if CBL_PROFILING_ENABLED == CBL_ENABLED

// Chewable Headers //
#include "cbl/Util/TimeSpan.h"
#include "cbl/Debug/ProfileManager.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

#include <unordered_map>
#include <intsafe.h>

using namespace cbl;

namespace cbl {
struct Profile {
	typedef std::unordered_map<Hash,Profile> Children;

	Profile();

	cbl::Hash	ID;
	Profile*	Parent;
	Children	ChildList;
	Int64		StartTime;
	Int64		TotalTime;
	Int64		MinTime;
	Int64		MaxTime;
	Int32		Recurse;
	Int32		Samples;
};
}

inline Profile::Profile()
: Parent(NULL)
, StartTime(0)
, TotalTime(0)
, MinTime(INT64_MAX)
, MaxTime(0)
, Recurse(0)
, Samples(0)
{
}

ProfileManager::ProfileManager()
: mStackCount(0)
, mLongestLine(30)
, mRoot( new Profile() )
{
	mCurrent = mRoot;
}

ProfileManager::~ProfileManager()
{
	// write profiles here.
	GenerateStatistics("FullProfile.log");

	CBL_DELETE( mRoot );
}

void ProfileManager::Enter( const Char* id )
{
	if( !id ) return;

	++mStackCount;
	if( mCurrent->ID.GetHash() == HashFunction<cbl::HashType::Murmur>::Generate(id) )  {
		++(mCurrent->Recurse);
		++(mCurrent->Samples);
		return;
	}

	Profile * profile	= &mCurrent->ChildList[id];
	profile->ID			= id;
	profile->Parent		= mCurrent;
	++(profile->Samples);

	if( profile->ID.GetName().length() + mStackCount * 2 > mLongestLine )
		mLongestLine = profile->ID.GetName().length() + mStackCount * 2;

	mCurrent			= profile;
	mCurrent->StartTime	= Stopwatch::GetInternalTicks();
}

void ProfileManager::Exit( void )
{
	if( mStackCount - 1 < 0 ) return;

	--mStackCount;
	if( (--mCurrent->Recurse) > 0 ) return;

	Int64 time = Stopwatch::GetInternalTicks() - mCurrent->StartTime;

	mCurrent->TotalTime += time;
	if( time < mCurrent->MinTime ) mCurrent->MinTime = time;
	if( time > mCurrent->MaxTime ) mCurrent->MaxTime = time;
	mCurrent = mCurrent->Parent;
}

void ProfileManager::GenerateStatistics(const char* filename)
{
	std::ofstream file;
	file.open( filename );
	file << std::left << std::setw(mLongestLine+1) << "Function Name" <<
		std::left << std::setw(20) << "| Total Time(s)" << 
		std::left << std::setw(20) << "| Min Time(s)" << 
		std::left << std::setw(20) << "| Max Time(s)" << 
		std::left << std::setw(20) << "| Avg Time(s)" << 
		std::left << std::setw(20) << "| Calls" << std::endl;

	file << std::setfill('-');

	file << std::left << std::setw(mLongestLine+1) << "-" <<
		std::left << std::setw(20) << "|" <<
		std::left << std::setw(20) << "|" <<
		std::left << std::setw(20) << "|" <<
		std::left << std::setw(20) << "|" <<
		std::left << std::setw(20) << "|" << std::endl;

	file << std::setfill(' ');

	dumpNode( file, mRoot, -1 );
	file.close();
}

void ProfileManager::dumpNode( std::ostream & stream, Profile * profile, Int32 space )
{
	if( profile->ID.GetName().length() > 0 ) {
		std::string id;
		for( int i = 0; i < space; ++i )
			id += "  ";
		id += profile->ID.GetName();
		TimeReal totalTime = cbl::TimeReal( profile->TotalTime ) / Stopwatch::GetSystemFrequency();
		TimeReal minTime = cbl::TimeReal( profile->MinTime ) / Stopwatch::GetSystemFrequency();
		TimeReal maxTime = cbl::TimeReal( profile->MaxTime ) / Stopwatch::GetSystemFrequency();

		stream << std::left << std::setw(mLongestLine+1) << id << "| " <<
			std::left << std::setw(18) << totalTime << "| " <<
			std::left << std::setw(18) << minTime << "| " <<
			std::left << std::setw(18) << maxTime << "| " <<
			std::left << std::setw(18) << totalTime / profile->Samples << "| " <<
			std::left << std::setw(18) << profile->Samples << std::endl;
	}

	++space;
	Profile::Children & c = profile->ChildList;
	for( Profile::Children::iterator it = c.begin(); it != c.end(); ++it ) {
		dumpNode( stream, &(it->second), space );
	}
}
#endif