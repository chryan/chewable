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
 * @file ObjectManager.inl
 * @brief Object factory template/inline methods.
 */

// Chewable Headers //
#include "cbl/Debug/Assert.h"
#include "cbl/Util/FileSystem.h"
#include "cbl/Reflection/Typing.h"

namespace cbl
{
	template< typename OBJECT_TYPE >
	inline OBJECT_TYPE* ObjectManager::Create( const CName& name, bool init )
	{
		// Force a compile-time type test.
		CBL_ENTITY_TYPETEST( Object, OBJECT_TYPE );
		return static_cast<OBJECT_TYPE*>( Create( TypeCName<OBJECT_TYPE>(), name, init ) );
	}

	template< typename DESERIALISER_TYPE >
	ObjectPtr ObjectManager::LoadObjectFromFile( const cbl::Char*, const cbl::Char*, bool ) {
		CBL_STATIC_ASSERT( false ); // Static assert by default.
	}

	template< typename SERIALISER_TYPE >
	inline void ObjectManager::SaveObjectToFile( const cbl::Char* file, const CName& name ) const {
		SaveObjectToFile( file, Get(name) );
	}

	template< typename SERIALISER_TYPE >
	inline void ObjectManager::SaveObjectToFile( const cbl::Char* file, ObjectID id ) const {
		SaveObjectToFile( file, Get(id) );
	}

	template< typename SERIALISER_TYPE >
	void ObjectManager::SaveObjectToFile( const cbl::Char* file, ObjectPtr obj ) const {
		CBL_STATIC_ASSERT( false ); // Static assert by default.
	}

	template< typename OBJECT_TYPE >
	inline OBJECT_TYPE* ObjectManager::Get( const CName& name ) const
	{
		// Force a compile-time type test.
		CBL_ENTITY_TYPETEST( Object, OBJECT_TYPE );
		ObjectNameTable::const_iterator findit = mObjectNameTable.find( name );
		return findit != mObjectNameTable.end() ? static_cast< OBJECT_TYPE* >( mObjectList[findit->second] ) : NULL;
	}

	template< typename OBJECT_TYPE >
	inline OBJECT_TYPE* ObjectManager::Get( ObjectID id ) const
	{
		// Force a compile-time type test.
		CBL_ENTITY_TYPETEST( Object, OBJECT_TYPE );
		return id < mObjectList.size() ? static_cast< OBJECT_TYPE* >( mObjectList[id] ) : NULL;
	}

	inline ObjectPtr ObjectManager::Get( const CName& name ) const
	{
		return Get<Object>( name );
	}

	inline ObjectPtr ObjectManager::Get( ObjectID id ) const
	{
		return Get<Object>( id );
	}

	inline void ObjectManager::Destroy( const CName& name )
	{
		ObjectNameTable::const_iterator findit = mObjectNameTable.find( name );
		if( findit == mObjectNameTable.end() ) {
			LOG_ERROR( "Object name doesn't exist: " << name );
			return;
		}
		Destroy( findit->second );
	}

	inline void ObjectManager::Destroy( const ObjectPtr obj )
	{
		Destroy( obj->GetID() );
	}

	inline bool ObjectManager::IsDestroying( const CName& name ) const
	{
		ObjectNameTable::const_iterator findit = mObjectNameTable.find( name );
		return findit != mObjectNameTable.end() ? IsDestroying( findit->second ) : false;
	}

	inline bool ObjectManager::IsDestroying( ObjectID id ) const
	{
		return std::find( mObjectsToDestroy.begin(), mObjectsToDestroy.end(), id ) != mObjectsToDestroy.end();
	}

	inline bool ObjectManager::IsDestroying( const ObjectPtr obj ) const
	{
		return IsDestroying( obj->GetID() );
	}

	inline bool ObjectManager::Rename( const ObjectPtr obj, const Hash& newName )
	{
		return Rename( obj->mName, newName );
	}

	template< typename OBJECT_TYPE >
	OBJECT_TYPE* ObjectManager::DeserialiseObject( Deserialiser& deserialiser, bool init )
	{
		CBL_ENTITY_TYPETEST( Object, OBJECT_TYPE );
		if( deserialiser.IsStreamEnded() ) {
			LOG_ERROR( "Stream is ended. Unable to deserialise new object" );
			return NULL;
		}

		OBJECT_TYPE* obj = CBL_ENT.New<OBJECT_TYPE>();
		
		if( !obj ) {
			LOG_ERROR( "Error creating new object." );
			return NULL;
		}

		if( !deserialiser.DeserialisePtr( obj ) || !Add( obj ) ) {
			CBL_ENT.Delete( obj );
			return NULL;
		} else if( init ) {
			InitObject( obj );
		}

		return obj;
	}
}