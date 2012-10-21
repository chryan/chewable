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
 * @file TypeDB.inl
 * @brief Type information database.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

namespace cbl
{
	template< typename TYPE >
	inline void TypeDB::ConstructEntity( void* ent ) {
		new (ent) TYPE;
	}

	template< typename TYPE >
	inline void TypeDB::DestructEntity( void* ent ) {
		((TYPE*)ent)->TYPE::~TYPE();
	}

	template< typename TYPE >
	inline Type& TypeDB::Create()
	{
		const CName& name = TypeCName<TYPE>();
		TypeMap::iterator findit = mTypes.find( name );
		return findit == mTypes.end() ? *(CreateImpl<TYPE>()) : *(findit->second);
	}

	template< typename TYPE >
	inline const Type* TypeDB::Get( void ) const
	{
		const Type* type = Get( TypeCName<TYPE>() );
		return type ? type : const_cast<TypeDB*>( this )->CreateImpl<TYPE>();
	}

	inline const Type* TypeDB::Get( const CName& name ) const
	{
		TypeMap::const_iterator findit = mTypes.find( name );
		return findit != mTypes.end() ? findit->second : NULL;
	}

	template< typename TYPE >
	inline Type* TypeDB::CreateImpl( void )
	{
		Type* type = new Type( TypeCName<TYPE>(), sizeof(TYPE), ConstructEntity<TYPE>, DestructEntity<TYPE>, this, IsConvertible<TYPE,Entity>::Value );
		mTypes.insert( std::make_pair( TypeCName<TYPE>(), type ) );
		return type;
	}
}
