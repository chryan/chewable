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
 * @file Hash.h
 * @brief Hashed string object.
 */

#ifndef __CBL_HASH_H_
#define __CBL_HASH_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/Property.h"

namespace cbl
{
	/***** Types *****/
	typedef Uint32			HashValue;

	//! @brief String hashing utility class.
	//! 
	//! The object hashes a string into an integer value and stores both the string
	//! and the hash value. Hash objects are compared using their hash values for
	//! fast hash comparisons.
	class CBL_API Hash
	{
	/***** Properties *****/
	public:
		GETTER_AUTO_CREF(	String,		Text );		//!< Gets the hash text.
		GETTER_AUTO(		HashValue,	Hash );		//!< Gets the hash value.

	/***** Static Public Methods *****/
	public:
		static HashValue Generate( const Char* string );
		static HashValue Generate( const Char* string, Int32 length );
		static HashValue Generate( const String& string );

		//! Used for serialisation.
		static void ToString( String& str, const Type*, const void* obj, const FieldAttr* attr );
		//! Used for deserialisation.
		static void FromString( const String& str, const Type*, void* obj, const FieldAttr* attr );

	/***** Public Methods *****/
	public:
		//! Default constructor.
		Hash();
		//! Destructor.
		~Hash();
		//! Constructor.
		//! @param  name	Name to be hashed.
		Hash( const Char * name );
		//! Constructor.
		//! @param  name	Name to be hashed.
		Hash( const String& name );
		//! Assignment operator for strings.
		Hash & operator = ( const Char* name );
		//! Assignment operator for strings.
		Hash & operator = ( const String& name );
		//! Equality operator.
		bool operator == ( const Hash & rhs ) const;
		//! Equality operator.
		bool operator == ( const HashValue & rhs ) const;
		//! Inequality operator.
		bool operator != ( const Hash & rhs ) const;
		//! Less than operator.
		bool operator < ( const Hash & rhs ) const;
		//! More than operator.
		bool operator > ( const Hash & rhs ) const;

	/***** Private Members *****/
	private:
		String				mText;			//!< Hash name.
		HashValue			mHash;			//!< Hash value.
		friend class		Type;
		friend class		EntityManager;
	};

	//! Outputs hash value and name to stream operator.
	inline Ostream & operator << ( Ostream & stream, const Hash & hash ) {
		return stream << hash.GetHash();
	}
}

#include "cbl/Reflection/Typing.h"
CBL_TYPE( cbl::Hash, Hash );

template<>
struct std::hash<cbl::Hash> {
	inline std::size_t operator() ( const cbl::Hash& hash ) const { return hash.GetHash(); }
};

#include "Hash.inl"

#endif // __CBL_HASH_H_
