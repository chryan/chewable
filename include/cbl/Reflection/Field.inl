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
 * @file Field.inl
 * @brief Type field information.
 * @see https://bitbucket.org/dwilliamson/reflectabit
 */

#include "Detail/ArrayContainer_Impl.h"
#include "Detail/VectorContainer_Impl.h"
#include "Detail/SetContainer_Impl.h"
#include "Detail/MapContainer_Impl.h"

namespace cbl
{
	template< typename ENTITY_TYPE, typename FIELD_TYPE >
	inline Field::Field( const CName& name, const cbl::Type* type, FIELD_TYPE ENTITY_TYPE::*field, FieldAttr attrs, const Char* group, const Char* desc )
	: Type( type ), IsPointer( IsPtr<FIELD_TYPE>::Value ), Offset( offsetof( ENTITY_TYPE, *field ) ), Name( name ), Attributes( attrs )
	, Group( group ), Desc( desc )
	{
		Container = SharedPtr<FieldContainer>( detail::CreateContainer( ((ENTITY_TYPE*)0)->*field ) );
	}
}
