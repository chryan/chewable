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
 * @file Typing.h
 * @brief Reflection system. References Don Williamson's Reflectabit library.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#ifndef __CBL_TYPING_H_
#define __CBL_TYPING_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Util/CName.h"
#include "cbl/Util/Hash.h"
#include "cbl/Util/Noncopyable.h"

// External Libraries //
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <unordered_set>
#include <deque>

namespace cbl
{
	//! Template class to check if a type is a pointer.
	template< typename TYPE >
	struct IsPtr{ static const bool Value = false; };
	//! Template specialised class to check if a type is a pointer.
	template< typename TYPE >
	struct IsPtr<TYPE*> { static const bool Value = true; };
	//! Template class to get pointer's type.
	template< typename TYPE >
	struct StripPtr{ typedef TYPE Type; };
	//! Template specialised class to get pointer's type.
	template< typename TYPE >
	struct StripPtr<TYPE*> { typedef TYPE Type; };
	//! Check if a class is a derived from base.
	//! IsConvertible<Entity,Object>::Value == true
	template< typename DERIVED_TYPE, typename BASE_TYPE >
	struct IsConvertible
	{
	private:
		template< typename TYPE >
		static Char _BaseTest( TYPE* );

		template< typename TYPE >
		static Float64 _BaseTest( ... );

	public:
		static const bool Value = sizeof( _BaseTest< StripPtr<BASE_TYPE>::Type >(static_cast< StripPtr<DERIVED_TYPE>::Type* >(0))) == sizeof(Char);
	};

	namespace detail
	{
		//! Unique type name for basic types.
		//! Use CBL_TYPE to declare type name.
		template< typename TYPE >
		inline const Char* TypeName( const TYPE* ) {
		}
	}

	template< typename TYPE >
	inline const Char* TypeName( void ) {
		return detail::TypeName( (const TYPE*)0 );
	}

	//! Unique type hash generated from each type.
	template< typename TYPE >
	inline const HashValue TypeHash( void ) {
		static const HashValue _hash = Hash::Generate( TypeName< StripPtr<TYPE>::Type >() );
		return _hash;
	}

	/***** Forward declarations *****/
	struct CName;

	//! Get type name and hash.
	template< typename TYPE >
	inline const CName& TypeCName( void ) {
		static const CName _name = CName( TypeName< StripPtr<TYPE>::Type >(), TypeHash< StripPtr<TYPE>::Type >() );
		return _name;
	}

	//! Get type hash.
	template< typename TYPE >
	inline const Hash& TypeHashName( void ) {
		static const Hash _hash = Hash( TypeName< StripPtr<TYPE>::Type >() );
		return _hash;
	}

	namespace detail
	{
		//! Generated type name for arrays.
		//! Basic type must be defined using CBL_TYPE.
		template< typename TYPE, int LENGTH >
		inline const Char* TypeName( const TYPE(*)[LENGTH] ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<TYPE>::Type*)0 ) ) + "Array";
			return _name.c_str();
		}

		//! Generated type name for std::vector.
		//! Basic type must be defined using CBL_TYPE.
		template< typename TYPE >
		inline const Char* TypeName( const std::vector<TYPE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<TYPE>::Type*)0 ) ) + "Vector";
			return _name.c_str();
		}

		//! Generated type name for std::set.
		//! Basic type must be defined using CBL_TYPE.
		template< typename TYPE >
		inline const Char* TypeName( const std::set<TYPE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<TYPE>::Type*)0 ) ) + "Set";
			return _name.c_str();
		}

		//! Generated type name for std::unordered_set.
		//! Basic type must be defined using CBL_TYPE.
		template< typename TYPE >
		inline const Char* TypeName( const std::unordered_set<TYPE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<TYPE>::Type*)0 ) ) + "USet";
			return _name.c_str();
		}

		//! Generated type name for std::map.
		//! Basic type must be defined using CBL_TYPE.
		template< typename KEY, typename VALUE >
		inline const Char* TypeName( const std::map<KEY,VALUE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<KEY>::Type*)0 ) ) + std::string( TypeName( (const StripPtr<VALUE>::Type*)0 ) ) + "Map";
			return _name.c_str();
		}

		//! Generated type name for std::unordered_map.
		//! Basic type must be defined using CBL_TYPE.
		template< typename KEY, typename VALUE >
		inline const Char* TypeName( const std::unordered_map<KEY,VALUE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<KEY>::Type*)0 ) ) + std::string( TypeName( (const StripPtr<VALUE>::Type*)0 ) ) + "UMap";
			return _name.c_str();
		}

		//! Generated type name for std::deque.
		//! Basic type must be defined using CBL_TYPE.
		template< typename TYPE >
		inline const Char* TypeName( const std::deque<TYPE>* ) {
			static const std::string _name = std::string( TypeName( (const StripPtr<TYPE>::Type*)0 ) ) + "Deque";
			return _name.c_str();
		}
	}
}

//! Declare new chewable type.
#define CBL_TYPE( type, name )\
	namespace cbl { namespace detail { \
		template<>\
		inline const Char* TypeName<type>( const type* ) { return #name; }\
	} }

#define CBL_TYPE_FRIEND\
	friend class cbl::Type;\
	friend class cbl::EntityManager

#define CBL_REFLECTABLE\
	friend class cbl::EntityManager;\
	friend class cbl::TypeDB;\
	friend class cbl::Type;

/***** Default Integral Types *****/
CBL_TYPE( cbl::Int8,	Int8 );
CBL_TYPE( cbl::Int16,	Int16 );
CBL_TYPE( cbl::Int32,	Int32 );
CBL_TYPE( cbl::Int64,	Int64 );
CBL_TYPE( cbl::Uint8,	Uint8 );
CBL_TYPE( cbl::Uint16,	Uint16 );
CBL_TYPE( cbl::Uint32,	Uint32 );
CBL_TYPE( cbl::Uint64,	Uint64 );
CBL_TYPE( cbl::Float32,	Float32 );
CBL_TYPE( cbl::Float64,	Float64 );
CBL_TYPE( cbl::Char,	Char );
CBL_TYPE( cbl::String,	String );
CBL_TYPE( bool,			Boolean );

#include "Field.h"
#include "Type.h"
#include "TypeDB.h"

#endif // __CBL_TYPING_H_
