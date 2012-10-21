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
 * @file CblRegistrar.h
 * @brief Chewable type registrar.
 */

#ifndef __CBL_CBLREGISTRAR_H_
#define __CBL_CBLREGISTRAR_H_

// Chewable Headers //
#include "cbl/Chewable.h"

namespace cbl
{
	//! Chewable registrar.
	//! Takes care of registering all chewable types.
	class CBL_API CblRegistrar
	{
	/***** Public Static Methods *****/
	public:
		//! Register Chewable types in the CBL_ENT.
		static void RegisterCblTypes( void );

	/***** Private Methods *****/
	private:
		//! Constructor.
		CblRegistrar();
		
	/***** Private Members *****/
	private:
		static CblRegistrar _sInstance;	//!< Static instance to handle automatic registration.
	};
}

#endif // __CBL_CBLREGISTRAR_H_
