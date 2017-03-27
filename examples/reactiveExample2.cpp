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

#include <seh/seh.h>
using namespace seh;

#include <iostream>

class EventManager : public seh::IEventHandler
{
public:
  // We override this method because IEventHandler only propage event if 
  //  parent class has defined the Event callback
  virtual void dispatchEvent( seh::Event* e, const bool& propagation = false ) override
  {
    for ( auto ieh : _childrenHandlers )
    {
      ieh->dispatchEvent( e, propagation );
    }
  }
};

EventManager em;

class SayHelloEvent : public seh::Event
{
  SEH_IMPLEMENT_EVENT( SayHelloEvent )
};

class MyObj : public seh::IEventHandler
{
public:
  MyObj( )
  {
    em.addChildEventHandler( this );
  }
  void sayHello( )
  {
    em.dispatchEvent( new SayHelloEvent( ) );
  }
};

class OtherObj : public seh::IEventHandler
{
public:
  OtherObj( )
  {
    em.addChildEventHandler( this );

    registerEvent( this, &OtherObj::onSayHello );
  }

protected:
  void onSayHello( SayHelloEvent* )
  {
    std::cout << "Hello everybody" << std::endl;
  }
};


int main( )
{
  MyObj myObj;
  OtherObj otherObj;
  std::cout << std::boolalpha << otherObj.hasEvent<SayHelloEvent>( ) << std::endl;
  myObj.sayHello( );


  //system( "PAUSE" );
}
