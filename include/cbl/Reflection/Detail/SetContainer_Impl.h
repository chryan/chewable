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
 * @file SetContainer_Impl.h
 * @brief Set field container reflection implementation.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_SETCONTAINER_IMPL_H_
#define __CBL_SETCONTAINER_IMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Reflection/FieldContainer.h"
#include "cbl/Debug/Assert.h"

// External Libraries //
#include <set>
#include <unordered_set>

namespace cbl
{
	namespace detail
	{
		//! Set/Hashed set iterator
		template< typename SET_TYPE >
		class SetReadIterator_Impl :
			public FieldReadIterator
		{
		public:
			typedef typename SET_TYPE::const_iterator				Iterator;

		public:
			inline SetReadIterator_Impl( const SET_TYPE* container )
				: mContainer( *container ), mIterator( container->begin() ) {}

			virtual const void* GetKey( void ) const {
				return NULL;
			}

			virtual const void* GetValue( void ) const {
				CBL_ASSERT_TRUE( mIterator != mContainer.end() );
				return &(*mIterator);
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
			const SET_TYPE&		mContainer;
			mutable Iterator	mIterator;
		};

		template< typename SET_TYPE >
		class SetWriteIterator_Impl :
			public FieldWriteIterator
		{
		public:
			typedef typename SET_TYPE::const_iterator			Iterator;
			typedef typename SET_TYPE::value_type				ValueType;

		public:
			inline SetWriteIterator_Impl( SET_TYPE* container )
				: mContainer( *container ) {}

			virtual bool Add( void* obj ) {
				return mContainer.insert( *( ValueType* )obj ).second;
			}

			virtual bool Add( void*, void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

			virtual void* AddEmpty( void ) {
				return &mContainer.insert( ValueType() );
			}

			virtual void* AddEmpty( void* key ) {
				CBL_FAIL( "Feature not implemented." );
				return NULL;
			}

		private:
			SET_TYPE&	mContainer;
		};

		//! std::set container creation specialization.
		template< typename KEY, typename COMPARE, typename ALLOC >
		FieldContainer* CreateContainer( std::set<KEY, COMPARE, ALLOC>& )
		{
			// Can't deal with keys that are pointers
			CBL_STATIC_ASSERT( IsPtr<KEY>::Value == false );

			typedef typename std::set<KEY, COMPARE, ALLOC> SetType;

			FieldContainer* cont = new FieldContainer_Impl<
				SetType,
				SetReadIterator_Impl<SetType>,
				SetWriteIterator_Impl<SetType> >();

			cont->ValueType			= &CBL_ENT.Types.Create<KEY>();
			cont->IsValuePointer	= IsPtr<KEY>::Value;

			return cont;
		}

		//! std::unordered_set container creation specialization.
		template< typename KEY, typename COMPARE, typename ALLOC >
		FieldContainer* CreateContainer( std::unordered_set<KEY, COMPARE, ALLOC>& )
		{
			// Can't deal with keys that are pointers
			CBL_STATIC_ASSERT( IsPtr<KEY>::Value == false );

			typedef typename std::unordered_set<KEY, COMPARE, ALLOC> SetType;

			FieldContainer* cont = new FieldContainer_Impl<
				SetType,
				SetReadIterator_Impl<SetType>,
				SetWriteIterator_Impl<SetType> >();

			cont->ValueType			= &CBL_ENT.Types.Create<KEY>();
			cont->IsValuePointer	= IsPtr<KEY>::Value;

			return cont;
		}
	}
}

#endif // __CBL_SETCONTAINER_IMPL_H_
