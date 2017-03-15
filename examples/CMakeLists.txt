include_directories(
  ${PROJECT_BINARY_DIR}/include
  ${PROJECT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

set( SEHEXAMPLE_HEADERS )
set( SEHEXAMPLE_SOURCES example.cpp )
set( SEHEXAMPLE_LINK_LIBRARIES
  seh
)
common_application( sehExample )
