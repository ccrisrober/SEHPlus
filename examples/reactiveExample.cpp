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

class Attack : public Event
{
  SEH_IMPLEMENT_EVENT( Attack )
public:
  Attack( const float& damage )
    : _damage( damage ) {}

  float damage( void ) const
  {
    return _damage;
  }

private:
  float _damage;
};

class Enemy;

class EnemyHit : public Event
{
  SEH_IMPLEMENT_EVENT( EnemyHit )
public:
  EnemyHit( Enemy* enemy )
    : _enemy( enemy ) {}

  Enemy* enemy( ) const
  {
    return _enemy;
  }

private:
  Enemy* _enemy;
};

class CustomEvent : public Event
{
  SEH_IMPLEMENT_EVENT( CustomEvent )
};


class Enemy
{
public:
  Enemy( const std::string& name ) 
    : _name( name )
    , _damage( 15.0f ) {}

  std::string name( void ) const
  {
    return _name;
  }
  float damage( void ) const
  {
    return _damage;
  }

private:
  std::string _name;
  float _damage;
};


class Human : public IEventHandler
{
public:
  Human( )
    : _health( 100 )
  {
    registerEvent( this, &Human::onAttack );
    registerEvent( this, &Human::onEnemyHit );
  }
protected:
  void receiveDamage( int dmg )
  {
    _health -= dmg;
    std::cout << "HP: " << _health << std::endl;
    if ( _health <= 0 )
    {
      std::cout << "I'm dead" << std::endl;
    }
  }
  void onAttack( Attack* attack )
  {
    std::cout << "Hit by attack" << std::endl;
    receiveDamage( attack->damage( ) );
  }

  void onEnemyHit( EnemyHit* hit )
  {
    Enemy* enemy = hit->enemy( );
    std::cout << "Hit by enemy: " << enemy->name( ).c_str( ) << ". Damage: " << enemy->damage( ) << std::endl;
    receiveDamage( enemy->damage( ) );
  }

  int _health;
};

class AirGun
{
public:
  AirGun( )
    : _eventHandler( this )
  {}

  void handleEvent( Event* event )
  {
    // Redirect event to internal event handler
    _eventHandler.dispatchEvent( event );
  }

private:
  class AirGunEventHandler : public IEventHandler
  {
  public:
    AirGunEventHandler( AirGun* tank ) 
      : _tank( tank )
    {
      registerEvent( _tank, &AirGun::onDamagedByAttack );
      //registerEvent( _tank, &AirGun::onEnemyHit );
    }
    AirGun* _tank;
  };
  friend class AirGunEventHandler;
  void onDamagedByAttack( Attack* )
  {
    std::cout << "Hit by attack" << std::endl;
  }
  /*void onEnemyHit( EnemyHit* e )
  {
    std::cout << "Hit by enemy '" << e->enemy( )->name( ) << "'" << std::endl;
  }*/
  AirGunEventHandler _eventHandler;
};


int main( )
{
  std::cout << "HUMAN" << std::endl;
  Human h;
  h.dispatchEvent( new Attack( 20.0f ) );
  h.dispatchEvent( new EnemyHit( new Enemy( std::string( "Enemy1" ) ) ) );
  h.dispatchEvent( new EnemyHit( new Enemy( std::string( "Enemy2" ) ) ) );
  h.dispatchEvent( new Attack( 10.0f ) );
  h.dispatchEvent( new EnemyHit( new Enemy( std::string( "Enemy1" ) ) ) );
  h.dispatchEvent( new Attack( 50.0f ) );

  h.dispatchEvent( new CustomEvent( ) );

  std::cout << std::endl << std::endl;

  std::cout << "AIRGUN" << std::endl;
  AirGun tank;
  tank.handleEvent( new EnemyHit( new Enemy( std::string( "Enemy2" ) ) ) );
  tank.handleEvent( new Attack( 10.0f ) );

  //system( "PAUSE" );


  /*h.dispatchEvent( new CustomEvent( ) );

  std::function<void( CustomEvent* ) > f = [] ( CustomEvent* )
  {
  std::cout << "RECEIVED CUSTOM EVENT" << std::endl;
  };

  h.registerEvent( [ ], &f );*/
}
