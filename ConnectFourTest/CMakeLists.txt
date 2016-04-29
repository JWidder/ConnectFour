set(SOURCES ConnectFourTest.cpp GameTest.cpp)
set(HEADERS catch.hpp gsl_assert.h)

add_executable(ConnectFourTest ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourTest ConnectFour)
