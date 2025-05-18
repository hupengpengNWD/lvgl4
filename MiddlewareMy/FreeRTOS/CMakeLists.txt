cmake_minimum_required(VERSION 3.22)

# 定义 FreeRTOS 静态库
add_library(freertos STATIC)

# FreeRTOS 源文件列表
target_sources(freertos PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/croutine.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/event_groups.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/list.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/queue.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/stream_buffer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/tasks.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/timers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/CMSIS_RTOS_V2/cmsis_os2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/Common/mpu_wrappers.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/Common/mpu_wrappers_v2.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/GCC/ARM_CM4F/port.c
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/MemMang/heap_4.c
)

# FreeRTOS 头文件包含路径
target_include_directories(freertos PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/include
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/CMSIS_RTOS_V2
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/portable/GCC/ARM_CM4F
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

# 链接 stm32cubemx 以继承 CMSIS 路径和定义
target_link_libraries(freertos PUBLIC
    stm32cubemx # Inherit STM32CubeMX definitions and includes
)

# 编译定义（如果需要）
target_compile_definitions(freertos PUBLIC
    # 可根据需要添加，例如 CMSIS-RTOS 相关定义
)