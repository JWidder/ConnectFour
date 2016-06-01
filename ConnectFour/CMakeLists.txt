
SET(SOURCES ConnectFour.cpp Players.cpp)
SET(HEADERS gsl_assert.h)
SET(PUBLIC Public/ConnectFour.hpp Public/Players.hpp)

add_library(ConnectFour ${SOURCES} ${HEADERS} ${PUBLIC})
target_include_directories(ConnectFour
  PUBLIC Public
  PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(ConnectFour PUBLIC foonathan_memory)
