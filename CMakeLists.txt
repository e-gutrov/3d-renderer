cmake_minimum_required(VERSION 3.10)
project(CourseProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(include/Eigen)
add_subdirectory(include/renderer)

add_executable(${PROJECT_NAME} test.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC include/Eigen include)
target_link_libraries(${PROJECT_NAME} PUBLIC renderer)