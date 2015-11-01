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
 * @file Chewable.h
 * @brief Essential header inclusions.
 */

#ifndef __CBL_CHEWABLE_H_
#define __CBL_CHEWABLE_H_

#include "cbl/Config.h"
#include "cbl/Platform.h"
#include "cbl/TypeDefs.h"
#include "cbl/Util/Helpers.h"

// disable: "<type> needs to have dll-interface to be used by clients'
// Happens on STL member variables which are not public therefore is ok
#   pragma warning( disable : 4251 )

#define _TPL template< typename T1 >
#define _TPL2 template< typename T1, typename T2 >
#define _TPL3 template< typename T1, typename T2, typename T3 >

// Forward Declarations //
namespace cbl
{
	// Core //
	class DrawableGameComponent;
	class Game;
	class GameComponent;
	class GameComponentCollection;
	class GameState;
	class GameStateManager;
	class GameTime;
	class IDrawable;
	class IUpdatable;
	class Object;
	class ObjectPart;
	class ObjectPartTable;
	class ObjectGroups;
	class ObjectManager;
	class Services;

	// Debug //
#if CBL_LOGGING_ENABLED == CBL_ENABLED
	class ConsoleLogger;
	class FileLogger;
	class ILogger;
	class LogManager;
#endif
#if CBL_PROFILING_ENABLED == CBL_ENABLED
	class ProfileManager;
#endif
	// Math //
	class Matrix3;
	class Matrix4;
	_TPL class Vector2;
	_TPL class Vector3;
	_TPL class Vector4;

	// Reflection //
	class CblRegistrar;
	class Deserialiser;
	class Entity;
	class EntityManager;
	class FieldAttr;
	class Field;
	class Serialiser;
	class Type;
	class TypeDB;

	// Thread //
	class Mutex;
	class Runnable;
	class Thread;
	class ThreadData;
	
	// Utility //
	class ByteStream;
	struct CName;
	class Colour;
	class FileInfo;
	class FileSystem;
	class Hash;
	class Noncopyable;
	_TPL class SharedPtr;
	class Stopwatch;
	class TimeSpan;
	_TPL class WeakPtr;
}

#undef _TPL3
#undef _TPL2
#undef _TPL

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cstdarg>
#include <vector>
#include <map>
#include <string>
#include <set>
#include <list>
#include <deque>
#include <queue>
#include <bitset>
#include <algorithm>
#include <functional>
#include <limits>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <initializer_list>

#include "cbl/Memory/MemDebugger.h" // Memory manager must be included after STL and before local headers.

#endif // __CBL_CHEWABLE_H_