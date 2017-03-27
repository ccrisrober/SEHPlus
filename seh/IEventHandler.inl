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

template <class T, class EventTmpl>
void IEventHandler::registerEvent( T* o, void ( T::*evFn )( EventTmpl* ) )
{
_customHandlers[ EventTmpl::StaticGetUID( ) ] = new EventFunctionHandler<T, EventTmpl>( o, evFn );
}

template<class EventTmpl>
void IEventHandler::removeEvent( )
{
  auto it = _customHandlers.find( EventTmpl::StaticGetUID( ) );
  _customHandlers.erase( it );
}

template<class EventTmpl>
bool IEventHandler::hasEvent( )
{
  return _customHandlers.find( EventTmpl::StaticGetUID( ) ) != _customHandlers.end( );
}

template <class T, class EventTmpl>
void EventFunctionHandler<T, EventTmpl>::call( Event* e )
{
  ( _instance->*_fn )( static_cast< EventTmpl* >( e ) );
}
