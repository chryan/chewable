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
 * @file MemDebugger.h
 * @brief Memory debugger for leak detection. Just uses VLD for now.
 */

#ifndef __CBL_MEMDEBUGGER_H_
#define __CBL_MEMDEBUGGER_H_

// Chewable Headers //
#include "cbl/Config.h"
#include "cbl/Platform.h"

#if ( CBL_COMPILER == CBL_COMPILER_MSVC ) && \
( CBL_MEMORY_MANAGER == CBL_MEMORY_MANAGER_DEBUG )
	// Enable MSVC memory tracker.
	#define _CRTDBG_MAP_ALLOC
	#include <stdlib.h>
	#include <crtdbg.h>

	#if CBL_VLD_ENABLED == CBL_ENABLED
		#include <windows.h>
		#include <vld.h>
	#endif
#endif

#endif // __CBL_MEMDEBUGGER_H_
