cmake_minimum_required(VERSION 3.22)

# Define the FatFs library
add_library(FatFs STATIC)

# Source files
target_sources(FatFs PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/diskio.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ff.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ff_gen_drv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ffunicode.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/fatfs.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/sd/sd_diskio.c
)

# Include directories
target_include_directories(FatFs PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/src/drivers/sd
    ${CMAKE_CURRENT_SOURCE_DIR}/../Appli/Core/Inc  # For main.h
)

# Link dependencies (if any)
target_link_libraries(FatFs PUBLIC
    stm32cubemx  # Inherit STM32CubeMX definitions and includes
)

# Add compile definitions (optional, based on project needs)
target_compile_definitions(FatFs PRIVATE
    USE_HAL_DRIVER
    STM32H7R7xx
    $<$<CONFIG:Debug>:DEBUG>
)