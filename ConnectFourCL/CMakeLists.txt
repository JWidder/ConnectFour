set(SOURCES main.cpp outputResult.cpp collectResult.cpp neuralNet.cpp neuralPlayer.cpp)
set(HEADERS outputResult.hpp collectResult.hpp neuralNet.hpp)

add_executable(ConnectFourCL ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourCL ConnectFour)
