cmake_minimum_required(VERSION 3.15)
project(CrossZero C)

set(CMAKE_C_STANDARD 99)

add_executable(CrossZero main.c backfield.c backfield.h game.c game.h frontfield.c frontfield.h player.c player.h menu.c menu.h)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(CrossZero ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )