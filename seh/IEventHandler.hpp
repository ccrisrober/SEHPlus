/**
 * Copyright (c) 2017, Cristian Rodríguez Bernal
 * All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 **/

#ifndef __SEH_IEVENT_HANDLER_H__
#define __SEH_IEVENT_HANDLER_H__

#include "Event.hpp"
#include <unordered_map>

#include <seh/api.h>

#ifdef SEH_EVENT_PROPAGATION
#include <iostream>
#include <vector>
#endif

namespace seh
{
  class HandlerFn
  {
  public:
    virtual ~HandlerFn( void ) {}
    void exec( Event* event ) { call( event ); }
  private:
    virtual void call( Event* ) = 0;
  };
  template <class T, class EventTmpl>
  class EventFunctionHandler : public HandlerFn
  {
  public:
    typedef void ( T::*MemberFunc )( EventTmpl* );
    EventFunctionHandler( T* instance, MemberFunc memFn ) 
      : _instance( instance )
      , _fn( memFn )
    {
    }
    void call( Event* e );
  private:
    T* _instance;
    MemberFunc _fn;
  };

  class IEventHandler
  {
    using CustomHandlers = std::unordered_map<std::string, HandlerFn*>;
  public:
    SEH_API
    virtual ~IEventHandler( void );
    SEH_API
    virtual void dispatchEvent( Event* e, const bool& propagation = false );
    SEH_API
    void removeEvent( const Event* );
    SEH_API
    void removeEvent( const std::string& name );

    template<class EventTmpl>
    void removeEvent( );

    template <class T, class EventTmpl>
    void registerEvent( T*, void ( T::*evFn )( EventTmpl* ) );

    SEH_API
    bool hasEvent( const Event* );
    SEH_API
    bool hasEvent( const std::string& name );

    template<class EventTmpl>
    bool hasEvent( );

  public:
    SEH_API
    void addChildEventHandler( IEventHandler* h );

#ifdef SEH_EVENT_PROPAGATION
  protected:
    std::vector< IEventHandler*> _childrenHandlers;
#endif

  private:
    CustomHandlers _customHandlers;
  };

  #include "IEventHandler.inl"
}

#endif /* __SEH_IEVENT_HANDLER_H__ */
