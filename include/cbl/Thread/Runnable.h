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
 * @file Runnable.h
 * @brief Runnable thread abstract class.
 */

#ifndef __CBL_RUNNABLE_H_
#define __CBL_RUNNABLE_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! Abstract class which provides the entry point for a thread.
	class CBL_API Runnable
	{
	public:
		Runnable();
		virtual ~Runnable();
		virtual void Run( void ) = 0;
	};
}

#endif // __CBL_RUNNABLE_H_
