cmake_minimum_required(VERSION 3.22)


set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)


if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})


set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

set(STM32_MCU_FLAGS  "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard " )


set(STM32_LINKER_SCRIPT stm32h7r7xx_flash.ld)
set(STM32_LINKER_OPTION  )


include("../gcc-arm-none-eabi.cmake")

get_filename_component(PROJECT_ROOT_NAME ${CMAKE_SOURCE_DIR} NAME)
set(CMAKE_PROJECT_NAME ${PROJECT_ROOT_NAME})
project(${CMAKE_PROJECT_NAME})
add_executable(${CMAKE_PROJECT_NAME})

include("mx-generated.cmake")

set(CMAKE_CXX_COMPILER_FORCED "true") 


# 设置 lv_conf.h 路径
set(LV_CONF_PATH ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_conf.h CACHE STRING "Path to lv_conf.h")

# 添加 LVGL 子目录
add_subdirectory(${CMAKE_SOURCE_DIR}/../MiddlewareMy/lvgl lvgl)

# 添加 USBX 子目录
add_subdirectory(${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx usbx)

target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 

)

enable_language(C ASM)

target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    

    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/gt9xx
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lcd_4inches_rgb

    ${CMAKE_SOURCE_DIR}/../MiddlewareMy
)


target_sources(${CMAKE_PROJECT_NAME} PRIVATE

    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/gt9xx/gt9xx.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lcd_4inches_rgb/rgb_lcd_init.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_port_disp.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/lv_port_indev.c
    

)

# 链接 LVGL 和USBX 库
target_link_libraries(${CMAKE_PROJECT_NAME} lvgl usbx)

target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE

)


if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()









