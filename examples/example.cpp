#include <seh/seh.h>
using namespace seh;

#include <iostream>

class CustomEvent : public Event
{
public:
  IMPLEMENT_EVENT( CustomEvent )
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
  IMPLEMENT_EVENT( SelectionEvent )
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
  void onCustomMessage( const CustomEvent* e )
  {
    std::cout << "DockGroupTreeView: " << e->getValue( ) << std::endl;
  }
  void onSelection( const SelectionEvent* e )
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
  void onCustomMessage( const CustomEvent* e )
  {
    std::cout << "SecondTreeView: " << e->getValue( ) << std::endl;
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
  auto ev = new CustomEvent( 5 );
  auto dGroupTreeView = new DockGroupTreeView( );
  dGroupTreeView->dispatchEvent( new CustomEvent( 40 ), true );
  std::cout << std::endl << std::endl;
  dGroupTreeView->dispatchEvent( new SelectionEvent( "hola" ) );
  std::cout << std::endl << std::endl;
  dGroupTreeView->dispatchEvent( new CustomEvent( 20 ) );
  std::cout << std::endl << std::endl;

  auto ss = new SecondTreeView( );
  ss->dispatchEvent( new CustomEvent( 10 ), true );
  std::cout << std::endl << std::endl;
  auto sss = new SubSecondTreeView( );
  ss->addChildEventHandler( sss );

  dGroupTreeView->addChildEventHandler( ss );
  dGroupTreeView->dispatchEvent( new CustomEvent( 40 ), true );
  std::cout << std::endl << std::endl;

  std::cout << ss->hasEvent( new CustomEvent( 10 ) ) << std::endl;
  std::cout << ss->hasEvent( SelectionEvent::StaticGetUID( ) ) << std::endl;
  std::cout << ss->hasEvent<SelectionEvent>( ) << std::endl;
  std::cout << ss->hasEvent<CustomEvent>( ) << std::endl;


  ss->dispatchEvent( new CustomEvent( 40 ), true );
  std::cout << std::endl << std::endl;
  ss->dispatchEvent( new SelectionEvent( "adios" ) );
  std::cout << std::endl << std::endl;
  ss->dispatchEvent( new CustomEvent( 20 ) );
  std::cout << std::endl << std::endl;

  system( "PAUSE" );
}