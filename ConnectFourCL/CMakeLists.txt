set(SOURCES main.cpp outputResult.cpp collectResult.cpp)
set(HEADERS outputResult.hpp collectResult.hpp)

add_executable(ConnectFourCL ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourCL ConnectFour)
