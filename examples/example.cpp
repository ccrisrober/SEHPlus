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

class CustomEvent : public Event
{
public:
  SEH_IMPLEMENT_EVENT( CustomEvent )
  CustomEvent( int v ) : _value( v ) {}

  int getValue( )	const	{ return _value; }

private:
  int _value;
};

class IDockPlugin : public IEventHandler
{
public:
  IDockPlugin( )
  {
  }
  virtual ~IDockPlugin( )
  {
  }
};

class SelectionEvent : public Event
{
public:
  SEH_IMPLEMENT_EVENT( SelectionEvent )
    SelectionEvent( std::string id )
    : Event( )
    , _id( id )
  {
    }
  std::string id( ) const
  {
    return _id;
  }
protected:
  std::string _id;
};

class DockGroupTreeView : public IDockPlugin
{
public:
  DockGroupTreeView( )
  {
    registerEvent( this, &DockGroupTreeView::onCustomMessage );
    registerEvent( this, &DockGroupTreeView::onSelection );
  }
  void onCustomMessage( CustomEvent* e )
  {
    std::cout << "DockGroupTreeView: " << e->getValue( ) << std::endl;
  }
  void onSelection( SelectionEvent* e )
  {
    std::cout << e->id( ) << std::endl;
  }
  virtual ~DockGroupTreeView( )
  {
  }
};

class SecondTreeView : public IDockPlugin
{
public:
  SecondTreeView( )
  {
    registerEvent( this, &SecondTreeView::onCustomMessage );
  }
  void onCustomMessage( CustomEvent* e )
  {
    std::cout << "SecondTreeView: " << e->getValue( ) << std::endl;
    //e->stopPropagation();
  }
};

class SubSecondTreeView : public IEventHandler
{
public:
  SubSecondTreeView( )
  {
    registerEvent( this, &SubSecondTreeView::onCustomMessage );
  }
  void onCustomMessage( const CustomEvent* e )
  {
    std::cout << "SubSecondTreeView: " << e->getValue( ) << std::endl;
  }
};

int main( )
{
  auto ss = new SecondTreeView();
  auto sss = new SubSecondTreeView();
  ss->addChildEventHandler(sss);
  ss->dispatchEvent(new CustomEvent(1), true);
  sss->removeEvent<CustomEvent>();
  ss->dispatchEvent(new CustomEvent(1), true);

  // system( "PAUSE" );
}
