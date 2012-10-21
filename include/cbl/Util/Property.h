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
 * @file Property.h
 * @brief Template property class.
 */

#ifndef __CBL_PROPERTY_H_
#define __CBL_PROPERTY_H_

// Disable annoying warning
#pragma warning( disable:4251 )

/***** Getter Macros *****/

//! Getter method macro for defining an accessor/getter method.
//! Usage:
//! @code
//! class GetterTest
//! {
//! public:
//!     GETTER( int, Member );
//!
//!     GETTER_PTR( int, PtrMember )
//!     {
//!         std::cout << "Return pointer." << std::endl;
//!         return _ptrMem;
//!     }
//!     GETTER_REF( int, RefMember )
//!     {
//!         std::cout << "Return by reference." << std::endl;
//!         return _member;
//!     }
//!     GETTER_CREF( int, CRefMember )
//!     {
//!         std::cout << "Return by const reference." << std::endl;
//!         return _member;
//!     }
//! private:
//!     int _member;
//!     int * _ptrMem;
//! }
//!
//! // External declaration.
//! GETTER_DECL( GetterTest, int, Member )
//! {
//!     std::cout << "Return by value." << std::endl;
//!     return _member;
//! }
//! 
//! GetterTest test;
//! test.GetMember();
//! test.GetPtrMember();
//! test.GetRefMember();
//! test.GetCRefMember();
//! @endcode
#define GETTER( type, getter_name )\
	inline const type Get##getter_name( void ) const
//! Reference getter method macro.
//! @see GETTER
#define GETTER_PTR( type, getter_name )\
	inline type * Get##getter_name( void ) const
//! Reference getter method macro.
//! @see GETTER
#define GETTER_CPTR( type, getter_name )\
	inline const type * Get##getter_name( void ) const
//! Reference getter method macro.
//! @see GETTER
#define GETTER_REF( type, getter_name )\
	inline type & Get##getter_name( void )
//! Const reference getter method macro.
//! @see GETTER
#define GETTER_CREF( type, getter_name )\
	inline const type & Get##getter_name( void ) const

//! Getter method definition macro.
#define GETTER_DEF( class_type, type, getter_name )\
	const type class_type::Get##getter_name( void ) const
//! Reference getter method definition macro.
//! @see GETTER
#define GETTER_PTR_DEF( class_type, type, getter_name )\
	inline type * class_type::Get##getter_name( void ) const
//! Reference getter method definition macro.
//! @see GETTER
#define GETTER_CPTR_DEF( class_type, type, getter_name )\
	inline const type * class_type::Get##getter_name( void ) const
//! Reference getter method definition macro.
//! @see GETTER
#define GETTER_REF_DEF( class_type, type, getter_name )\
	inline type & class_type::Get##getter_name( void )
//! Const reference getter method definition macro.
//! @see GETTER
#define GETTER_CREF_DEF( class_type, type, getter_name )\
	inline const type & class_type::Get##getter_name( void ) const

/***** Default Getter Macros *****/
//! Getter method macro for defining a default accessor/getter method.
//! Usage:
//! @code
//! class GetterTest
//! {
//! public:
//!     GETTER_DEFAULT( int, Member, _member );
//!     GETTER_DEFAULT_REF( int, RefMember, _member );
//!     GETTER_DEFAULT_CREF( int, CRefMember, _member );
//! 
//! private:
//!     int _member;
//! }
//! 
//! GetterTest test;
//! test.GetMember();
//! test.GetRefMember();
//! test.GetCRefMember();
//! @endcode
#define GETTER_DEFAULT( type, getter_name, member )\
	GETTER( type, getter_name ) { return member; }
//! Default pointer getter method macro.
//! @see GETTER_DEFAULT_PTR
#define GETTER_DEFAULT_PTR( type, getter_name, member )\
	GETTER_PTR( type, getter_name ) { return member; }
//! Default const pointer getter method macro.
//! @see GETTER_DEFAULT_CPTR
#define GETTER_DEFAULT_CPTR( type, getter_name, member )\
	GETTER_CPTR( type, getter_name ) { return member; }
//! Default reference getter method macro.
//! @see GETTER_DEFAULT
#define GETTER_DEFAULT_REF( type, getter_name, member )\
	GETTER_REF( type, getter_name ) { return member; }
//! Default const reference getter method macro.
//! @see GETTER_DEFAULT
#define GETTER_DEFAULT_CREF( type, getter_name, member )\
	GETTER_CREF( type, getter_name ) { return member; }


