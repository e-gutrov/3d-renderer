cmake_minimum_required(VERSION 3.15)
project(3d_renderer)

set(CMAKE_CXX_STANDARD 17)

include_directories(SFML)
include_directories(Eigen)

add_executable(3d_renderer src/screen.cpp src/renderer.cpp src/world.cpp src/camera.cpp src/primitives.cpp src/flat_primitives.cpp test.cpp)

include_directories(SFML)

target_link_libraries(3d_renderer sfml-graphics sfml-window sfml-system)
