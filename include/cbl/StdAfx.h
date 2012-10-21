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
 * @file StdAfx.h
 * @brief Precompiled headers.
 */

// Precompiled Headers //
#include "cbl/Chewable.h"
#include "cbl/Config.h"
#include "cbl/Platform.h"
#include "cbl/TypeDefs.h"
#include "cbl/Util/String.h"
// Core //
#include "cbl/Core/DrawableGameComponent.h"
#include "cbl/Core/Event.h"
#include "cbl/Core/Game.h"
#include "cbl/Core/GameComponent.h"
#include "cbl/Core/GameComponentCollection.h"
#include "cbl/Core/GameState.h"
#include "cbl/Core/GameStateManager.h"
#include "cbl/Core/GameTime.h"
#include "cbl/Core/IDrawable.h"
#include "cbl/Core/IUpdatable.h"
#include "cbl/Core/Object.h"
#include "cbl/Core/ObjectPart.h"
#include "cbl/Core/ObjectPartTable.h"
#include "cbl/Core/ObjectGroups.h"
#include "cbl/Core/ObjectManager.h"
#include "cbl/Core/Services.h"
// Debug //
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/ConsoleLogger.h"
#include "cbl/Debug/FileLogger.h"
#include "cbl/Debug/ILogger.h"
#include "cbl/Debug/Logging.h"
#include "cbl/Debug/LogLevel.h"
#include "cbl/Debug/LogManager.h"
#include "cbl/Debug/ProfileManager.h"
#include "cbl/Debug/Profiling.h"
// Math //
#include "cbl/Math/Functions.h"
#include "cbl/Math/Matrix3.h"
#include "cbl/Math/Matrix4.h"
#include "cbl/Math/Vector2.h"
#include "cbl/Math/Vector3.h"
#include "cbl/Math/Vector4.h"
// Reflection //
#include "cbl/Reflection/CblRegistrar.h"
#include "cbl/Reflection/Typing.h"
#include "cbl/Reflection/BinaryDeserialiser.h"
#include "cbl/Reflection/BinarySerialiser.h"
#include "cbl/Reflection/Deserialiser.h"
#include "cbl/Reflection/Entity.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Reflection/EnumConst.h"
#include "cbl/Reflection/Field.h"
#include "cbl/Reflection/FieldContainer.h"
#include "cbl/Reflection/LinearDeserialiser.h"
#include "cbl/Reflection/LinearSerialiser.h"
#include "cbl/Reflection/NodeDeserialiser.h"
#include "cbl/Reflection/NodeSerialiser.h"
#include "cbl/Reflection/Serialiser.h"
#include "cbl/Reflection/Type.h"
#include "cbl/Reflection/TypeDB.h"
// Thread //
#include "cbl/Thread/Mutex.h"
#include "cbl/Thread/Runnable.h"
#include "cbl/Thread/Thread.h"
#include "cbl/Thread/ThreadData.h"
// Util //
#include "cbl/Util/ByteStream.h"
#include "cbl/Util/Colour.h"
#include "cbl/Util/Delegate.h"
#include "cbl/Util/FileInfo.h"
#include "cbl/Util/FileSystem.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Helpers.h"
#include "cbl/Util/Noncopyable.h"
#include "cbl/Util/Property.h"
#include "cbl/Util/SharedPtr.h"
#include "cbl/Util/Stopwatch.h"
#include "cbl/Util/String.h"
#include "cbl/Util/TimeSpan.h"
#include "cbl/Util/WeakPtr.h"
