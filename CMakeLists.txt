cmake_minimum_required(VERSION 3.24)
project(sp_engine)
set(CMAKE_CXX_STANDARD 14)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(src)

add_executable(sp_engine src/main.cpp)

target_link_libraries(sp_engine ${OPENGL_LIBRAIRIES})
target_link_libraries(sp_engine ${GLUT_LIBRAIRIES})
target_link_libraries(sp_engine -lopengl32 -g -lfreeglut -lglu32)


