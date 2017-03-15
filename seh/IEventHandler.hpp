#ifndef __IEVENT_HANDLER_H__
#define __IEVENT_HANDLER_H__

#include "Event.hpp"
#include <unordered_map>

#include <seh/api.h>

#ifndef SEH_WITH_EVENT_PROPAGATION
#include <iostream>
#endif

namespace seh
{
  class HandlerFn
  {
  public:
    virtual ~HandlerFn( void ) {}
    void exec( const Event* event ) { call( event ); }
  private:
    virtual void call( const Event* ) = 0;
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
    };

    void call( const Event* e );
  private:
    T* _instance;
    MemberFunc _fn;
  };

  class IEventHandler
  {
    using CustomHandlers = std::unordered_map<std::string, HandlerFn*>;
  public:
    SEH_API
    virtual ~IEventHandler( );
    SEH_API
    void dispatchEvent( const Event* e, const bool& propagation = false );
    SEH_API
    void removeEvent( const Event* );

    template <class T, class EventTmpl>
    void registerEvent( T*, void ( T::*evFn )( EventTmpl* ) );

    SEH_API
    bool hasEvent( const Event* );
    SEH_API
    bool hasEvent( const std::string name );

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

#endif /* __IEVENT_HANDLER_H__ */