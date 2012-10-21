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
 * @file Thread.inl
 * @brief Threading inline functions.
 */

namespace cbl
{
	inline void Thread::Sleep( cbl::Real seconds )
	{
		Sleep_Impl( cbl::Uint32( seconds * 1000.0f ) );
	}

	inline void Thread::Sleep( cbl::Uint32 milliseconds )
	{
		Sleep_Impl( milliseconds );
	}

	inline void Thread::Yield( void )
	{
		Yield_Impl();
	}

	inline Thread::ThreadID Thread::GetID( void ) const
	{
		return GetID_Impl();
	}

	inline bool Thread::IsRunning( void ) const
	{
		return IsRunning_Impl();
	}

	inline Thread * Thread::GetCurrent()
	{
		return static_cast< Thread * >( GetCurrent_Impl() );
	}

	inline Thread::ThreadID Thread::GetCurrentID( void )
	{
		return GetCurrentID_Impl();
	}
}