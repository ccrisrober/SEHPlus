source_group(\\ FILES CMakeLists.txt)

set( SEH_PUBLIC_HEADERS
  IEventHandler.hpp
  Event.hpp
)

set( SEH_HEADERS
  IEventHandler.inl
)

set( SEH_SOURCES
  IEventHandler.cpp
)

common_library( seh )
