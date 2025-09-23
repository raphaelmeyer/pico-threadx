cmake_minimum_required(VERSION 4.0)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoThreadXExample)

pico_sdk_init()

add_executable(example)
target_sources(example PRIVATE src/main.c)

target_link_libraries(example PRIVATE pico_stdlib)
