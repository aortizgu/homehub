cmake_minimum_required(VERSION 3.0.0)
project(homehub DESCRIPTION "smart thermostat app" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -g -O0")
set(CMAKE_PLATFORM_INDEPENDENT_CODE ON)

add_subdirectory(spdlog)

set(INSTALL_BIN_DIR "/tmp/homehub")
option(BUILD_CTL "Build drogon_ctl" OFF)
option(BUILD_EXAMPLES "Build examples" OFF)
add_subdirectory(drogon)

add_subdirectory(src)