/***** Auto Getter Macros *****/
//! Getter method macro for defining a default accessor/getter method without specifying the member name.
//! The member must have the same name as the getter_name with an 'm' in the front.
//! Usage:
//! @code
//! class GetterTest
//! {
//! public:
//!     GETTER_AUTO( int, Member );
//!     GETTER_AUTO_REF( int, RefMember );
//!     GETTER_AUTO_CREF( int, CRefMember );
//! 
//! private:
//!     int mMember;
//!     int mRefMember;
//!     int mCRefMember;
//! }
//! 
//! GetterTest test;
//! test.GetMember();
//! test.GetRefMember();
//! test.GetCRefMember();
//! @endcode
#define GETTER_AUTO( type, getter_name )\
	GETTER_DEFAULT( type, getter_name, m##getter_name )
//! Automatic pointer getter method macro.
//! @see GETTER_AUTO
#define GETTER_AUTO_PTR( type, getter_name )\
	GETTER_DEFAULT_PTR( type, getter_name, m##getter_name )
//! Automatic const pointer getter method macro.
//! @see GETTER_AUTO
#define GETTER_AUTO_CPTR( type, getter_name )\
	GETTER_DEFAULT_CPTR( type, getter_name, m##getter_name )
//! Automatic reference getter method macro.
//! @see GETTER_AUTO
#define GETTER_AUTO_REF( type, getter_name )\
	GETTER_DEFAULT_REF( type, getter_name, m##getter_name )
//! Automatic const reference getter method macro.
//! @see GETTER_AUTO
#define GETTER_AUTO_CREF( type, getter_name )\
	GETTER_DEFAULT_CREF( type, getter_name, m##getter_name )

/***** Setter Macros *****/
//! Setter method macro for defining an mutator/setter method.
//! The member must have the same name as the getter_name with an 'm' in the front.
//! Usage:
//! @code
//! class SetterTest
//! {
//! public:
//!     SETTER( int, Member ) // Source parameter name is 'value'
//!     SETTER_DEFAULT( int, MemberDefault, _member );
//!     SETTER_AUTO( int, MemberAuto );
//! 
//! private:
//!     int _member;
//!     int mMemberAuto;
//! }
//!
//! // External declaration.
//! SETTER_DEF( SetterTest, int, Member )
//! {
//!     _member = value;
//! }
//! 
//! GetterTest test;
//! test.SetMember( 10 );        // _member is now 10.
//! test.SetMemberDefault( 20 ); // _member is now 20.
//! test.SetMemberAuto( 30 );    // mMemberAuto is now 30.
//! @endcode
#define SETTER( type, setter_name )\
	inline void Set##setter_name( const type & value )
//! Regular setter (non-inlined method).
#define SETTER_NO_INLINE( type, setter_name )\
	inline void Set##setter_name( const type & value )
//! Declare external setter function definition.
//! @see SETTER
#define SETTER_DEF( class_type, type, setter_name )\
	void class_type::Set##setter_name( const type & value )
//! Default setter method macro.
//! @see SETTER
#define SETTER_DEFAULT( type, setter_name, member )\
	SETTER( type, setter_name ) { member = value; }
//! Automatic setter method macro.
//! @see SETTER
#define SETTER_AUTO( type, setter_name )\
	SETTER_DEFAULT( type, setter_name, m##setter_name )

/***** Getter/Setter Macros *****/
//! Default getter and setter methods.
//! @see GETTER_DEFAULT
//! @see SETTER_DEFAULT
#define GETSET_DEFAULT( type, getset_name, member )\
	GETTER_DEFAULT( type, getset_name, member )\
	SETTER_DEFAULT( type, getset_name, member )
//! Default reference getter and setter methods.
//! @see GETTER_DEFAULT_REF
//! @see SETTER_DEFAULT
#define GETSET_DEFAULT_REF( type, getset_name, member )\
	GETTER_DEFAULT_REF( type, getset_name, member )\
	SETTER_DEFAULT( type, getset_name, member )
//! Default const reference getter and setter methods.
//! @see GETTER_DEFAULT_CREF
//! @see SETTER_DEFAULT
#define GETSET_DEFAULT_CREF( type, getset_name, member )\
	GETTER_DEFAULT_CREF( type, getset_name, member )\
	SETTER_DEFAULT( type, getset_name, member )
//! Automatic getter and setter methods.
//! @see GETTER_AUTO
//! @see SETTER_AUTO
#define GETSET_AUTO( type, getset_name )\
	GETTER_AUTO( type, getset_name )\
	SETTER_AUTO( type, getset_name )
//! Automatic reference getter and setter methods.
//! @see GETTER_AUTO_REF
//! @see SETTER_AUTO
#define GETSET_AUTO_REF( type, getset_name )\
	GETTER_AUTO_REF( type, getset_name )\
	SETTER_AUTO( type, getset_name )
//! Automatic const reference getter and setter methods.
//! @see GETTER_AUTO_CREF
//! @see SETTER_AUTO
#define GETSET_AUTO_CREF( type, getset_name )\
	GETTER_AUTO_CREF( type, getset_name )\
	SETTER_AUTO( type, getset_name )

#endif //__CBL_PROPERTY_H_
