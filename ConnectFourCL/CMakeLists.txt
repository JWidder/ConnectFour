set(SOURCES main.cpp outputResult.cpp collectResult.cpp neuralNet.cpp neuralPlayer.cpp IniFile.cpp selectPlayer.cpp)
set(HEADERS outputResult.hpp collectResult.hpp neuralNet.hpp NeuralPlayer.hpp gsl_assert.h selectPlayer.hpp)

add_executable(ConnectFourCL ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourCL ConnectFour)
