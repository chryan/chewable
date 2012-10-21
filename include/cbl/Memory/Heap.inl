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
 * @file Heap.inl
 * @brief Fixed sized heap allocator.
 */

// Disable the 'default construction' warning.
#pragma warning( disable : 4345 )

namespace cbl
{
    template< class C, cbl::Uint32 HeapSize >
    Heap<C,HeapSize>::Heap()
    {
		mMemAlloc = new cbl::Char[ sizeof(C) * HeapSize + sBitSlotSize ];
		memset( mMemAlloc, 0, sBitSlotSize ); // Initialise memory bit slots to 0.
        // Set our trailing unused bits to 1 so we don't ever use them.
        if( sSpareBits ) {
            Uint32 bits = 0;
            Uint32 set = 1;
            Uint32 loop = 32 - sSpareBits;
            for( Uint32 i = 0; i < loop; ++i, set <<= 1 )
                bits |= set;
            *(reinterpret_cast<cbl::Uint32*>(mMemAlloc + sBitSlotSize - sizeof(Uint32))) = bits;
        }
	}

    template< class C, cbl::Uint32 HeapSize >
    Heap<C,HeapSize>::~Heap()
    {
		delete [] mMemAlloc;
	}

    template< class C, cbl::Uint32 HeapSize >
    inline C* Heap<C,HeapSize>::Allocate()
    {
        cbl::Char* _mem = _AllocateSpace();
        return _mem ? reinterpret_cast<C*>( new (_mem) C() ) : NULL;
	}

//! Heap allocation template definition.
#define ALLOC_DEF( paramCount )\
    template< class C, cbl::Uint32 HeapSize >\
    template< CBL_TPLPARAM_REPEAT(A, paramCount) >\
    inline C* Heap<C,HeapSize>::Allocate( CBL_PARAM_REPEAT_DECL(A, a, paramCount) )\
    {\
        cbl::Char* _mem = _AllocateSpace();\
        return _mem ? reinterpret_cast<C*>( new (_mem) C(CBL_PARAM_REPEAT(a, paramCount)) ) : NULL;\
    }

    ALLOC_DEF(1);
    ALLOC_DEF(2);
    ALLOC_DEF(3);
    ALLOC_DEF(4);
    ALLOC_DEF(5);
    ALLOC_DEF(6);
    ALLOC_DEF(7);
    ALLOC_DEF(8);
    ALLOC_DEF(9);
    ALLOC_DEF(10);

#undef ALLOC_DEF

    template< class C, cbl::Uint32 HeapSize >
    bool Heap<C,HeapSize>::Deallocate( C* mem )
    {
		Uint32 arraypos	= ( reinterpret_cast<Char*>(mem) - ( mMemAlloc + sBitSlotSize ) ) / sizeof(C);
		Uint32 bitpos		= arraypos % 32;
		Uint32* mempos		= reinterpret_cast<Uint32*>(mMemAlloc) + arraypos / 32;
		if( ( *mempos & ( 0x80000000 >> bitpos ) ) == 0 )
			return false;
		*mempos ^= ( 0x80000000 >> bitpos );
		return true;
	}

    template< class C, cbl::Uint32 HeapSize >
    Char* Heap<C,HeapSize>::_AllocateSpace( void )
    {
        Uint32* mem = reinterpret_cast<cbl::Uint32*>(mMemAlloc);
        for( Uint32 i = 0; i < sBitSlots; ++i )
        {
            Uint32 availBit = Math::MostSigBit32( ~(*mem) );
            if( availBit != 0 ) {
                *mem |= availBit; // set the 'allocated' bit.
                return (mMemAlloc + sBitSlotSize + ( i * 32 + Math::LastZeroBitPos(availBit) ) * sizeof(C));
            }
            ++mem;
        }

        return NULL;
    }
}
