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
 * @file MapContainer_Impl.h
 * @brief Map field container reflection implementation.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_MAPCONTAINER_IMPL_H_
#define __CBL_MAPCONTAINER_IMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Reflection/FieldContainer.h"
#include "cbl/Debug/Assert.h"

// External Libraries //
#include <map>
#include <unordered_map>

namespace cbl
{
	namespace detail
	{
		//! Map/Hashed map iterator
		template< typename MAP_TYPE >
		class MapReadIterator_Impl :
			public FieldReadIterator
		{
		public:
			typedef typename MAP_TYPE::const_iterator				Iterator;

		public:
			inline MapReadIterator_Impl( const MAP_TYPE* container )
				: mContainer( *container ), mIterator( container->begin() ) {}

			virtual const void* GetKey( void ) const {
				CBL_ASSERT_TRUE( mIterator != mContainer.end() );
				return &(mIterator->first);
			}

			virtual const void* GetValue( void ) const {
				CBL_ASSERT_TRUE( mIterator != mContainer.end() );
				return &(mIterator->second);
			}

			virtual bool IncNext( void ) const {
				if( mIterator == mContainer.end() )
					return false;
				++mIterator;
				return true;
			}

			virtual bool IsValid( void ) const {
				return mIterator != mContainer.end();
			}

			virtual Uint32 Count( void ) const {
				return mContainer.size();
			}

		private:
			const MAP_TYPE&		mContainer;
			mutable Iterator	mIterator;
		};

		template< typename MAP_TYPE >
		class MapWriteIterator_Impl :
			public FieldWriteIterator
		{
		public:
			typedef typename MAP_TYPE::const_iterator			Iterator;
			typedef typename MAP_TYPE::value_type::first_type	KeyType;
			typedef typename MAP_TYPE::value_type::second_type	ValueType;

		public:
			inline MapWriteIterator_Impl( MAP_TYPE* container )
				: mContainer( *container ) {}

			virtual bool Add( void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

			virtual bool Add( void* key, void* obj ) {
				return mContainer.insert( std::make_pair( *(KeyType*)key, *( ValueType* )obj ) ).second;
			}

			virtual void* AddEmpty( void ) {
				CBL_FAIL( "Feature not implemented." );
				return NULL;
			}

			virtual void* AddEmpty( void* key ) {
				return &mContainer[ *(KeyType*)key ];
			}

		private:
			MAP_TYPE&	mContainer;
		};

		//! std::map container creation specialization.
		template< typename KEY, typename DATA, typename COMPARE, typename ALLOC >
		FieldContainer* CreateContainer( std::map<KEY, DATA, COMPARE, ALLOC>& )
		{
			// Can't deal with keys that are pointers
			CBL_STATIC_ASSERT( IsPtr<KEY>::Value == false );

			typedef typename std::map<KEY, DATA, COMPARE, ALLOC> MapType;

			FieldContainer* cont = new FieldContainer_Impl<
				MapType,
				MapReadIterator_Impl<MapType>,
				MapWriteIterator_Impl<MapType> >();

			cont->KeyType			= &CBL_ENT.Types.Create<KEY>();
			cont->ValueType			= &CBL_ENT.Types.Create<DATA>();
			cont->IsKeyPointer		= IsPtr<KEY>::Value;
			cont->IsValuePointer	= IsPtr<DATA>::Value;

			return cont;
		}

		//! std::unordered_map container creation specialization.
		template< typename KEY, typename DATA, typename COMPARE, typename ALLOC >
		FieldContainer* CreateContainer( std::unordered_map<KEY, DATA, COMPARE, ALLOC>& )
		{
			// Can't deal with keys that are pointers
			CBL_STATIC_ASSERT( IsPtr<KEY>::Value == false );

			typedef typename std::unordered_map<KEY, DATA, COMPARE, ALLOC> MapType;

			FieldContainer* cont = new FieldContainer_Impl<
				MapType,
				MapReadIterator_Impl<MapType>,
				MapWriteIterator_Impl<MapType> >();

			cont->KeyType			= &CBL_ENT.Types.Create<KEY>();
			cont->ValueType			= &CBL_ENT.Types.Create<DATA>();
			cont->IsKeyPointer		= IsPtr<KEY>::Value;
			cont->IsValuePointer	= IsPtr<DATA>::Value;

			return cont;
		}
	}
}

#endif // __CBL_MAPCONTAINER_IMPL_H_
