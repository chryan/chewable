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
 * @file test_Hash.cpp
 * @brief Unit testing for hash class.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Memory/Heap.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

struct HeapTest {
	cbl::Uint32 x;
	cbl::Uint32 y;
	cbl::Uint32 z;

    HeapTest() {
    }

    HeapTest( int t ) {
        x = y = z = t;
    }

    HeapTest( const HeapTest& rhs ) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
    }
};

TEST( HeapFixtureTest, Heap_AllocDeallocTest ) {
    static const Uint32 amt = 1024;

	Heap<HeapTest,amt>	heapTest;
	HeapTest* arr[amt];

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		arr[i] = heapTest.Allocate();
		ASSERT_TRUE( arr[i] != NULL );
		arr[i]->x = i + 5;
		arr[i]->y = i + 5;
		arr[i]->z = i + 5;
	}

	ASSERT_TRUE( heapTest.Allocate() == NULL );

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_EQ( arr[i]->x, i + 5 );
		ASSERT_EQ( arr[i]->y, i + 5 );
		ASSERT_EQ( arr[i]->z, i + 5 );
	}

	ASSERT_TRUE( heapTest.Allocate() == NULL );

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_TRUE( heapTest.Deallocate( arr[i] ) );
	}

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_FALSE( heapTest.Deallocate( arr[i] ) );
	}

	// Test the allocations for a second time.
	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		arr[i] = heapTest.Allocate();
		arr[i]->x = i + 5;
		arr[i]->y = i + 5;
		arr[i]->z = i + 5;
	}

	ASSERT_TRUE( heapTest.Allocate() == NULL );

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_EQ( arr[i]->x, i + 5 );
		ASSERT_EQ( arr[i]->y, i + 5 );
		ASSERT_EQ( arr[i]->z, i + 5 );
	}

	ASSERT_TRUE( heapTest.Allocate() == NULL );

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_TRUE( heapTest.Deallocate( arr[i] ) );
	}

	for( cbl::Uint32 i = 0; i < amt; ++i ) {
		ASSERT_FALSE( heapTest.Deallocate( arr[i] ) );
	}
}

TEST( HeapFixtureTest, Heap_FragmentedTest ) {
	Heap<HeapTest,1024>	heapTest;
	HeapTest* arr[2][256];

	for( cbl::Uint32 i = 0; i < 128; ++i ) {
		arr[0][i] = heapTest.Allocate();
		ASSERT_TRUE( arr[0][i] != NULL );
	}
	for( cbl::Uint32 i = 0; i < 128; ++i ) {
		arr[1][i] = heapTest.Allocate();
		ASSERT_TRUE( arr[1][i] != NULL );
	}

	for( cbl::Uint32 i = 128; i < 256; ++i ) {
		arr[0][i] = heapTest.Allocate();
		ASSERT_TRUE( arr[0][i] != NULL );
	}
	for( cbl::Uint32 i = 128; i < 256; ++i ) {
		arr[1][i] = heapTest.Allocate();
		ASSERT_TRUE( arr[1][i] != NULL );
	}


	for( cbl::Uint32 i = 0; i < 256; ++i ) {
		ASSERT_TRUE( heapTest.Deallocate( arr[0][i] ) );
	}
	for( cbl::Uint32 i = 0; i < 256; ++i ) {
		ASSERT_FALSE( heapTest.Deallocate( arr[0][i] ) );
	}

	for( cbl::Uint32 i = 0; i < 256; ++i ) {
		ASSERT_TRUE( heapTest.Deallocate( arr[1][i] ) );
	}
	for( cbl::Uint32 i = 0; i < 256; ++i ) {
		ASSERT_FALSE( heapTest.Deallocate( arr[1][i] ) );
	}
}

TEST( HeapFixtureTest, Heap_AllocDeallocNonPower2Test ) {

    static const Uint32 amt = 1001;

    Heap<HeapTest,amt>	heapTest;
    HeapTest* arr[amt];

    HeapTest init;
    init.x = 0;
    init.y = 0;
    init.z = 0;

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        arr[i] = heapTest.Allocate(init);
        ASSERT_TRUE( arr[i] != NULL );
        ASSERT_EQ( arr[i]->x, 0 );
        arr[i]->x = i + 5;
        ASSERT_EQ( arr[i]->y, 0 );
        arr[i]->y = i + 5;
        ASSERT_EQ( arr[i]->z, 0 );
        arr[i]->z = i + 5;
    }

    ASSERT_TRUE( heapTest.Allocate() == NULL );

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_EQ( arr[i]->x, i + 5 );
        ASSERT_EQ( arr[i]->y, i + 5 );
        ASSERT_EQ( arr[i]->z, i + 5 );
    }

    ASSERT_TRUE( heapTest.Allocate() == NULL );

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_TRUE( heapTest.Deallocate( arr[i] ) );
    }

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_FALSE( heapTest.Deallocate( arr[i] ) );
    }

    // Test the allocations for a second time.
    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        arr[i] = heapTest.Allocate(1);
        ASSERT_EQ( arr[i]->x, 1 );
        arr[i]->x = i + 5;
        ASSERT_EQ( arr[i]->y, 1 );
        arr[i]->y = i + 5;
        ASSERT_EQ( arr[i]->z, 1 );
        arr[i]->z = i + 5;
    }

    ASSERT_TRUE( heapTest.Allocate() == NULL );

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_EQ( arr[i]->x, i + 5 );
        ASSERT_EQ( arr[i]->y, i + 5 );
        ASSERT_EQ( arr[i]->z, i + 5 );
    }

    ASSERT_TRUE( heapTest.Allocate() == NULL );

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_TRUE( heapTest.Deallocate( arr[i] ) );
    }

    for( cbl::Uint32 i = 0; i < amt; ++i ) {
        ASSERT_FALSE( heapTest.Deallocate( arr[i] ) );
    }
}