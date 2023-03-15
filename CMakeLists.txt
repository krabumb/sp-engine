cmake_minimum_required(VERSION 3.24)
project(sp_engine)
set(CMAKE_C_STANDARD 17)
set(CMAKE_GENERATOR_PLATFORM x64)

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(STATUS "Target architecture: 64-bit")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(STATUS "Target architecture: 32-bit")
else()
    message(FATAL_ERROR "Unknown target architecture")
endif()

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(src)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

add_executable(sp_engine src/main.c)

target_link_libraries(sp_engine ${OPENGL_LIBRAIRIES})
target_link_libraries(sp_engine ${GLUT_LIBRAIRIES})

target_link_libraries(sp_engine -lfreeglut -lopengl32 -lglu32)
target_link_libraries(sp_engine -A x64)


