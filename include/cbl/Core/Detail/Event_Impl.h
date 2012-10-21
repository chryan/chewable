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
 * @file Event_Impl.h
 * @brief Event template implementation.
 * See Event.h and unit test file for usage example.
 */

// Chewable Headers //
#include "cbl/Util/Noncopyable.h"
#include "cbl/Thread/Mutex.h"
#include "cbl/Debug/Assert.h"

#if CBL_EVENT_PARAM_COUNT > 0
#define CBL_EVENT_SEP ,
#else
#define CBL_EVENT_SEP
#endif

#define CBL_EVENT_JOIN_MACRO(X, Y)	CBL_EVENT_DO_JOIN(X, Y)
#define CBL_EVENT_DO_JOIN(X, Y)		CBL_EVENT_DO_JOIN2(X, Y)
#define CBL_EVENT_DO_JOIN2(X, Y)	X##Y

namespace cbl
{
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
#define CBL_EVENT_CLASS_NAME Event
#define CBL_DELEGATE_CLASS_NAME Delegate
#else
#define CBL_EVENT_CLASS_NAME CBL_EVENT_JOIN_MACRO( Event, CBL_EVENT_PARAM_COUNT )
#define CBL_DELEGATE_CLASS_NAME CBL_EVENT_JOIN_MACRO( Delegate, CBL_EVENT_PARAM_COUNT )
#endif
	template< typename RType CBL_EVENT_SEP CBL_EVENT_TEMPLATE_PARAMS >
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
	class CBL_EVENT_CLASS_NAME< RType ( CBL_EVENT_TEMPLATE_ARGS ) > :
#else
	class CBL_EVENT_CLASS_NAME :
#endif
		Noncopyable
	{
	/***** Types *****/
	public:
		typedef RType ReturnType;
#ifdef CBL_TPLFUNCTION_PREFERRED_SYNTAX
		typedef CBL_DELEGATE_CLASS_NAME< RType ( CBL_EVENT_TEMPLATE_ARGS ) > Delegate;	//!< Event delegate type.
#else
		typedef CBL_DELEGATE_CLASS_NAME< RType CBL_EVENT_SEP CBL_EVENT_TEMPLATE_ARGS > Delegate;
#endif

	/***** Public Methods *****/
	public:
		//! Empty default constructor.
		inline CBL_EVENT_CLASS_NAME() {}
		//! Empty destructor.
		inline ~CBL_EVENT_CLASS_NAME() {}
		//! Raise an event with arguments.
		void Raise( CBL_EVENT_PARAMS ) {
			CBL_MUTEX_SCOPEDLOCK( mtxEvent );
			if( mDelegates.size() ) {
				for( cbl::Uint32 i = 0; i < mDelegates.size(); ++i ) {
					Delegate run = mDelegates[i];
					if( run ) run( CBL_EVENT_ARGS );
				}
				if( mSweep ) Sweep();
			}
		}
		//! Raise an event with arguments using the () operator.
		inline void operator () ( CBL_EVENT_PARAMS ) {
			Raise( CBL_EVENT_ARGS );
		}
		//! Register a listener function to the event.
		inline void Register( const typename Delegate & delegate ) {
			CBL_MUTEX_SCOPEDLOCK( mtxEvent );
			mDelegates.push_back( delegate );
		}
		//! Increment operator used to register a listener function to the event.
		inline void operator += ( const typename Delegate & delegate ) {
			Register( delegate );
		}
		//! Unregister a listener function from the event.
		void Unregister( const typename Delegate & delegate ) {
			CBL_MUTEX_SCOPEDLOCK( mtxEvent );
			for( cbl::Uint32 i = 0; i < mDelegates.size(); ++i ) {
				if( mDelegates[i] == delegate ) {
					mDelegates[i].Reset();
					mSweep = true;
					break;
				}
			}
		}
		//! Decrement operator used to unregister a listener function from the event.
		inline void operator -= ( const typename Delegate & delegate ) {
			Unregister( delegate );
		}
		//! Clears all registered event listeners.
		inline void Clear( void ) {
			CBL_MUTEX_SCOPEDLOCK( mtxEvent );
			mDelegates.clear();
		}

	/***** Static Public Methods *****/
	public:
		//! Wrapper function for getting a function delegate.
		template< ReturnType( *OMethod )( CBL_EVENT_TEMPLATE_ARGS ) >
		inline static typename Delegate Function() {
			return Delegate::FromFunction< OMethod >();
		}
		//! Wrapper function for getting a class method delegate.
		template< class O, ReturnType( O::*OMethod )( CBL_EVENT_TEMPLATE_ARGS ) >
		inline static typename Delegate Method( O * objectPtr ) {
			return Delegate::FromMethod< O, OMethod >( objectPtr );
		}
		//! Wrapper function for getting a class const method delegate.
		template< class O, ReturnType( O::*OMethod )( CBL_EVENT_TEMPLATE_ARGS ) const >
		inline static typename Delegate CMethod( const O * objectPtr ) {
			return Delegate::FromConstMethod< O, OMethod >( objectPtr );
		}
		
	/***** Private Methods *****/
	private:
		//! Sweep up invalidated events.
		void Sweep( void ) {
			DelegateList::iterator it = mDelegates.begin();
			while( it != mDelegates.end() ) {
				if( !*it )	it = mDelegates.erase( it );
				else		++it;
			}
			mSweep = false;
		}
		
	/***** Internal Types *****/
	private:
		typedef std::vector< typename Delegate >	DelegateList;	//!< Event delegate list.

	/***** Private Members *****/
	private:
		typename DelegateList	mDelegates;		//!< Event delegates.
		bool					mSweep;			//!< Clean invalid delegates.
		CBL_MUTEX_DECLARE( mtxEvent );
	};
}

#undef CBL_EVENT_PARAM_COUNT
#undef CBL_EVENT_SEP
#undef CBL_EVENT_JOIN_MACRO
#undef CBL_EVENT_DO_JOIN
#undef CBL_EVENT_DO_JOIN2
#undef CBL_EVENT_CLASS_NAME
#undef CBL_DELEGATE_CLASS_NAME