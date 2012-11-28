set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/arduino-cmake/cmake/ArduinoToolchain.cmake)

cmake_minimum_required(VERSION 2.8)

project(arduino-android C CXX)

print_board_list()
print_programmer_list()


add_subdirectory(src)  
