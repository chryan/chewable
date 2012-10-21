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
 * @file CblRegistrar.cpp
 * @brief Chewable type registrar.
 */

// Precompiled Headers //
#include "cbl/StdAfx.h"

using namespace cbl;

CblRegistrar CblRegistrar::_sInstance = CblRegistrar();

void CblRegistrar::RegisterCblTypes( void )
{
	TypeDB& typedb = CBL_ENT.Types;

	// Create all basic Chewable types.
	typedb.Create<ObjectPart>();
	typedb.Create<Object>()
		.CBL_FIELDM( Name, Object )
		.CBL_FIELDM( Parts, Object );
	typedb.Create<GameState>();

	/***** Vector2 *****/
	typedb.Create<Vector2i>()
		.CBL_FIELD( X, Vector2i )
		.CBL_FIELD( Y, Vector2i );
	typedb.Create<Vector2f>()
		.CBL_FIELD( X, Vector2f )
		.CBL_FIELD( Y, Vector2f );
	typedb.Create<Vector2d>()
		.CBL_FIELD( X, Vector2d )
		.CBL_FIELD( Y, Vector2d );

	/***** Vector3 *****/
	typedb.Create<Vector3f>()
		.CBL_FIELD( X, Vector3f )
		.CBL_FIELD( Y, Vector3f )
		.CBL_FIELD( Z, Vector3f );
	typedb.Create<Vector3d>()
		.CBL_FIELD( X, Vector3d )
		.CBL_FIELD( Y, Vector3d )
		.CBL_FIELD( Z, Vector3d );

	/***** Vector4 *****/
	typedb.Create<Vector4f>()
		.CBL_FIELD( X, Vector4f )
		.CBL_FIELD( Y, Vector4f )
		.CBL_FIELD( Z, Vector4f )
		.CBL_FIELD( W, Vector4f );
	typedb.Create<Vector4d>()
		.CBL_FIELD( X, Vector4d )
		.CBL_FIELD( Y, Vector4d )
		.CBL_FIELD( Z, Vector4d )
		.CBL_FIELD( W, Vector4d );
	
	/***** Colour *****/
	typedb.Create<Colour>()
		.CBL_FIELD( R, Colour )
		.CBL_FIELD( G, Colour )
		.CBL_FIELD( B, Colour )
		.CBL_FIELD( A, Colour );

	/***** Matrix3 *****/
	typedb.Create<Matrix3>()
		.CBL_FIELD( _pM, Matrix3 );

	/***** Matrix4 *****/
	typedb.Create<Matrix4>()
		.CBL_FIELD( _pM, Matrix4 );

	/***** Hash *****/
	typedb.Create<Hash>()
		.DefineSerialisers( &Hash::ToString, &Hash::FromString );

	/***** FileInfo *****/
	typedb.Create<FileInfo>()
		.CBL_FIELDM( Path, FileInfo )
		.CBL_FIELDM( File, FileInfo )
		.DefineSerialisers( &FileInfo::ToString, &FileInfo::FromString );
}

CblRegistrar::CblRegistrar()
{
	// Automatically register cbl types.
	RegisterCblTypes();
}
