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

#endif // __CBL_HELPER_H_