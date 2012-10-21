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
 * @file String.inl
 * @brief std::string replacement for strings.
 */

namespace cbl
{
	inline String::String()
	: mSize(0)
	, mString(new Char[1])
	{
		mString[0] = '\0';
	}

	inline String::String(const Char* str)
	: mSize( ::strlen(str) )
	, mString( new Char[mSize+1] )
	{
		memcpy(mString,str,mSize);
		mString[mSize] = '\0';
	}

	inline String::String(const Char* str, cbl::Uint32 length)
	: mSize( length )
	, mString( new Char[mSize+1] )
	{
		memcpy(mString,str,mSize);
		mString[mSize] = '\0';
	}

	inline String::String(const std::string& str)
	: mSize( str.size() )
	, mString( new Char[mSize+1] )
	{
		memcpy(mString,str.c_str(),mSize);
		mString[mSize] = '\0';
	}

	inline String::String(const String& str)
	: mSize( str.mSize )
	, mString( new Char[mSize+1] )
	{
		memcpy(mString, str.mString, mSize);
		mString[mSize] = '\0';
	}

	inline String::~String()
	{
		free();
	}

	inline String& String::operator = (const String& str)
	{
		if( mSize < str.mSize ) {
			Char* newString = new Char[str.mSize+1];
			memcpy(newString, str.mString, str.mSize+1);
			free();
			mString = newString;
		}
		else
			memcpy(mString, str.mString, str.mSize+1);

		mSize = str.mSize;
		return *this;
	}

	inline String& String::operator = (const std::string& str) {
		cbl::Uint32 size = str.size();
		if( mSize < size ) {
			Char* newString = new Char[size+1];
			memcpy(newString, str.c_str(), size);
			free();
			mString = newString;
		}
		else
			memcpy(mString, str.c_str(), size);

		mSize = size;
		mString[mSize] = '\0';
		return *this;
	}

	inline String& String::operator = (const Char* str)
	{
		cbl::Uint32 size = ::strlen(str);
		if( mSize < size ) {
			Char* newString = new Char[size+1];
			memcpy(newString, str, size);
			free();
			mString = newString;
		}
		else
			memcpy(mString,str,size);

		mSize = size;
		mString[mSize] = '\0';
		return *this;
	}

	inline String& String::operator += (const String& str )
	{
		cbl::Uint32 newSize = mSize + str.mSize;
		Char* newString = new Char[newSize+1];
		memcpy(newString, mString, mSize);
		memcpy(newString+mSize, str.mString, str.mSize);
		free();

		mSize = newSize;
		mString = newString;
		mString[mSize] = '\0';
		return *this;
	}

	inline String& String::operator += (const std::string& str )
	{
		cbl::Uint32 newSize = mSize + str.size();
		Char* newString = new Char[newSize+1];
		memcpy(newString, mString, mSize);
		memcpy(newString+mSize, str.c_str(), str.size());
		free();

		mSize = newSize;
		mString = newString;
		mString[mSize] = '\0';
		return *this;
	}

	inline String& String::operator += (const Char* str )
	{
		cbl::Uint32 strsize = ::strlen(str);
		cbl::Uint32 newSize = mSize + strsize;
		Char* newString = new Char[newSize+1];
		memcpy(newString, mString, mSize);
		memcpy(newString+mSize, str, strsize);
		free();

		mSize = newSize;
		mString = newString;
		mString[mSize] = '\0';
		return *this;
	}

	inline Char& String::operator [] (int i) {
		return mString[i];
	}

	inline const Char& String::operator [] (int i) const {
		return mString[i];
	}

	inline const Char* String::c_str( void ) const {
		return mString;
	}

	inline size_t String::size( void ) const {
		return mSize;
	}

	inline size_t String::length( void ) const {
		return mSize;
	}

	inline String String::substr(size_t pos, size_t n) const
	{
		return String( mString+pos, n == npos ? mSize-pos: n );
	}

	inline size_t String::find_first_of(Char c, size_t pos) const
	{
		if( pos >= mSize ) return npos;
		while( pos < mSize ) {
			if( c == mString[pos] ) return pos;
			++pos;
		}

		return npos;
	}

	inline size_t String::find_last_of(Char c, size_t pos) const
	{
		if( pos >= mSize ) return npos;
		while( pos >= 0 ) {
			if( c == mString[pos] ) return pos;
			--pos;
		}
		return pos; // -1 will return npos.
	}

	inline String::operator std::string ( void ) const {
		return std::string( mString );
	}

	inline Ostream& operator << (Ostream& o, const String& str) {
		o << str.c_str();
		return o;
	}

	inline bool String::operator == (const String& str) const
	{
		if( mSize != str.mSize ) return false;
		return memcmp( mString, str.mString, mSize ) == 0;
	}

	inline bool String::operator == (const Char* str) const
	{
		if( mSize != ::strlen(str) ) return false;
		return memcmp( mString, str, mSize ) == 0;
	}

	inline bool String::operator == (const std::string& str) const
	{
		if( mSize != str.size() ) return false;
		return memcmp( mString, str.c_str(), mSize ) == 0;
	}

	inline bool String::operator != (const String& str) const
	{
		return !operator==(str);
	}

	inline bool String::operator != (const Char* str) const
	{
		return !operator==(str);
	}

	inline bool String::operator != (const std::string& str) const
	{
		return !operator==(str);
	}

	inline bool String::operator < (const String& str) const
	{
		return memcmp( mString, str.mString, mSize < str.mSize ? mSize+1 : str.mSize+1 ) < 0;
	}

	inline bool String::operator < (const Char* str) const
	{
		size_t len = ::strlen(str);
		return memcmp( mString, str, mSize < len ? mSize+1 : len+1 ) < 0;
	}

	inline bool String::operator < (const std::string& str) const
	{
		size_t len = str.size();
		return memcmp( mString, str.c_str(), mSize < len ? mSize+1 : len+1 ) < 0;
	}

	inline bool String::operator > (const String& str) const
	{
		return memcmp( mString, str.mString, mSize < str.mSize ? mSize+1 : str.mSize+1 ) > 0;
	}

	inline bool String::operator > (const Char* str) const
	{
		size_t len = ::strlen(str);
		return memcmp( mString, str, mSize < len ? mSize+1 : len+1 ) > 0;
	}

	inline bool String::operator > (const std::string& str) const
	{
		size_t len = str.size();
		return memcmp( mString, str.c_str(), mSize < len ? mSize+1 : len+1 ) > 0;
	}

	inline void String::free(void) {
		CBL_DELETE_ARRAY(mString);
	}
}
