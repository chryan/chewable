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
 * @file test_Reflection.cpp
 * @brief Unit testing for reflection utilities.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

// Chewable Headers //
#include <cbl/Chewable.h>
#include <cbl/Reflection/Typing.h>

// Google Test //
#include <gtest/gtest.h>

using namespace cbl;

namespace cbl
{
	struct DummyAccess {};
	template<>
	DummyAccess* EntityManager::New<DummyAccess>( void ) const
	{
		this->EntityManager::~EntityManager();
		this->EntityManager::EntityManager();
		CblRegistrar::RegisterCblTypes();
		return NULL;
	}
}
void ForceReconstructEntityManager( void )
{
	EntityManager* em = const_cast<EntityManager*>( EntityManager::InstancePtr() );
	em->New<DummyAccess>();
}

TEST( ReflectionFixture, CommonTest )
{
	const Char* splitStr = "/123/345/555/5//";

	std::vector<String> strs = Serialiser::SplitStreamPath( splitStr );
	ASSERT_EQ( strs.size(), 4 );
	ASSERT_STREQ( strs[0].c_str(), "123" );
	ASSERT_STREQ( strs[1].c_str(), "345" );
	ASSERT_STREQ( strs[2].c_str(), "555" );
	ASSERT_STREQ( strs[3].c_str(), "5" );
}

struct ReflectTest :
	public Entity
{
	int x;
	int y;

	virtual Entity::OPTIONS OnPreChanged( void ) { return Entity::O_NORMAL; }
	virtual void OnChanged( void ) {}
	virtual Entity::OPTIONS OnPreSaved( void ) const { return Entity::O_NORMAL; }
	virtual void OnSaved( void ) const {}
};

CBL_TYPE( ReflectTest, ReflectTest );

class TestType {};

namespace _tt {
	class TestType {};
	namespace _tt {
		struct TestType{};
	}
}

class InheritedType :
	public TestType
{
};

CBL_TYPE( TestType, TestType );
CBL_TYPE( InheritedType, InheritedType);
CBL_TYPE( _tt::TestType, _ttTestType );
CBL_TYPE( _tt::_tt::TestType, _tt_ttTestType );

TEST( ReflectionFixture, TypeNameTest )
{
	ASSERT_STREQ( TypeCName<TestType>().Text, "TestType" );
	ASSERT_STREQ( TypeCName<_tt::TestType>().Text, "_ttTestType" );
	ASSERT_STREQ( TypeCName<_tt::_tt::TestType>().Text, "_tt_ttTestType" );

}

TEST( ReflectionFixture, TypeBaseTest )
{
	CBL_ENT.Types.Create<TestType>();
	CBL_ENT.Types.Create<InheritedType>()
		.Base<TestType>();
	CBL_ENT.Types.Create<_tt::TestType>();

	ASSERT_TRUE( CBL_ENT.Types.Get<TestType>() != NULL );
	ASSERT_TRUE( CBL_ENT.Types.Get<InheritedType>() != NULL );
	ASSERT_TRUE( CBL_ENT.Types.Get<_tt::TestType>() != NULL );
	ASSERT_TRUE( CBL_ENT.Types.Get<InheritedType>()->IsType<TestType>() );
	ASSERT_FALSE( CBL_ENT.Types.Get<InheritedType>()->IsType<_tt::TestType>() );

	ForceReconstructEntityManager();
}

TEST( ReflectionFixture, EntityInheritanceTest )
{
	const Type* entType = CBL_ENT.Types.Get<Object>();
	ASSERT_TRUE( (entType != NULL) && entType->IsEntity );
	const Type* nonEnt = CBL_ENT.Types.Get<Int8>();
	ASSERT_TRUE( (nonEnt != NULL) && !nonEnt->IsEntity );

	Int8* newInt = CBL_ENT.New<Int8>();
	*newInt = 10;

	ASSERT_EQ( *newInt, 10 );
	CBL_DELETE( newInt );
}

