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
 * @file GameComponentCollection.inl
 * @brief Inline methods for GameComponentCollection.
 */

namespace cbl
{
	/***** Inline Methods *****/
	inline const size_t GameComponentCollection::size( void ) const
	{
		return mComponentList.size();
	}

	inline GameComponentCollection::const_reverse_iterator GameComponentCollection::rbegin( void ) const
	{
		return mComponentList.rbegin();
	}

	inline GameComponentCollection::const_iterator GameComponentCollection::begin( void ) const
	{
		return mComponentList.begin();
	}

	inline GameComponentCollection::reverse_iterator GameComponentCollection::rbegin( void )
	{
		return mComponentList.rbegin();
	}

	inline GameComponentCollection::iterator GameComponentCollection::begin( void )
	{
		return mComponentList.begin();
	}
	
	inline GameComponentCollection::const_reverse_iterator GameComponentCollection::rend( void ) const
	{
		return mComponentList.rend();
	}
	
	inline GameComponentCollection::const_iterator GameComponentCollection::end( void ) const
	{
		return mComponentList.end();
	}
	
	inline GameComponentCollection::reverse_iterator GameComponentCollection::rend( void )
	{
		return mComponentList.rend();
	}
	
	inline GameComponentCollection::iterator GameComponentCollection::end( void )
	{
		return mComponentList.end();
	}
}
