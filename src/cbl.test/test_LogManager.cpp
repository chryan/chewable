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
 * @file test_LogManager.cpp
 * @brief Unit testing for log manager class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Debug/LogManager.h>
#include <cbl/Debug/ConsoleLogger.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

class LogManagerFixture : public ::testing::Test
{
protected:

	LogManagerFixture() : logMgr( LogManager::Instance() ) {}

	LogManager		& logMgr;

};

TEST_F( LogManagerFixture, LogManager_OutputTest )
{
	logMgr.Write( "No output", LogLevel::Info, __FILE__, __LINE__ );

	logMgr.Add( "ConsoleLogger", new ConsoleLogger );
	logMgr.Add( "ConsoleLogger2", new ConsoleLogger );

	logMgr.Write( "Output", LogLevel::Info, __FILE__, __LINE__ );

	ConsoleLogger * logger1 = static_cast< ConsoleLogger * >( logMgr.Get( "ConsoleLogger" ) );
	ConsoleLogger * logger2 = static_cast< ConsoleLogger * >( logMgr.Get( "ConsoleLogger2" ) );
	ILogger * emptyLogger = logMgr.Get( "Non-existant Logger" );

	ASSERT_TRUE( logger1 != NULL );
	ASSERT_TRUE( logger2 != NULL );
	ASSERT_TRUE( emptyLogger == NULL );

	logMgr.Remove( "ConsoleLogger" );
	logMgr.Remove( "ConsoleLogger2" );

	logMgr.Write( "No output", LogLevel::Info, __FILE__, __LINE__ );
}