TEST( ReflectionFixture, StringifyTest )
{
	// Test Int8 values.
	{
		Int8 value = 10;

		const Type* type = CBL_ENT.Types.Get<Int8>();
		String testStringify;
		type->ToString( testStringify, type, &value, NULL );
		ASSERT_EQ( testStringify, "10" );
		testStringify = "50";
		type->FromString( testStringify.c_str(), type, &value, NULL );
		ASSERT_EQ( value, 50 );
	}

	// Test bool values.
	{
		bool value = false;

		const Type* type = CBL_ENT.Types.Get<bool>();
		String testStringify;
		type->ToString( testStringify, type, &value, NULL );
		ASSERT_EQ( testStringify, "false" );
		value = true;
		type->ToString( testStringify, type, &value, NULL );
		ASSERT_EQ( testStringify, "true" );

		type->FromString( "FaLsE", type, &value, NULL );
		ASSERT_FALSE( value );
		type->FromString( "TruE", type, &value, NULL );
		ASSERT_TRUE( value );
		type->FromString( "0", type, &value, NULL );
		ASSERT_FALSE( value );
		type->FromString( "1", type, &value, NULL );
		ASSERT_TRUE( value );
	}
}

TEST( ReflectionFixture, EntityCreateDelete )
{
	CBL_ENT.Types.Create<ReflectTest>()
		.CBL_FIELD( x, ReflectTest );

	ReflectTest* tpl_rt = CBL_ENT.New<ReflectTest>();
	ReflectTest* nam_rt = (ReflectTest*)CBL_ENT.New( "ReflectTest" );

	ASSERT_TRUE( tpl_rt != NULL );
	ASSERT_TRUE( nam_rt != NULL );

	CBL_ENT.Delete( tpl_rt );
	CBL_ENT.Delete( nam_rt );

	nam_rt = (ReflectTest*)CBL_ENT.New( cbl::TypeCName<ReflectTest>() );
	ASSERT_TRUE( nam_rt != NULL );

	nam_rt->x = 5;
	nam_rt->y = 10;

	ASSERT_EQ( nam_rt->x, 5 );
	ASSERT_EQ( nam_rt->y, 10 );

	CBL_ENT.Delete( nam_rt );

	ForceReconstructEntityManager();
}

TEST( ReflectionFixture, FieldTest )
{
	Vector3f vec( 1.0f, 2.0f, 3.0f );

	const Type* type = CBL_ENT.Types.Get<Vector3f>();

	const Field* x = type->GetField( "X" );
	const Field* y = type->GetField( "Y" );
	const Field* z = type->GetField( "Z" );

	ASSERT_TRUE( x && y && z );
	ASSERT_FALSE( type->GetField( "Bad" ) );

	ASSERT_NEAR( *(cbl::Float32*)(x->GetPtr(&vec)), 1.0f, 0.0001f );
	ASSERT_NEAR( *(cbl::Float32*)(y->GetPtr(&vec)), 2.0f, 0.0001f );
	ASSERT_NEAR( *(cbl::Float32*)(z->GetPtr(&vec)), 3.0f, 0.0001f );
}

namespace TestEnum
{
	enum Options {
		First	= 0x01,
		Second	= 0x02,
		Third	= 0x04,
		Fourth	= 0x08,
	};
}

CBL_TYPE( TestEnum::Options, TestEnum );

TEST( ReflectionFixture, EnumTest )
{
	CBL_ENT.Types.Create<TestEnum::Options>()
		.CBL_ENUM( First, TestEnum )
		.CBL_ENUM( Second, TestEnum )
		.CBL_ENUM( Third, TestEnum )
		.CBL_ENUM( Fourth, TestEnum );

	TestEnum::Options value = TestEnum::First;

	const Type* type = CBL_ENT.Types.Get<TestEnum::Options>();
	String testStringify;
	type->ToString( testStringify, type, &value, NULL );
	ASSERT_EQ( testStringify, "First" );
	value = TestEnum::Second;
	type->ToString( testStringify, type, &value, NULL );
	ASSERT_EQ( testStringify, "Second" );

	type->FromString( "Third", type, &value, NULL );
	ASSERT_EQ( value, TestEnum::Third );
	type->FromString( "Fourth", type, &value, NULL );
	ASSERT_EQ( value, TestEnum::Fourth );

	ForceReconstructEntityManager();
}

