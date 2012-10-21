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
 * @file Heap.h
 * @brief Fixed sized heap allocator.
 */

#ifndef __CBL_HEAP_H_
#define __CBL_HEAP_H_

// Chewable Headers //
#include "cbl/Chewable.h"

// Disable the 'default construction' warning.
#pragma warning( disable : 4345 )

namespace cbl
{
	inline unsigned int msb32(register unsigned int x)
	{
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return(x & ~(x >> 1));
	}

	inline unsigned int ones32(register unsigned int x)
	{
		x -= ((x >> 1) & 0x55555555);
		x = (((x >> 2) & 0x33333333) + (x & 0x33333333));
		x = (((x >> 4) + x) & 0x0f0f0f0f);
		x += (x >> 8);
		x += (x >> 16);
		return(x & 0x0000003f);
	}

	inline unsigned int lzc(register unsigned int x)
	{
		x |= (x >> 1);
		x |= (x >> 2);
		x |= (x >> 4);
		x |= (x >> 8);
		x |= (x >> 16);
		return(32 - ones32(x));
	}

	template< class C, cbl::Uint32 HeapSize = 1024 >
	class Heap{
	public:
		Heap() {
			mMemAlloc = new cbl::Char[ sizeof(C) * HeapSize + sBitSlots ];
			memset( mMemAlloc, 0, sBitSlots ); // Initialise memory bit slots to 0.
		}

		~Heap() {
			delete [] mMemAlloc;
		}

		C* Allocate() {
			cbl::Uint32* mem = reinterpret_cast<cbl::Uint32*>(mMemAlloc);
			cbl::Uint32 loopCount = HeapSize / 32;
			for( cbl::Uint32 i = 0; i < loopCount; ++i ) {
				cbl::Uint32 availBit = msb32( ~(*mem) );
				if( availBit != 0 ) {
					*mem |= availBit; // set the 'allocated' bit.
					return reinterpret_cast<C*>( new (mMemAlloc + sBitSlots + ( i * 32 + lzc(availBit) ) * sizeof(C)) C() );
				}
				++mem;
			}

			//LOG( cbl::LogLevel::Error << "Heap overflow." ); // Heap overflow.
			return NULL;
		}

		C* Allocate( const C& cpy ) {
			cbl::Uint32* mem = reinterpret_cast<cbl::Uint32*>(mMemAlloc);

			for( cbl::Uint32 i = 0; i < HeapSize / 32; ++i ) {
				cbl::Uint32 availBit = msb32( ~(*mem) );
				if( availBit != 0 ) {
					*mem |= availBit; // set the 'allocated' bit.
					return reinterpret_cast<C*>( new (mMemAlloc + sBitSlots + ( i * 32 + lzc(availBit) ) * sizeof(C)) C(cpy) );
				}
				++mem;
			}

			//LOG( cbl::LogLevel::Error << "Heap overflow." ); // Heap overflow.
			return NULL;
		}

		bool Deallocate( C* mem ) {
			cbl::Uint32 arraypos	= ( reinterpret_cast<cbl::Char*>(mem) - ( mMemAlloc + sBitSlots ) ) / sizeof(C);
			cbl::Uint32 bitpos		= arraypos % 32;
			cbl::Uint32* mempos		= reinterpret_cast<cbl::Uint32*>(mMemAlloc) + arraypos / 32;
			if( ( *mempos & ( 0x80000000 >> bitpos ) ) == 0 )
				return false;
			*mempos ^= ( 0x80000000 >> bitpos );
			return true;
		} 

	private:
		// We get the number of bit slots we need by taking the StackSize / 8 (number of bits in char).
		static const cbl::Uint32 sBitSlots = HeapSize / 8;

	private:
		cbl::Char*			mMemAlloc;
	};
}

#endif // __CBL_HEAP_H_
