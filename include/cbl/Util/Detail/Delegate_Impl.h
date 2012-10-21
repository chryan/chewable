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
 * @file Delegate_Impl.h
 * @brief
 * Templated delegate object that can store a function pointer or a member function pointer.
 * Reference: http://www.codeproject.com/KB/cpp/ImpossiblyFastCppDelegate.aspx.
 */

#if CBL_DELEGATE_PARAM_COUNT > 0
#define CBL_DELEGATE_SEP ,
#else
#define CBL_DELEGATE_SEP
#endif

#define CBL_DELEGATE_JOIN_MACRO(X, Y)	CBL_DELEGATE_DO_JOIN(X, Y)
#define CBL_DELEGATE_DO_JOIN(X, Y)		CBL_DELEGATE_DO_JOIN2(X, Y)
#define CBL_DELEGATE_DO_JOIN2(X, Y)		X##Y

namespace cbl
{
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
#define CBL_DELEGATE_CLASS_NAME Delegate
#else
#define CBL_DELEGATE_CLASS_NAME CBL_DELEGATE_JOIN_MACRO( Delegate, CBL_DELEGATE_PARAM_COUNT )
#endif
	template <typename RType CBL_DELEGATE_SEP CBL_DELEGATE_TEMPLATE_PARAMS>
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
	class CBL_DELEGATE_CLASS_NAME< RType ( CBL_DELEGATE_TEMPLATE_ARGS ) >
#else
	class CBL_DELEGATE_CLASS_NAME
#endif
	{
	/***** Types *****/
	public:
		typedef RType ReturnType;		//!< Delegate return type.
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
		typedef ReturnType ( CBL_DELEGATE_CALLTYPE * SignatureType )( CBL_DELEGATE_TEMPLATE_ARGS );
#endif

	/***** Public Methods *****/
	public:
		//! Get a function delegate.
		template< ReturnType( *TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) >
		inline static CBL_DELEGATE_CLASS_NAME FromFunction() {
			return FromStub( NULL, &FunctionStub< TMethod > );
		}
		//! Get a class method delegate.
		template< class T, ReturnType( T::*TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) >
		inline static CBL_DELEGATE_CLASS_NAME FromMethod( T * objectPtr ) {
			return FromStub( objectPtr, &MethodStub< T, TMethod > );
		}
		//! Get a class const method delegate.
		template< class T, ReturnType( T::*TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) const >
		inline static CBL_DELEGATE_CLASS_NAME FromConstMethod( T const * objectPtr ) {
			return FromStub( const_cast< T * >( objectPtr ), &ConstMethodStub< T, TMethod > );
		}
		//! Bracket operator used to trigger delegate.
		inline ReturnType operator()( CBL_DELEGATE_PARAMS ) const {
			return ( *mStubPtr )( mObjectPtr CBL_DELEGATE_SEP CBL_DELEGATE_ARGS );
		}
		//! Check if delegate is empty.
		inline operator bool ( void ) const {
			return mStubPtr != NULL;
		}
		//! Logical negation operator.
		inline bool operator!( void ) const {
			return !( operator bool() );
		}
		//! For STL container storage.
		inline bool operator < ( const CBL_DELEGATE_CLASS_NAME & rhs ) const {
			return ( mObjectPtr < rhs.mObjectPtr ) && ( mStubPtr < rhs.mStubPtr );
		}
		//! Compares two delegates if they are the same.
		inline bool operator == ( const CBL_DELEGATE_CLASS_NAME & rhs ) const {
			return ( rhs.mObjectPtr == mObjectPtr ) && ( rhs.mStubPtr == mStubPtr );
		}
		//! Resets the delegate to NULL (for invalidation).
		inline void Reset( void ) {
			mStubPtr = NULL;
		}

	/***** Internal Types *****/
	private:
		//! Function callback type.
		typedef ReturnType ( CBL_DELEGATE_CALLTYPE * StubType )( void * objectPtr CBL_DELEGATE_SEP CBL_DELEGATE_PARAMS );

	/***** Private Methods *****/
	private:
		//! Constructor.
		inline CBL_DELEGATE_CLASS_NAME() : mObjectPtr(NULL),	mStubPtr(NULL) {}
		//! Overloaded constructor.
		inline CBL_DELEGATE_CLASS_NAME( void * objPtr, StubType stubPtr ) : mObjectPtr(objPtr), mStubPtr(stubPtr) {}
		//! Get the delegate 'stub'
		inline static CBL_DELEGATE_CLASS_NAME FromStub( void * objectPtr, StubType stubType ) {
			return CBL_DELEGATE_CLASS_NAME( objectPtr, stubType );
		}
		//! Call the delegate function 'stub'.
		template< ReturnType( *TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) >
		inline static ReturnType CBL_FASTCALL FunctionStub( void * CBL_DELEGATE_SEP CBL_DELEGATE_PARAMS ) {
			return ( TMethod )( CBL_DELEGATE_ARGS );
		}
		//! Call the delegate method 'stub'.
		template< class T, ReturnType( T::*TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) >
		inline static ReturnType CBL_DELEGATE_CALLTYPE MethodStub( void * objectPtr CBL_DELEGATE_SEP CBL_DELEGATE_PARAMS ) {
			T * p = static_cast< T * >( objectPtr );
			return ( p->*TMethod )( CBL_DELEGATE_ARGS );
		}
		//! Call the delegate const method 'stub'.
		//! @tparam	T			Object type.
		//! @tparam	TMethod		Function pointer type.
		//! @param	stubType	Calling member const function (stub) type.
		//! @return				Returns the member const function's return data.
		template< class T, ReturnType( T::*TMethod )( CBL_DELEGATE_TEMPLATE_ARGS ) const >
		inline static ReturnType CBL_DELEGATE_CALLTYPE ConstMethodStub( void * objectPtr CBL_DELEGATE_SEP CBL_DELEGATE_PARAMS )
		{
			T const * p = static_cast< T * >( objectPtr );
			return ( p->*TMethod )( CBL_DELEGATE_ARGS );
		}

	/***** Private Members *****/
	private:
		void	 	* mObjectPtr;	//!< Object pointer.
		StubType 	mStubPtr;		//!< Function mapping pointer.
	};
}

#undef CBL_DELEGATE_SEP
#undef CBL_DELEGATE_JOIN_MACRO
#undef CBL_DELEGATE_DO_JOIN
#undef CBL_DELEGATE_DO_JOIN2
#undef CBL_DELEGATE_CLASS_NAME