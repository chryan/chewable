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
#include "cbl/Math/Functions.h"
#include "cbl/Util/Helpers.h"

namespace cbl
{
	template< class C, cbl::Uint32 HeapSize = 1024 >
	class Heap
    {
    /***** Public Methods *****/
	public:
        //! Constructor.
		Heap();
        //! Destructor.
		~Heap();
        //! Default object allocation.
		C* Allocate();
        
//! Heap allocation template methods.
#define ALLOC_DECL( paramCount )\
        template< CBL_TPLPARAM_REPEAT(A, paramCount) >\
        C* Allocate( CBL_PARAM_REPEAT_DECL(A, a, paramCount) )

        ALLOC_DECL(1);
        ALLOC_DECL(2);
        ALLOC_DECL(3);
        ALLOC_DECL(4);
        ALLOC_DECL(5);
        ALLOC_DECL(6);
        ALLOC_DECL(7);
        ALLOC_DECL(8);
        ALLOC_DECL(9);
        ALLOC_DECL(10);

#undef ALLOC_DECL

		bool Deallocate( C* mem );

    private:
        Char* _AllocateSpace( void );

    /***** Private Static Members *****/
	private:
        static const Uint32 sSpareBits = HeapSize % 32;
		// We get the number of bit slots we need by taking the StackSize / 32 (number of bits in a Uint32).
		static const Uint32 sBitSlots = sSpareBits ? HeapSize / 32 + 1 : HeapSize / 32;
        static const Uint32 sBitSlotSize = sBitSlots * sizeof(Uint32);

    /***** Private Members *****/
	private:
		Char*           mMemAlloc;  //!< Allocated memory.
	};
}

#include "Heap.inl"

#endif // __CBL_HEAP_H_
