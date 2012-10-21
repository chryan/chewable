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
 * @file Helpers.h
 * @brief Helper utilities.
 */

#ifndef __CBL_HELPER_H_
#define __CBL_HELPER_H_


#define CBL_FOREACH_IMPL( stl_container_type, iterator_type, iterator_name, container, beginFunc, endFunc )\
	for( stl_container_type::iterator_type iterator_name = (container).beginFunc(), end = (container).endFunc(); (iterator_name) != end; ++(iterator_name) )

#define CBL_FOREACH( stl_container_type, iterator_name, container )\
	CBL_FOREACH_IMPL( stl_container_type, iterator, iterator_name, container, begin, end )

#define CBL_FOREACH_CONST( stl_container_type, iterator_name, container )\
	CBL_FOREACH_IMPL( stl_container_type, const_iterator, iterator_name, container, begin, end )

#define CBL_FOREACH_REV( stl_container_type, iterator_name, container )\
	CBL_FOREACH_IMPL( stl_container_type, reverse_iterator, iterator_name, container, rbegin, rend )

#define CBL_FOREACH_REV_CONST( stl_container_type, iterator_name, container )\
	CBL_FOREACH_IMPL( stl_container_type, const_reverse_iterator, iterator_name, container, rbegin, rend )


/***** Template Parameter Helpers *****/
#define CBL_TPLPARAM_REPEAT_1( typeName ) typename typeName##1
#define CBL_TPLPARAM_REPEAT_2( typeName ) CBL_TPLPARAM_REPEAT_1( typeName ), typename typeName##2
#define CBL_TPLPARAM_REPEAT_3( typeName ) CBL_TPLPARAM_REPEAT_2( typeName ), typename typeName##3
#define CBL_TPLPARAM_REPEAT_4( typeName ) CBL_TPLPARAM_REPEAT_3( typeName ), typename typeName##4
#define CBL_TPLPARAM_REPEAT_5( typeName ) CBL_TPLPARAM_REPEAT_4( typeName ), typename typeName##5
#define CBL_TPLPARAM_REPEAT_6( typeName ) CBL_TPLPARAM_REPEAT_5( typeName ), typename typeName##6
#define CBL_TPLPARAM_REPEAT_7( typeName ) CBL_TPLPARAM_REPEAT_6( typeName ), typename typeName##7
#define CBL_TPLPARAM_REPEAT_8( typeName ) CBL_TPLPARAM_REPEAT_7( typeName ), typename typeName##8
#define CBL_TPLPARAM_REPEAT_9( typeName ) CBL_TPLPARAM_REPEAT_8( typeName ), typename typeName##9
#define CBL_TPLPARAM_REPEAT_10( typeName ) CBL_TPLPARAM_REPEAT_9( typeName ), typename typeName##10

#define CBL_TPLPARAM_REPEAT( typeName, count ) CBL_TPLPARAM_REPEAT_##count##( typeName )

/***** Template Parameter Declaration Helpers *****/
#define CBL_PARAM_REPEAT_DECL_1( type, varName ) type##1 varName##1
#define CBL_PARAM_REPEAT_DECL_2( type, varName ) CBL_PARAM_REPEAT_DECL_1( type, varName ), type##2 varName##2
#define CBL_PARAM_REPEAT_DECL_3( type, varName ) CBL_PARAM_REPEAT_DECL_2( type, varName ), type##3 varName##3
#define CBL_PARAM_REPEAT_DECL_4( type, varName ) CBL_PARAM_REPEAT_DECL_3( type, varName ), type##4 varName##4
#define CBL_PARAM_REPEAT_DECL_5( type, varName ) CBL_PARAM_REPEAT_DECL_4( type, varName ), type##5 varName##5
#define CBL_PARAM_REPEAT_DECL_6( type, varName ) CBL_PARAM_REPEAT_DECL_5( type, varName ), type##6 varName##6
#define CBL_PARAM_REPEAT_DECL_7( type, varName ) CBL_PARAM_REPEAT_DECL_6( type, varName ), type##7 varName##7
#define CBL_PARAM_REPEAT_DECL_8( type, varName ) CBL_PARAM_REPEAT_DECL_7( type, varName ), type##8 varName##8
#define CBL_PARAM_REPEAT_DECL_9( type, varName ) CBL_PARAM_REPEAT_DECL_8( type, varName ), type##9 varName##9
#define CBL_PARAM_REPEAT_DECL_10( type, varName ) CBL_PARAM_REPEAT_DECL_9( type, varName ), type##10 varName##10

#define CBL_PARAM_REPEAT_DECL( type, varName, count ) CBL_PARAM_REPEAT_DECL_##count##( type, varName )

/***** Template Parameter Usage Helpers *****/
#define CBL_PARAM_REPEAT_1( varName ) varName##1
#define CBL_PARAM_REPEAT_2( varName ) CBL_PARAM_REPEAT_1( varName ), varName##2
#define CBL_PARAM_REPEAT_3( varName ) CBL_PARAM_REPEAT_2( varName ), varName##3
#define CBL_PARAM_REPEAT_4( varName ) CBL_PARAM_REPEAT_3( varName ), varName##4
#define CBL_PARAM_REPEAT_5( varName ) CBL_PARAM_REPEAT_4( varName ), varName##5
#define CBL_PARAM_REPEAT_6( varName ) CBL_PARAM_REPEAT_5( varName ), varName##6
#define CBL_PARAM_REPEAT_7( varName ) CBL_PARAM_REPEAT_6( varName ), varName##7
#define CBL_PARAM_REPEAT_8( varName ) CBL_PARAM_REPEAT_7( varName ), varName##8
#define CBL_PARAM_REPEAT_9( varName ) CBL_PARAM_REPEAT_8( varName ), varName##9
#define CBL_PARAM_REPEAT_10( varName ) CBL_PARAM_REPEAT_9( varName ), varName##10

#define CBL_PARAM_REPEAT( varName, count ) CBL_PARAM_REPEAT_##count##( varName )


#endif // __CBL_HELPER_H_