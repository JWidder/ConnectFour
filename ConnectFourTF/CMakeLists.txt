set(SOURCES main.cpp brett.cpp patternOutput.cpp snapshot.cpp stdafx.cpp createTrainingFile.cpp IniFile.cpp brettBasis.cpp brettExtended.cpp)
set(HEADERS brett.hpp patternOutput.hpp snapshot.hpp stdafx.h targetver.h createTrainingFile.hpp brettBasis.hpp brettExtended.hpp)
set (Design _design.md)

add_executable(ConnectFourTF ${SOURCES} ${HEADERS} ${Design})

target_link_libraries(ConnectFourTF ConnectFour)
