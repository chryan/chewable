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
 * @file TypeDB.cpp
 * @brief Type information database.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Reflection/TypeDB.h"

using namespace cbl;

TypeDB::TypeDB()
{
	Create<Int8>().DefaultSerialisers<Int8>();
	Create<Int16>().DefaultSerialisers<Int16>();
	Create<Int32>().DefaultSerialisers<Int32>();
	Create<Int64>().DefaultSerialisers<Int64>();
	Create<Uint8>().DefaultSerialisers<Uint8>();
	Create<Uint16>().DefaultSerialisers<Uint16>();
	Create<Uint32>().DefaultSerialisers<Uint32>();
	Create<Uint64>().DefaultSerialisers<Uint64>();
	Create<Float32>().DefaultSerialisers<Float32>();
	Create<Float64>().DefaultSerialisers<Float64>();
	Create<Char>().DefaultSerialisers<Char>();
	Create<Uchar>().DefaultSerialisers<Uchar>();
	Create<String>().DefaultSerialisers<String>();
	Create<bool>().DefaultSerialisers<bool>();
}

TypeDB::~TypeDB()
{
	CBL_FOREACH( TypeMap, it, mTypes )
		CBL_DELETE( it->second );
	mTypes.clear();
}
