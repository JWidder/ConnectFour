set(SOURCES ConnectFourTest.cpp)
set(HEADERS catch.hpp gsl_assert.h)

add_executable(ConnectFourTest ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourTest ConnectFour)
