set(SOURCES main.cpp )
set(HEADERS )

add_executable(ConnectFourReferenz ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourReferenz ConnectFour)
