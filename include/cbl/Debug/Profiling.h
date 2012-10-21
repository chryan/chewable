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
 * @file Profiling.h
 * @brief Profile utilities. Include this file to use profiling features.
 */

#ifndef __CBL_PROFILING_H_
#define __CBL_PROFILING_H_

// Chewable Headers //
#include "cbl/Chewable.h"

#if CBL_PROFILING_ENABLED == CBL_ENABLED

#define CBL_PROFILE_COMPONENTS	CBL_ENABLED

// Chewable Headers //
#include "cbl/Debug/ProfileManager.h"

/***** Profiling Macros *****/
//! Start automatic scoped function profiling.
#define CBL_PROFILE_FUNCTION\
	cbl::ProfileManager::Scope _profile##__COUNTER__( __FUNCTION__ )
//! Start automatic scoped function-section profiling.
#define CBL_PROFILE_SECTION( name )\
	cbl::ProfileManager::Scope _profile##__COUNTER__( #name )

#else
#define CBL_PROFILE_FUNCTION
#define CBL_PROFILE_SECTION( name )
#endif // CBL_PROFILING_ENABLED == CBL_ENABLED

#endif // __CBL_PROFILING_H_