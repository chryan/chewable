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
 * @file Hash.cpp
 * @brief Hashed string object.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include "cbl/Util/Hash.h"
#include "cbl/Debug/Assert.h"
#include "cbl/Debug/Logging.h"

#if( defined(__GNUC__) && defined(__i386__) ) || defined(__WATCOMC__)\
  || defined(_MSC_VER) || defined (__BORLANDC__) || defined (__TURBOC__) 
	#define Get16Bits( val ) ( *( ( const Uint16 * )( val ) ) )
#else
	#define Get16Bits( val ) ((((uint32_t)(((const Uint8 *)(d))[1])) << 8)\
						   +(uint32_t)(((const Uint8 *)(d))[0]) )
#endif

using namespace cbl;

void Hash::ToString( String& str, const Type*, const void* obj, const FieldAttr* )
{
	str = (*(Hash*)obj).GetText();
}

void Hash::FromString( const String& str, const Type*, void* obj, const FieldAttr* )
{
	(*(Hash*)obj) = str;
}

Hash::~Hash()
{
}

Hash& Hash::operator = ( const Char* name )
{
	mText = name ? name : "";
	mHash = name ? Generate( mText.c_str(), mText.length() ) : 0;
	return *this;
}

Hash& Hash::operator = ( const String& name )
{
	mText = name;
	mHash = Generate( mText.c_str(), mText.length() );
	return *this;
}

typedef unsigned char uint8_t;
typedef unsigned long uint32_t;
typedef unsigned __int64 uint64_t;

#if defined(_MSC_VER)
#define FORCE_INLINE    __forceinline
#define ROTL32(x,y)     _rotl(x,y)
#define ROTL64(x,y)     _rotl64(x,y)
#define BIG_CONSTANT(x) (x)
#else   // defined(_MSC_VER)
#define FORCE_INLINE __attribute__((always_inline))
inline uint32_t rotl32 ( uint32_t x, int8_t r ) {
	return (x << r) | (x >> (32 - r));
}

inline uint64_t rotl64 ( uint64_t x, int8_t r ) {
	return (x << r) | (x >> (64 - r));
}
#define ROTL32(x,y)     rotl32(x,y)
#define ROTL64(x,y)     rotl64(x,y)
#define BIG_CONSTANT(x) (x##LLU)
#endif // !defined(_MSC_VER)

FORCE_INLINE uint32_t getblock ( const uint32_t * p, int i ) {
	return p[i];
}

FORCE_INLINE uint32_t fmix ( uint32_t h ) {
	h ^= h >> 16;
	h *= 0x85ebca6b;
	h ^= h >> 13;
	h *= 0xc2b2ae35;
	h ^= h >> 16;

	return h;
}

HashValue Hash::Generate( const Char* string, Int32 length )
{
	if( length == 0 ) return 0;
	const uint8_t * data = (const uint8_t*)string;
	const int nblocks = length / 4;

	static const uint32_t seed = 0;
	uint32_t h1 = seed;

	uint32_t c1 = 0xcc9e2d51;
	uint32_t c2 = 0x1b873593;

	const uint32_t * blocks = (const uint32_t *)(data + nblocks*4);

	for(int i = -nblocks; i; ++i)
	{
		uint32_t k1 = getblock(blocks,i);

		k1 *= c1;
		k1 = ROTL32(k1,15);
		k1 *= c2;

		h1 ^= k1;
		h1 = ROTL32(h1,13); 
		h1 = h1*5+0xe6546b64;
	}

	const uint8_t * tail = (const uint8_t*)(data + nblocks*4);

	uint32_t k1 = 0;

	switch(length & 3)
	{
	case 3: k1 ^= tail[2] << 16;
	case 2: k1 ^= tail[1] << 8;
	case 1: k1 ^= tail[0];
		k1 *= c1; k1 = ROTL32(k1,16); k1 *= c2; h1 ^= k1;
	};

	h1 ^= length;
	h1 = fmix(h1);

	return h1;
}
