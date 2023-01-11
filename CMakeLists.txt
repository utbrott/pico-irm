cmake_minimum_required(VERSION 3.12)

# Pull in SDK
include(pico_sdk_import.cmake)

project(resistance_meter C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

pico_sdk_init()

add_executable(${PROJECT_NAME}
    main.cpp
    lib/display.cpp
)

add_subdirectory(
    pico-ssd1306
)

target_link_libraries(${PROJECT_NAME}
    pico_stdlib
    pico_ssd1306
    hardware_i2c
)

pico_add_extra_outputs(${PROJECT_NAME})
