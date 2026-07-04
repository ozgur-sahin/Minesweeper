cmake_minimum_required(VERSION 3.10)
project(MinesweeperLogic)

# Set the C++ standard to keep it rigorous and modern
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB SOURCES CONFIGURE_DEPENDS "*.cpp")

# Tell the compiler to turn your main file into a runnable program
add_executable(Minesweeper ${SOURCES})