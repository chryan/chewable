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
 * @file test_BinarySerialisation.cpp
 * @brief Unit testing for binary serialisation.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Serialisation/BinarySerialiser.h>
#include <cbl/Serialisation/BinaryDeserialiser.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

namespace cbl
{
	struct DummyAccessBinary {};
	template<>
	DummyAccessBinary* EntityManager::New<DummyAccessBinary>( void ) const
	{
		this->EntityManager::~EntityManager();
		this->EntityManager::EntityManager();
		CblRegistrar::RegisterCblTypes();
		return NULL;
	}
}
void ForceReconstructEntityManager_BinaryS( void )
{
	EntityManager* em = const_cast<EntityManager*>( EntityManager::InstancePtr() );
	em->New<DummyAccessBinary>();
}

TEST( BinarySerialisationTest, BasicStructureTest )
{
	for( size_t i = 0; i < 5; ++i ) {
		std::ofstream ofile;
		ofile.open( "output.bin" );

		ASSERT_TRUE( ofile.is_open() );

		cbl::Vector3f out( 1.0f * (i*0.5f), 2.0f, 3.0f );
		BinarySerialiser b;
		b
			.SetStream( ofile )
			.Serialise( out );

		ofile.close();

		std::ifstream ifile;
		ifile.open( "output.bin" );

		ASSERT_TRUE( ifile.is_open() );

		cbl::Vector3f in;
		BinaryDeserialiser d;
		d.SetStream( ifile );
		ASSERT_FALSE( d.IsStreamEnded() );
		d.Deserialise( in );

		ASSERT_EQ( in.X, 1.0f * (i*0.5f) );
		ASSERT_EQ( in.Y, 2.0f );
		ASSERT_EQ( in.Z, 3.0f );

		ifile.close();

		ASSERT_TRUE( d.IsStreamEnded() );
	}
}

struct BinaryContainerTest
{
	Uint32						Value1;
	Uint32						Value2;
	Uint32						Value3;
	String						StringValue;
	std::map<Uint32,Float32>	Map;
	std::vector<Vector3f>		Vec;
};

CBL_TYPE( BinaryContainerTest, BinaryContainerTest );

TEST( BinarySerialisationTest, MapContainerTest )
{
	CBL_ENT.Types.Create<BinaryContainerTest>()
		.CBL_FIELD( Value1, BinaryContainerTest )
		.CBL_FIELD( Value2, BinaryContainerTest )
		.CBL_FIELD( Value3, BinaryContainerTest )
		.CBL_FIELD( StringValue, BinaryContainerTest )
		.CBL_FIELD( Map, BinaryContainerTest )
		.CBL_FIELD( Vec, BinaryContainerTest );

	BinaryContainerTest out;

	out.Value1 = 10;
	out.Value2 = 50;
	out.Value3 = 123807;
	out.StringValue = "Testing Stuff!";
	out.StringValue += '\0';
	out.StringValue += "Second Half";
	for( size_t i = 0; i < 5; ++i ) {
		out.Map.insert( std::make_pair( i, i*0.5f ) );
		out.Vec.push_back( cbl::Vector3f( 1.0f * (i*0.5f), 2.0f, 3.0f ) );
	}

	std::ofstream ofile;
	ofile.open( "container.bin", std::ios_base::binary );

	ASSERT_TRUE( ofile.is_open() );

	BinarySerialiser b;
	b
		.SetStream( ofile )
		.Serialise( out );

	ofile.close();

	std::ifstream ifile;
	ifile.open( "container.bin", std::ios_base::binary );

	ASSERT_TRUE( ifile.is_open() );

	BinaryContainerTest in;
	BinaryDeserialiser d;
	d.SetStream( ifile );

	ASSERT_FALSE( d.IsStreamEnded() );
	d.Deserialise( in );

	ASSERT_EQ( out.Vec.size(), in.Vec.size() );

	ASSERT_EQ( in.Value1, 10 );
	ASSERT_EQ( in.Value2, 50 );
	ASSERT_EQ( in.Value3, 123807 );
	ASSERT_EQ( in.StringValue, out.StringValue );
	for( size_t i = 0; i < in.Vec.size(); ++i ) {

		ASSERT_EQ( in.Map[Uint32(i)], (i*0.5f) );
		ASSERT_EQ( in.Vec[i].X, 1.0f * (i*0.5f) );
		ASSERT_EQ( in.Vec[i].Y, 2.0f );
		ASSERT_EQ( in.Vec[i].Z, 3.0f );
	}

	ifile.close();

	ASSERT_TRUE( d.IsStreamEnded() );

	ForceReconstructEntityManager_BinaryS();
}