const int ContainerSize = 15;

struct ContainerTest
{
	Int32									Array[ContainerSize];
	std::vector<Int32>						Vector;
	std::set<Int32>							Set;
	std::unordered_set<Int32>				USet;
	std::map<Int32,std::string>				Map;
	std::unordered_map<Int32,std::string>	UMap;
	std::deque<Int32>						Deque;

	Int32 UnorderedTest;

	ContainerTest() : UnorderedTest(0) {
		for( int i = 0; i < ContainerSize; ++i ) {
			Array[i] = i;
			Vector.push_back( i );
			Set.insert(i);
			USet.insert(i);
			Deque.push_back(i);

			std::stringstream num;
			num << i;
			Map.insert( std::make_pair( i, num.str() ) );
			UMap.insert( std::make_pair( i, num.str() ) );

			UnorderedTest += i;
		}
	}
};
CBL_TYPE( ContainerTest, ContainerTest );

class ReflectionFieldContainerTestFixture :
	public ::testing::Test
{
protected:
	void SetUp()
	{
		CBL_ENT.Types.Create<ContainerTest>()
			.CBL_FIELD( Array, ContainerTest )
			.CBL_FIELD( Vector, ContainerTest )
			.CBL_FIELD( Set, ContainerTest )
			.CBL_FIELD( USet, ContainerTest )
			.CBL_FIELD( Map, ContainerTest )
			.CBL_FIELD( UMap, ContainerTest )
			.CBL_FIELD( Deque, ContainerTest );

		ContType = CBL_ENT.Types.Get<ContainerTest>();

		ASSERT_TRUE( ContType != NULL );
		ASSERT_EQ( ContType->GetFields().size(), 7 );
	}

	void TearDown()
	{
		ForceReconstructEntityManager();
	}

public:
	const Type* ContType;
};

TEST_F( ReflectionFieldContainerTestFixture, ArrayContainerTest )
{
	const Field* field = ContType->GetField( "Array" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_TRUE( field->Container->KeyType == NULL );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<Int32>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.Array ) {
		ASSERT_EQ( *it->GetValue<Int32>(), t++ );
	} CBL_FOREACH_FIELD_END( field->Container, it );
}

TEST_F( ReflectionFieldContainerTestFixture, VectorContainerTest )
{
	const Field* field = ContType->GetField( "Vector" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_TRUE( field->Container->KeyType == NULL );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<Int32>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.Vector ) {
		ASSERT_EQ( *it->GetValue<Int32>(), t++ );
	} CBL_FOREACH_FIELD_END(field->Container, it);

	cbl::FieldWriteIterator* writeIter = CBL_NEW_FIELD_WRITEIT(field->Container, &cont.Vector);

	ASSERT_TRUE(cont.Vector.back() != t);
	writeIter->Add(t);
	ASSERT_TRUE(cont.Vector.back() == t);
	ASSERT_TRUE(cont.Vector.back() != 0);
	writeIter->AddEmpty();
	ASSERT_TRUE(cont.Vector.back() == 0);
}

TEST_F( ReflectionFieldContainerTestFixture, SetContainerTest )
{
	const Field* field = ContType->GetField( "Set" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_TRUE( field->Container->KeyType == NULL );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<Int32>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.Set ) {
		ASSERT_EQ( *it->GetValue<Int32>(), t++ );
	} CBL_FOREACH_FIELD_END(field->Container, it);

	cbl::FieldWriteIterator* writeIter = CBL_NEW_FIELD_WRITEIT(field->Container, &cont.Set);
	ASSERT_TRUE(cont.Set.find(t) == cont.Set.end());
	writeIter->Add(t);
	ASSERT_TRUE(cont.Set.find(t) != cont.Set.end());

	cont.Set.erase(0);
	ASSERT_TRUE(cont.Set.find(0) == cont.Set.end());
	writeIter->AddEmpty();
	ASSERT_TRUE(cont.Set.find(0) != cont.Set.end());
}

