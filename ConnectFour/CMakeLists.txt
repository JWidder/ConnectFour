
SET(SOURCES ConnectFour.cpp)
SET(HEADERS gsl_assert.h)
SET(PUBLIC Public/ConnectFour.hpp)

add_library(ConnectFour ${SOURCES} ${HEADERS} ${PUBLIC})
target_include_directories(ConnectFour
  PUBLIC Public
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
