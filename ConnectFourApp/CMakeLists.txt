set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
  set(CMAKE_PREFIX_PATH "/usr/local/opt/qt5/")
ENDIF()
IF(WIN32)
  set(CMAKE_PREFIX_PATH "D:/Programming/Libraries/Qt/5.6/msvc2015_64")
ENDIF()
find_package(Qt5Widgets)
find_package(Qt5Core)
find_package(Qt5Gui)

set(SOURCES main.cpp MainWindow.cpp Board.cpp)
set(HEADERS MainWindow.h Board.h)

add_executable(ConnectFourApp WIN32 ${SOURCES} ${HEADERS})
target_link_libraries(ConnectFourApp ConnectFour Qt5::Widgets Qt5::Core Qt5::Gui)
