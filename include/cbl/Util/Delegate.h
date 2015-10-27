#pragma once
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
* @file Delegate.h
* @brief
* Templated delegate object that can store a function pointer or a member function pointer.
* Reference: http://www.codeproject.com/KB/cpp/ImpossiblyFastCppDelegate.aspx.
*/

#ifndef __CBL_DELEGATE_H_
#define __CBL_DELEGATE_H_

#define CBL_DELEGATE_CALLTYPE CBL_FASTCALL

namespace cbl
{
	template<class RType>
	class Delegate;

	template<class RType, class... Args>
	class Delegate<RType(Args...)>
	{
	/***** Public Methods *****/
	public:
		//! Get a function delegate.
		template< RType(*TMethod)(Args...) >
		inline static Delegate FromFunction() {
			return FromStub(NULL, &FunctionStub<TMethod>);
		}
		//! Get a class method delegate.
		template< typename T, RType(T::*TMethod)(Args...) >
		inline static Delegate FromMethod(T * objectPtr) {
			return FromStub(objectPtr, &MethodStub< T, TMethod >);
		}
		//! Get a class const method delegate.
		template< typename T, RType(T::*TMethod)(Args...) const >
		inline static Delegate FromConstMethod(T const * objectPtr) {
			return FromStub(const_cast<T *>(objectPtr), &ConstMethodStub< T, TMethod >);
		}
		//! Bracket operator used to trigger delegate.
		inline RType operator()(Args... args) const {
			return (*mStubPtr)(mObjectPtr, args...);
		}
		//! Check if delegate is empty.
		inline operator bool(void) const {
			return mStubPtr != NULL;
		}
		//! Logical negation operator.
		inline bool operator!(void) const {
			return !(operator bool());
		}
		//! For STL container storage.
		inline bool operator < (const Delegate & rhs) const {
			return (mObjectPtr < rhs.mObjectPtr) && (mStubPtr < rhs.mStubPtr);
		}
		//! Compares two delegates if they are the same.
		inline bool operator == (const Delegate & rhs) const {
			return (rhs.mObjectPtr == mObjectPtr) && (rhs.mStubPtr == mStubPtr);
		}
		//! Resets the delegate to NULL (for invalidation).
		inline void Reset(void) {
			mStubPtr = NULL;
		}

	/***** Internal Types *****/
	private:
		//! Function callback type.
		typedef RType(CBL_DELEGATE_CALLTYPE * StubType)(void * objectPtr, Args... args);

	/***** Private Methods *****/
	private:
		//! Constructor.
		inline Delegate () : mObjectPtr(NULL), mStubPtr(NULL) {}
		//! Overloaded constructor.
		inline Delegate(void * objPtr, StubType stubPtr) : mObjectPtr(objPtr), mStubPtr(stubPtr) {}
		//! Get the delegate 'stub'
		inline static Delegate FromStub(void * objectPtr, StubType stubType) {
			return Delegate(objectPtr, stubType);
		}
		//! Call the delegate function 'stub'.
		template< RType(*TMethod)(Args...) >
		inline static RType CBL_DELEGATE_CALLTYPE FunctionStub(void *, Args... args) {
			return (TMethod)(args...);
		}
		//! Call the delegate method 'stub'.
		template< class T, RType(T::*TMethod)(Args...) >
		inline static RType CBL_DELEGATE_CALLTYPE MethodStub(void * objectPtr, Args... args) {
			T * p = static_cast<T *>(objectPtr);
			return (p->*TMethod)(args...);
		}
		//! Call the delegate const method 'stub'.
		//! @tparam	T			Object type.
		//! @tparam	TMethod		Function pointer type.
		//! @param	stubType	Calling member const function (stub) type.
		//! @return				Returns the member const function's return data.
		template< class T, RType(T::*TMethod)(Args...) const >
		inline static RType CBL_DELEGATE_CALLTYPE ConstMethodStub(void * objectPtr, Args... args)
		{
			T const * p = static_cast<T *>(objectPtr);
			return (p->*TMethod)(args...);
		}

	/***** Private Members *****/
	private:
		void	 	*mObjectPtr;	//!< Object pointer.
		StubType 	mStubPtr;		//!< Function mapping pointer.
	};
}

#endif