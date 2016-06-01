set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5/")
ENDIF()
IF(WIN32)
  set(CMAKE_PREFIX_PATH "D:/Development/Libraries/Qt/Qt5.6.0/5.6/msvc2015_64")
ENDIF()
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)
find_package(Qt5Sql)

set(SOURCES main.cpp MainWindow.cpp Board.cpp Database.cpp)
set(HEADERS MainWindow.h Board.h Database.h)

add_executable(ConnectFourApp WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourApp ConnectFour Qt5::Widgets Qt5::Core Qt5::Gui Qt5::Sql)
