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
 * @file VectorSet.inl
 * @brief Fast map implementation.
 */

namespace cbl
{
	template<typename Key, typename Compare>
	inline VectorSet<Key,Compare>::VectorSet(cbl::Uint32 size,bool autoSort)
	: auto_sort(autoSort)
	, mSorted(true)
	{
		mSet.reserve(size);
	}

	template<typename Key, typename Compare>
	inline VectorSet<Key,Compare>::~VectorSet() {
		mSet.clear();
	}

	template<typename Key, typename Compare>
	inline void VectorSet<Key,Compare>::resort( void ) {
		if( mSorted ) return;
		std::sort( mSet.begin(), mSet.end(), Compare() );
		mSorted = true;
	}

	template<typename Key, typename Compare>
	inline bool VectorSet<Key,Compare>::insert( const Key& _key ) {
		if( this->find( _key ) != mSet.end() ) return false;
		mSet.push_back( _key );
		if( auto_sort ) std::sort( mSet.begin(), mSet.end(), Compare() );
		else mSorted = false;
		return true;
	}

	template<typename Key, typename Compare>
	bool VectorSet<Key,Compare>::erase( const Key& _key ) {
		if( mSet.empty() ) return false;
		typename iterator findit = this->find( _key );
		if( findit != mSet.end() ) {
			std::swap( *findit, mSet[mSet.size()-1] );
			mSet.pop_back();
			if( auto_sort ) std::sort( mSet.begin(), mSet.end(), Compare() );
			else mSorted = false;
			return true;
		}

		return false;
	}

	template<typename Key, typename Compare>
	inline void VectorSet<Key,Compare>::erase( const iterator& del ) {
		if( mSet.empty() ) return;

		if( del != mSet.end() ) {
			*del = mSet[mSet.size()-1];
			mSet.pop_back();
			if( auto_sort ) std::sort( mSet.begin(), mSet.end(), Compare() );
			else mSorted = false;
		}
	}

	template<typename Key, typename Compare>
	inline const size_t VectorSet<Key,Compare>::size( void ) const {
		return mSet.size();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::iterator VectorSet<Key,Compare>::begin( void ) {
		return mSet.begin();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::const_iterator VectorSet<Key,Compare>::begin( void ) const {
		return mSet.begin();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::iterator VectorSet<Key,Compare>::end( void ) {
		return mSet.end();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::const_iterator VectorSet<Key,Compare>::end( void ) const {
		return mSet.end();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::reverse_iterator VectorSet<Key,Compare>::rbegin( void ) {
		return mSet.rbegin();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::const_reverse_iterator VectorSet<Key,Compare>::rbegin( void ) const {
		return mSet.rbegin();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::reverse_iterator VectorSet<Key,Compare>::rend( void ) {
		return mSet.rend();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::const_reverse_iterator VectorSet<Key,Compare>::rend( void ) const {
		return mSet.rend();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::iterator VectorSet<Key,Compare>::find( const Key& _key ) {
		if( mSet.empty() ) return mSet.end();
		if( !mSorted ) {
			CBL_FOREACH( Set, it, mSet ) {
				if( !(*it < _key) && !(_key < *it) )
					return it;
			}
			return mSet.end();
		}

		typename iterator findit = std::lower_bound( mSet.begin(), mSet.end(), _key, Compare() );
		return( findit != mSet.end() && !Compare()( _key, *findit ) ) ? findit : mSet.end();
	}

	template<typename Key, typename Compare>
	inline typename VectorSet<Key,Compare>::const_iterator VectorSet<Key,Compare>::find( const Key& _key ) const {
		if( mSet.empty() ) return mSet.end();
		if( !mSorted ) {
			CBL_FOREACH_CONST( Set, it, mSet ) {
				if( !(*it < _key) && !(_key < *it) )
					return it;
			}
			return mSet.end();
		}

		typename const_iterator findit = std::lower_bound( mSet.begin(), mSet.end(), _key, Compare() );
		return( findit != mSet.end() && !Compare()( _key, *findit ) ) ? findit : mSet.end();
	}

	template<typename Key, typename Compare>
	inline Key& VectorSet<Key,Compare>::operator[] (size_t index) {
		return mSet[index];
	}

	template<typename Key, typename Compare>
	inline const Key& VectorSet<Key,Compare>::operator[] (size_t index) const {
		return mSet[index];
	}

	template<typename Key, typename Compare>
	inline void VectorSet<Key,Compare>::clear( void ) {
		mSet.clear();
	}
}
