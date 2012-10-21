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
 * @file test_ILogger.cpp
 * @brief Unit testing for logger class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Debug/ILogger.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class ConsoleLoggerTest : public ILogger
{
public:
	String		StoredMessage;

protected:

	virtual void Output( Char const * const message, LogLevel::Options msgLevel,
		const Char * file, Uint32 line )
	{
		std::cout << "[ConsoleLoggerTest] Output: " << message << " from:" << file << ":" << line << std::endl;
		StoredMessage = message;
	}
};

class LogStreamFixture : public ::testing::Test
{
protected:

	ConsoleLoggerTest		logger;
};

TEST_F( LogStreamFixture, LogStream_OutputTest )
{
	logger.Write( "HELLO", LogLevel::Info, __FILE__, __LINE__ );
	ASSERT_TRUE( logger.StoredMessage == "HELLO" );

	logger.Threshold = LogLevel::Debug | LogLevel::Info;
	logger.Write( "WORLD!", LogLevel::Warning, __FILE__, __LINE__ );
	ASSERT_FALSE( logger.StoredMessage == "WORLD!" );
}