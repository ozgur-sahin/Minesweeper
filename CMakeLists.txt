cmake_minimum_required(VERSION 3.16)
project(MinesweeperQt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Critical Qt Automation Flags
# AUTOMOC tells CMake to handle Qt's custom meta-object compiler behind the scenes.
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 2. Locate the core Qt6 graphical libraries on your system
find_package(Qt6 REQUIRED COMPONENTS Widgets)

# 3. Collect your source files
file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# 4. Create the program binary target
add_executable(Minesweeper ${SOURCES})

# 5. Link the Qt6 graphics engine to your compiled binary target
target_link_libraries(Minesweeper PRIVATE Qt6::Widgets)