TEST_F( ReflectionFieldContainerTestFixture, USetContainerTest )
{
	const Field* field = ContType->GetField( "USet" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_TRUE( field->Container->KeyType == NULL );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<Int32>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.USet ) {
		t += *it->GetValue<Int32>();
	} CBL_FOREACH_FIELD_END( field->Container, it );

	ASSERT_EQ( t, cont.UnorderedTest );

	cbl::FieldWriteIterator* writeIter = CBL_NEW_FIELD_WRITEIT(field->Container, &cont.USet);
	ASSERT_TRUE(cont.USet.find(t) == cont.USet.end());
	writeIter->Add(t);
	ASSERT_TRUE(cont.USet.find(t) != cont.USet.end());

	cont.USet.erase(0);
	ASSERT_TRUE(cont.USet.find(0) == cont.USet.end());
	writeIter->AddEmpty();
	ASSERT_TRUE(cont.USet.find(0) != cont.USet.end());
}

TEST_F( ReflectionFieldContainerTestFixture, MapContainerTest )
{
	const Field* field = ContType->GetField( "Map" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_EQ( field->Container->KeyType->Name, cbl::TypeName<Int32>() );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<std::string>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.Map ) {
		std::stringstream num;
		num << t;
		ASSERT_EQ( *it->GetValue<String>(), num.str() );
		ASSERT_EQ( *it->GetKey<Int32>(), t++ );
	} CBL_FOREACH_FIELD_END( field->Container, it );

	cbl::FieldWriteIterator* writeIter = CBL_NEW_FIELD_WRITEIT(field->Container, &cont.Map);

	ASSERT_TRUE(cont.Map.find(t) == cont.Map.end());
	writeIter->Add(t, std::string("tryAdd"));
	ASSERT_TRUE(cont.Map.find(t) != cont.Map.end());
	ASSERT_EQ(cont.Map.find(t)->second, "tryAdd");

	int key = 0;
	cont.Map.erase(0);
	ASSERT_TRUE(cont.Map.find(0) == cont.Map.end());
	writeIter->AddEmpty(&key);
	ASSERT_TRUE(cont.Map.find(0) != cont.Map.end());
	ASSERT_EQ(cont.Map.find(0)->second, std::string());
}

TEST_F( ReflectionFieldContainerTestFixture, UMapContainerTest )
{
	const Field* field = ContType->GetField( "UMap" );
	ASSERT_TRUE( field != NULL );
	ASSERT_TRUE( field->Container != NULL );
	ASSERT_EQ( field->Container->KeyType->Name, cbl::TypeName<Int32>() );
	ASSERT_EQ( field->Container->ValueType->Name, cbl::TypeName<std::string>() );

	ContainerTest cont;

	Int32 t = 0;
	CBL_FOREACH_READ_FIELD_BEGIN( field->Container, it, &cont.UMap ) {
		t += *it->GetKey<Int32>();
	} CBL_FOREACH_FIELD_END( field->Container, it );

	ASSERT_EQ(t, cont.UnorderedTest);

	cbl::FieldWriteIterator* writeIter = CBL_NEW_FIELD_WRITEIT(field->Container, &cont.UMap);

	ASSERT_TRUE(cont.UMap.find(t) == cont.UMap.end());
	writeIter->Add(t, std::string("tryAdd"));
	ASSERT_TRUE(cont.UMap.find(t) != cont.UMap.end());
	ASSERT_EQ(cont.UMap.find(t)->second, "tryAdd");

	cont.UMap.erase(0);
	ASSERT_TRUE(cont.UMap.find(0) == cont.UMap.end());
	writeIter->AddEmpty<int>(0);
	ASSERT_TRUE(cont.UMap.find(0) != cont.UMap.end());
	ASSERT_EQ(cont.UMap.find(0)->second, std::string());
}
