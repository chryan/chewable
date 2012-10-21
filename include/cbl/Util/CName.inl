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
 * @file Name.inl
 * @brief Constant hashed string object.
 */

namespace cbl
{
	/***** Name methods *****/
	inline CName::CName( const Char* txt )
		: Text( txt ), Hash( txt ? cbl::Hash::Generate( txt ) : 0 ) {}

	inline CName::CName( const cbl::Hash& hash )
		: Text( hash.GetText().c_str() ), Hash( hash.GetHash() ) {}

	inline CName::CName( const Char* txt, HashValue hash )
		: Text( txt ), Hash( hash ) {}

	inline CName::CName( HashValue hash )
		: Text( NULL ), Hash( hash ) {}

	inline CName& CName::operator = ( const Char* txt )
	{
		Text = txt;
		Hash = cbl::Hash::Generate( Text );
		return *this;
	}

	inline CName& CName::operator = ( const cbl::Hash& hash )
	{
		Text = hash.GetText().c_str();
		Hash = hash.GetHash();
		return *this;
	}

	inline bool CName::operator == ( const CName& rhs ) const
	{
		return Hash == rhs.Hash;
	}

	inline bool CName::operator < ( const CName& rhs ) const
	{
		return Hash < rhs.Hash;
	}

	inline CName::operator cbl::Hash ( void ) const
	{
		return cbl::Hash( Text );
	}
}
