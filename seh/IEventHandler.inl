template <class T, class EventTmpl>
void IEventHandler::registerEvent( T* o, void ( T::*evFn )( EventTmpl* ) )
{
_customHandlers[ EventTmpl::StaticGetUID( ) ] = new EventFunctionHandler<T, EventTmpl>( o, evFn );
}

template<class EventTmpl>
bool IEventHandler::hasEvent( )
{
  return _customHandlers.find( EventTmpl::StaticGetUID( ) ) != _customHandlers.end( );
}
#ifdef SEH_EVENT_PROPAGATION
void IEventHandler::addChildEventHandler( IEventHandler* h )
{
  _childrenHandlers.push_back( h );
}
#endif

template <class T, class EventTmpl>
void EventFunctionHandler<T, EventTmpl>::call( const Event* e )
{
  ( _instance->*_fn )( static_cast< EventTmpl* >( e ) );
}