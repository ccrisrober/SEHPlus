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

#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

#include <seh/api.h>

typedef std::string EventUID;

#define IMPLEMENT_EVENT(__CLASS__) \
  static EventUID StaticGetUID( ) { \
    static std::string sUID = #__CLASS__; \
    return ( EventUID ) sUID; /* This will be unique in the executable! */ \
  } \
  virtual EventUID GetUID( ) const { return StaticGetUID( ); }

namespace seh
{
  class IEventHandler;
  class Event
  {
    friend class IEventHandler;
  public:
    SEH_API
    virtual EventUID GetUID( ) const = 0;
    SEH_API
    void stopPropagation( void )
    {
      _propagation = false;
    }
  private:
    bool isEventPropagation( )
    {
        return _propagation;
    }

    bool _propagation;
  protected:
    Event( )
    : _propagation( true )
    {
    }
    virtual ~Event() {}
  };
}

#endif /* __EVENT_H__ */
