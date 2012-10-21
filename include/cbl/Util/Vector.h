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
 * @file Vector.h
 * @brief std::vector replacement.
 */

#ifndef __CBL_VECTOR_H_
#define __CBL_VECTOR_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	template<typename T>
	class Vector
	{
	public:
		struct iterator {
		public:
			iterator( T* _d );
			T& operator * ( void );
			iterator& operator ++ ( void );
			iterator operator ++ ( int );
			iterator& operator -- ( void );
			iterator operator -- ( int );
		private:
			T* _data;
		};
	public:
		Vector();
		Vector( size_t n );
		Vector( const Vector& rhs );
		Vector& operator = ( const Vector& rhs );

		size_t size( void ) const;
		void resize( size_t size );
		T& back(void);
		const T& back(void) const;
		void reserve( size_t size );

	private:
		Uint32	mCapacity;
		Uint32	mSize;
		T*		mData;
	};
}

#include "Vector.inl"

#endif // __CBL_VECTOR_H_
