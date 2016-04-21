project(ConnectFour)
cmake_minimum_required(VERSION 3.0)

add_definitions(-DGSL_THROW_ON_CONTRACT_VIOLATION)

add_subdirectory(ConnectFour)
add_subdirectory(ConnectFourTest)
