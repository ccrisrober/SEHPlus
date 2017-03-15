#include "IEventHandler.hpp"

namespace seh
{
  IEventHandler::~IEventHandler( )
  {
    CustomHandlers::iterator it = _customHandlers.begin( );
    while( it != _customHandlers.end( ) )
    {
      delete it->second;
      ++it;
    }
    _customHandlers.clear( );
  }

  void IEventHandler::dispatchEvent( const Event* e, const bool& propagation )
  {
    CustomHandlers::iterator it = _customHandlers.find( e->GetUID( ) );
    if( it != _customHandlers.end( ) )
    {
      it->second->exec( e );
#ifdef SEH_EVENT_PROPAGATION
      if( propagation )
      {
        for( auto ieh : _childrenHandlers )
        {
          ieh->dispatchEvent( e, propagation );
        }
      }
#endif
    }
  }

  void IEventHandler::removeEvent( const Event* e )
  {
    CustomHandlers::iterator it = _customHandlers.find( e->GetUID( ) );
    if( it != _customHandlers.end( ) )
    {
      _customHandlers.erase( it );
    }
  }

  bool IEventHandler::hasEvent( const Event* e )
  {
    return _customHandlers.find( e->GetUID( ) ) != _customHandlers.end( );
  }

  bool IEventHandler::hasEvent( const std::string name )
  {
    return _customHandlers.find( name ) != _customHandlers.end( );
  }
}