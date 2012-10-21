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
 * @file Hash.inl
 * @brief Hashed string object.
 */

namespace cbl
{
	inline Hash::Hash()
	: mHash(0)
	{
	}

	inline Hash::Hash( const Char* name )
	: mText( name ? name : "" )
	, mHash( name ? Generate( name ) : 0 )
	{
	}

	inline Hash::Hash( const String& name )
	: mText( name )
	, mHash( Generate( name.c_str(), name.length() ) )
	{
	}

	inline bool Hash::operator != ( const Hash & rhs ) const {
		return ( mHash != rhs.GetHash() );
	}

	inline bool Hash::operator == ( const Hash & rhs ) const {
		return ( mHash == rhs.GetHash() );
	}

	inline bool Hash::operator == ( const HashValue & rhs ) const {
		return ( mHash == rhs );
	}

	inline bool Hash::operator < ( const Hash & rhs ) const {
		return ( mHash < rhs.GetHash() );
	}

	inline bool Hash::operator > ( const Hash & rhs ) const {
		return ( mHash > rhs.GetHash() );
	}
	
	inline HashValue Hash::Generate( const Char* string ) {
		return Generate( string, strlen( string ) );
	}

	inline HashValue Hash::Generate( const String& string ) {
		return Generate( string.c_str(), Int32( string.length() ) );
	}
}