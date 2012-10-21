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
 * @file ArrayContainer_Impl.h
 * @brief Array field container reflection implementation.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_ARRAYCONTAINER_IMPL_H_
#define __CBL_ARRAYCONTAINER_IMPL_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Reflection/EntityManager.h"
#include "cbl/Reflection/FieldContainer.h"
#include "cbl/Debug/Assert.h"

namespace cbl
{
	namespace detail
	{
		template< typename TYPE, int LENGTH >
		class ArrayReadIterator_Impl :
			public FieldReadIterator
		{
		public:
			inline ArrayReadIterator_Impl( const TYPE* container )
				: mContainer(container), mPosition(0) {}

			virtual const void* GetKey( void ) const {
				return NULL;
			}

			virtual const void* GetValue( void ) const {
				CBL_ASSERT_TRUE( mPosition < LENGTH );
				return mContainer + mPosition;
			}

			virtual bool IncNext( void ) const {
				if( mPosition >= LENGTH ) return false;
				++mPosition;
				return true;
			}

			virtual bool IsValid( void ) const {
				return mPosition < LENGTH;
			}

			virtual Uint32 Count( void ) const {
				return LENGTH;
			}

		private:
			const TYPE*		mContainer;
			mutable Uint32	mPosition;
		};

		template< typename TYPE, int LENGTH >
		class ArrayWriteIterator_Impl :
			public FieldWriteIterator
		{
		public:
			inline ArrayWriteIterator_Impl( TYPE* container )
				: mContainer( container ), mPosition(0) {}

			virtual bool Add( void* obj ) {
				if( mPosition >= LENGTH ) return false;

				mContainer[mPosition++] = *(TYPE*)obj;
				return true;
			}

			virtual bool Add( void*, void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

			virtual void* AddEmpty( void ) {
				if( mPosition >= LENGTH ) return NULL;

				mContainer[mPosition] = TYPE();
				return &mContainer[mPosition++];
			}

			virtual void* AddEmpty( void* ) {
				CBL_FAIL( "Implementation not supported." );
				return false;
			}

		private:
			TYPE*	mContainer;
			Uint32	mPosition;
		};

		//! POD array container creation specialization.
		template <typename TYPE, int LENGTH>
		FieldContainer* CreateContainer( TYPE (&)[LENGTH] )
		{
			FieldContainer* cont = new FieldContainer_Impl<
				TYPE,
				ArrayReadIterator_Impl<TYPE, LENGTH>,
				ArrayWriteIterator_Impl<TYPE, LENGTH> >();

			cont->ValueType			= &CBL_ENT.Types.Create<TYPE>();
			cont->IsValuePointer	= IsPtr<TYPE>::Value;

			return cont;
		}
	}
}

#endif // __CBL_ARRAYCONTAINER_IMPL_H_
