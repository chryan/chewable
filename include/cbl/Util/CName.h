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
 * @file Name.h
 * @brief Constant hashed name. Intended for use with constant compile-time strings.
 */

#ifndef __CBL_CNAME_H_
#define __CBL_CNAME_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Hash.h"

namespace cbl
{
	//! Basic constant name hash.
	struct CBL_API CName
	{
		/***** Public Members *****/
		const Char*	Text;	//!< Name text.
		HashValue	Hash;	//!< Name hash.

		/***** Public Methods *****/
		//! Default constructor.
		inline CName() : Text( NULL ), Hash(0) {}
		//! Constructor. Create constant name from constant string.
		//! @param	txt		Constant string.
		CName( const Char* txt );
		//! Constructor. Create constant name from constant string.
		//! @param	txt		Constant string.
		explicit CName( const cbl::Hash& hash );
		//! Constructor.
		//! @param	txt		Name constant string text.
		//! @param	hash	Name hash.
		CName( const Char* txt, HashValue hash );
		//! Hash value constructor.
		//! WARNING: This only sets the hash value and it's to be used for name comparisons only.
		explicit CName( HashValue hash );
		//! Assignment operator.
		CName& operator = ( const Char* txt );
		//! Assignment operator.
		CName& operator = ( const cbl::Hash& hash );
		//! Equality operator.
		bool operator == ( const CName& rhs ) const;
		//! Equality operator.
		bool operator < ( const CName& rhs ) const;
		//! Conversion operator.
		operator cbl::Hash ( void ) const;
	};

	//! Outputs hash value and name to stream operator.
	inline Ostream & operator << ( Ostream& stream, const CName& name ) {
		return (stream << name.Text);
	}
}

//! Specialise Name std::hash comparison.
template<>
struct std::hash<cbl::CName> {
	inline std::size_t operator() ( const cbl::CName& name ) const { return name.Hash; }
};

#include "CName.inl"

#endif // __CBL_CNAME_H_
