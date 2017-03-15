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
  class Event
  {
  public:
    SEH_API
    virtual EventUID GetUID( ) const = 0;
  protected:
    virtual ~Event() {};
  };
}

#endif /* __EVENT_H__ */