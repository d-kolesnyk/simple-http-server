cmake_minimum_required(VERSION 2.8)

set(PROJ_NAME "simple-http-server")
project(${PROJ_NAME})

SET( GXX_COMPILE_FLAGS  "-Wall -Werror -Wextra -pedantic -std=c++14 -g -O0")
add_definitions(${GXX_COMPILE_FLAGS})

set(SOURCES
src/main.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})