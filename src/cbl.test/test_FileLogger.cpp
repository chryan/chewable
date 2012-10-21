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
 * @file test_FileLogger.cpp
 * @brief Unit testing for file logger class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Debug/FileLogger.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class FileLoggerFixture : public ::testing::Test
{
public:

	FileLoggerFixture()
		: logger( "Chewable_FileLogger_Test.log" )
	{
	}

protected:

	FileLogger		logger;
};

TEST_F( FileLoggerFixture, FileLogger_OutputTest )
{
	String file = String( __FILE__ );
	file = file.substr( file.find_last_of( '\\' ) + 1 );
	logger.Write( "Hello! This message will exceed the maximum Character limit per line in a log file."
		"Testing this is quite a chore and requires a lot of text to do so.", LogLevel::Info, file.c_str(), __LINE__ );
	logger.Threshold = LogLevel::Debug;
	logger.Write( "Debug!\nMessage!", LogLevel::Debug, file.c_str(), __LINE__ );
	logger.Write( "Warning!", LogLevel::Warning, file.c_str(), __LINE__ );
}