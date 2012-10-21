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
 * @file test_String.cpp
 * @brief Unit testing for the string class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Util/String.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

#if CBL_CUSTOM_STRING == CBL_ENABLED
const Char* helloc = "Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!";
std::string hello1 = "Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!";
std::string hello2 = "Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!";
cbl::String cblhello1 = "Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!";
cbl::String cblhello2 = "Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!Hello!";

TEST( StringFixture, CblStringAssignmentTest )
{
	cbl::String test;
	for( cbl::Uint32 i = 0; i < 100000000; ++i ) {
		test = cblhello1;
		test = cblhello2;
	}
}

TEST( StringFixture, StdStringAssignmentTest )
{
	std::string test;
	for( cbl::Uint32 i = 0; i < 100000000; ++i ) {
		test = hello1;
		test = hello2;
	}
}
#endif
