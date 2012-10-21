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
 * @file VectorContainer_Impl.h
 * @brief Vector field container reflection implementation.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_VECTORCONTAINER_IMPL_H_
#define __CBL_VECTORCONTAINER_IMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Reflection/FieldContainer.h"
#include "cbl/Debug/Assert.h"

namespace cbl
{
	namespace detail
	{
		template< typename VECTOR_TYPE >
		class VectorReadIterator_Impl :
			public FieldReadIterator
		{
		public:
			VectorReadIterator_Impl( const VECTOR_TYPE* container )
				: mContainer(*container), mPosition(0) {}

			virtual const void* GetKey( void ) const {
				return NULL;
			}

			virtual const void* GetValue( void ) const {
				CBL_ASSERT_TRUE( mPosition < mContainer.size() );
				return &(mContainer[mPosition]);
			}

			virtual bool IncNext( void ) const {
				if( mPosition >= mContainer.size() ) return false;
				++mPosition;
				return true;
			}

			virtual bool IsValid( void ) const {
				return mPosition < mContainer.size();
			}

			virtual Uint32 Count( void ) const {
				return mContainer.size();
			}

		private:
			const VECTOR_TYPE&	mContainer;
			mutable Uint32		mPosition;
		};

		template< typename VECTOR_TYPE >
		class VectorWriteIterator_Impl :
			public FieldWriteIterator
		{
		public:
			inline VectorWriteIterator_Impl( VECTOR_TYPE* container )
				: mContainer( *container ) {}

			virtual bool Add( void* obj ) {
				mContainer.push_back( *(VECTOR_TYPE::value_type*)obj );
				return true;
			}

			virtual bool Add( void*, void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

			virtual void* AddEmpty( void ) {
				mContainer.push_back( VECTOR_TYPE::value_type() );
				return &mContainer.back();
			}

			virtual void* AddEmpty( void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

		private:
			VECTOR_TYPE&	mContainer;
		};

		//! POD array container creation specialization.
		template <typename TYPE, typename ALLOCATOR>
		FieldContainer* CreateContainer( std::vector<TYPE, ALLOCATOR>& )
		{
			FieldContainer* cont = new FieldContainer_Impl<
				std::vector<TYPE, ALLOCATOR>,
				VectorReadIterator_Impl< std::vector<TYPE, ALLOCATOR> >,
				VectorWriteIterator_Impl< std::vector<TYPE, ALLOCATOR> > >();

			cont->ValueType			= &CBL_ENT.Types.Create<TYPE>();
			cont->IsValuePointer	= IsPtr<TYPE>::Value;

			return cont;
		}
	}
}

#endif // __CBL_VECTORCONTAINER_IMPL_H_
