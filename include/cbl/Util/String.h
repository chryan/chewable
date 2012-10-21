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
 * @file String.h
 * @brief std::string replacement for strings.
 */

#ifndef __CBL_STRING_H_
#define __CBL_STRING_H_

// Chewable Headers //
#include "cbl/Chewable.h"
#include "cbl/Math/Functions.h"

#if CBL_CUSTOM_STRING == CBL_ENABLED
namespace cbl
{
	//! std::string replacement class.
	class CBL_API String
	{
	public:
		static const size_t npos	= size_t(-1);

	public:
		String();
		String(const Char* str);
		String(const Char* str, cbl::Uint32 length);
		String(const std::string& str);
		String(const String& str);
		~String();

		String& operator = (const String& str);
		String& operator = (const std::string& str);
		String& operator = (const Char* str);
		String& operator += (const String& str );
		String& operator += (const std::string& str );
		String& operator += (const Char* str );

		Char& operator [] (int i);
		const Char& operator [] (int i) const;

		const Char* c_str( void ) const;
		size_t size( void ) const;
		size_t length( void ) const;

		String substr(size_t pos = 0, size_t n = npos) const;

		size_t find_first_of(Char c, size_t pos = 0) const;
		size_t find_last_of(Char c, size_t pos = 0) const;

		operator std::string ( void ) const;

		bool operator == (const String& str) const;
		bool operator == (const Char* str) const;
		bool operator == (const std::string& str) const;
		bool operator != (const String& str) const;
		bool operator != (const Char* str) const;
		bool operator != (const std::string& str) const;
		bool operator < (const String& str) const;
		bool operator < (const Char* str) const;
		bool operator < (const std::string& str) const;
		bool operator > (const String& str) const;
		bool operator > (const Char* str) const;
		bool operator > (const std::string& str) const;

	private:
		void free(void);

	private:
		Uint32	mSize;
		Char*	mString;
	};

	Ostream& operator << (Ostream& o, const cbl::String& str);
}

#include "String.inl"

#else
#include <string>
namespace cbl
{
	typedef std::string String;
}
#endif

#endif // __CBL_STRING_H_
