cmake_minimum_required(VERSION 3.15.3)
project(opengl)

set(CMAKE_CXX_STANDARD 14)
set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR "C:/Users/Tom/Desktop/libs/SFML-2.5.1/lib/cmake/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics network audio REQUIRED)

find_package(OpenGL REQUIRED)

add_executable(opengl main.cpp)



target_link_libraries(opengl sfml-graphics sfml-audio)
target_link_libraries(opengl ${OPENGL_LIBRARY} libglew32.a)