cmake_minimum_required(VERSION 3.26)
project(SFMLII)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR C:/Users/kurom/vcpkg/vcpkg/installed/x64-windows/share/sfml)


add_executable(SFMLII main.cpp)
find_package(SFML 2.5 COMPONENTS graphics system window CONFIG REQUIRED)
target_link_libraries(SFMLII sfml-graphics sfml-system sfml-window)