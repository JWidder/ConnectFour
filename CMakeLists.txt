project(ConnectFour)
cmake_minimum_required(VERSION 3.0)

add_definitions(-DGSL_THROW_ON_CONTRACT_VIOLATION)
if (WIN32)
  add_definitions(-D_SCL_SECURE_NO_WARNINGS)
else()
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
endif()

link_directories("C:/Program Files (x86)/MemBrain/DLL")

set(FOONATHAN_MEMORY_BUILD_TESTS OFF)
set(FOONATHAN_MEMORY_BUILD_TOOLS OFF)

#copy comp to outdir since download does not work here
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp11_lang DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp11_lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp14_lang DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp14_lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp17_lang DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/cpp17_lib DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/env DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/ext DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/compatibility/ts DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/comp.downloaded)

add_subdirectory(memory)
add_subdirectory(ConnectFour)
add_subdirectory(ConnectFourTest)
add_subdirectory(ConnectFourApp)
add_subdirectory(ConnectFourCL)
add_subdirectory(ConnectFourTF)
add_subdirectory(DLL)