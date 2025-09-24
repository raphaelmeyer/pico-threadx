cmake_minimum_required(VERSION 4.0)

include($ENV{PICO_SDK_PATH}/external/pico_sdk_import.cmake)

project(PicoThreadXExample)

pico_sdk_init()

add_executable(example)
target_sources(example PRIVATE
  src/main.c
  src/tx_initialize_low_level.S
)

target_link_libraries(example PRIVATE pico_stdlib azrtos::threadx cmsis_core)

# set(TX_USER_FILE "${CMAKE_CURRENT_SOURCE_DIR}/src/tx_user_config.h")

add_subdirectory(vendor)