struct BinaryEntityTest : public Entity
{
	virtual Entity::OPTIONS OnPreChanged( void ) { return Entity::O_NORMAL; }
	virtual void OnChanged( void ) {}
	virtual Entity::OPTIONS OnPreSaved( void ) const { return Entity::O_NORMAL; }
	virtual void OnSaved( void ) const {}
};

struct BinaryChild : public BinaryEntityTest
{
	Int32	X;
	Int32	Y;
	Int32	Array[5];
};

struct BinaryOtherChild : public BinaryEntityTest
{
	Float32	T;
	Float32	V;
	Float32	Array[5];
};

struct EntityContainer
{
	std::vector<BinaryEntityTest*>	Entities;

	~EntityContainer() {
		for( size_t i = 0; i < Entities.size(); ++i ) {
			CBL_DELETE( Entities[i] );
		}
	}
};

CBL_TYPE( BinaryEntityTest, BinaryEntityTest );
CBL_TYPE( BinaryChild, BinaryChild );
CBL_TYPE( BinaryOtherChild, BinaryOtherChild );
CBL_TYPE( EntityContainer, EntityContainer );

TEST( BinarySerialisationTest, EntityContainerTest )
{
	CBL_ENT.Types.Create<BinaryEntityTest>();
	
	CBL_ENT.Types.Create<BinaryChild>()
		.Base<BinaryEntityTest>()
		.CBL_FIELD( X, BinaryChild )
		.CBL_FIELD( Y, BinaryChild )
		.CBL_FIELD( Array, BinaryChild );

	CBL_ENT.Types.Create<BinaryOtherChild>()
		.Base<BinaryEntityTest>()
		.CBL_FIELD( T, BinaryOtherChild )
		.CBL_FIELD( V, BinaryOtherChild )
		.CBL_FIELD( Array, BinaryOtherChild );

	CBL_ENT.Types.Create<EntityContainer>()
		.CBL_FIELD( Entities, EntityContainer );

	EntityContainer out;
	for( size_t i = 0; i < 20; ++i ) {
		if( i % 2 ) {
			BinaryChild* child = CBL_ENT.New<BinaryChild>();
			child->X = 1 * i;
			child->Y = 2 * i;
			for( size_t t = 0; t < 5; ++t )
				child->Array[t] = t;
			out.Entities.push_back( child );
		} else {
			BinaryOtherChild* child = CBL_ENT.New<BinaryOtherChild>();
			child->T = (i * 0.5f);
			child->V = 2.0f * (i * 0.5f );
			for( size_t t = 0; t < 5; ++t )
				child->Array[t] = t * 2.0f;
			out.Entities.push_back( child );
		}
	}

	std::ofstream ofile;
	ofile.open( "entity_test.bin" );

	ASSERT_TRUE( ofile.is_open() );

	BinarySerialiser b;
	b
		.SetStream( ofile )
		.Serialise( out );

	ofile.close();

	std::ifstream ifile;
	ifile.open( "entity_test.bin" );

	ASSERT_TRUE( ifile.is_open() );

	EntityContainer in;
	BinaryDeserialiser d;
	d.SetStream( ifile );
	ASSERT_FALSE( d.IsStreamEnded() );
	d.Deserialise( in );

	ASSERT_EQ( out.Entities.size(), in.Entities.size() );
	for( size_t i = 0; i < 20; ++i ) {
		if( i % 2 ) {
			BinaryChild* child = (BinaryChild*)(out.Entities[i]);
			ASSERT_EQ( child->X, 1 * i );
			ASSERT_EQ( child->Y, 2 * i );
			for( size_t t = 0; t < 5; ++t )
				ASSERT_EQ( child->Array[t], t );
		} else {
			BinaryOtherChild* child = (BinaryOtherChild*)(out.Entities[i]);
			ASSERT_EQ( child->T, (i * 0.5f) );
			ASSERT_EQ( child->V, 2.0f * (i * 0.5f ) );
			for( size_t t = 0; t < 5; ++t )
				ASSERT_EQ( child->Array[t], t * 2.0f );
		}
	}

	ForceReconstructEntityManager_BinaryS();
}