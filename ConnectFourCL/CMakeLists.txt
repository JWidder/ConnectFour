set(SOURCES main.cpp outputResult.cpp collectResult.cpp  IniFile.cpp)
set(HEADERS outputResult.hpp collectResult.hpp  gsl_assert.h)

add_executable(ConnectFourCL ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourCL ConnectFour  MemBrainDll64.lib)
