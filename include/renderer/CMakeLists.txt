cmake_minimum_required(VERSION 3.10)
project(renderer)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(${PROJECT_NAME} screen.cpp renderer.cpp world.cpp camera.cpp primitives.cpp flat_primitives.cpp  application.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ../Eigen ../SFML)

target_link_libraries(${PROJECT_NAME} PUBLIC sfml-graphics sfml-window sfml-system)
