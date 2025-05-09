cmake_minimum_required(VERSION 3.22)

#
# This file is generated only once,
# and is not re-generated if converter is called multiple times.
#
# User is free to modify the file as much as necessary
#

# Setup compiler settings
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS ON)

# Define the build type
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()

message("Build type: " ${CMAKE_BUILD_TYPE})

# Enable compile command to ease indexing with e.g. clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

# Compiler options
set(STM32_MCU_FLAGS  "-mcpu=cortex-m7 -mfpu=fpv5-d16 -mfloat-abi=hard " )

#Linker options
set(STM32_LINKER_SCRIPT stm32h7r7xx_flash.ld)
set(STM32_LINKER_OPTION  )

# Include toolchain file
include("../gcc-arm-none-eabi.cmake")

# 动态获取项目根目录名称
get_filename_component(PROJECT_ROOT_NAME ${CMAKE_SOURCE_DIR} NAME)

# 设置项目名称为根目录名称
set(CMAKE_PROJECT_NAME ${PROJECT_ROOT_NAME})
project(${CMAKE_PROJECT_NAME})

# 创建可执行目标
add_executable(${CMAKE_PROJECT_NAME})

# Include mx-generated 
include("mx-generated.cmake")


# In order to use CMake for cross-compiling
set(CMAKE_CXX_COMPILER_FORCED "true") 


###########################################################################################################################################################################################################################
# Add project symbols (macros)
target_compile_definitions(${CMAKE_PROJECT_NAME} PRIVATE 
    # Add user defined symbols
    # USE_USBX
    UX_INCLUDE_USER_DEFINE_FILE
)

# Enable CMake support for ASM and C languages
enable_language(C ASM)

# Add include paths
target_include_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined include paths
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/app
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/inc
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/inc
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/ports/generic/inc
)

# Add sources to executable
target_sources(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user sources here
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/app/app_usbx_device.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/app/ux_device_cdc_acm.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/app/ux_device_descriptors.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_alternate_setting_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_alternate_setting_set.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_class_register.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_class_unregister.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_clear_feature.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_configuration_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_configuration_set.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_control_request_process.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_descriptor_send.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_disconnect.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_endpoint_stall.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_get_status.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_host_wakeup.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_initialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_interface_delete.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_interface_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_interface_set.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_interface_start.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_microsoft_extension_register.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_set_feature.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_tasks_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_transfer_abort.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_transfer_all_request_abort.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_transfer_request.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_transfer_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_device_stack_uninitialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_system_error_handler.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_system_initialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_system_tasks_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_system_uninitialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_descriptor_parse.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_long_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_long_put.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_allocate.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_allocate_mulc_safe.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_byte_pool_create.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_byte_pool_search.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_compare.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_copy.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_free.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_free_block_best_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_memory_set.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_short_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/core/src/ux_utility_string_length_check.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_activate.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkin_thread.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkout_thread.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_control_request.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_deactivate.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_entry.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_initialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_ioctl.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_read.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_read_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_tasks_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_unitialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_write.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_write_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_device_classes/src/ux_device_class_cdc_acm_write_with_callback.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_create.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_destroy.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_reset.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_stall.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_status.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_function.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize_complete.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_interrupt_handler.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_abort.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_request.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_run.c
    ${CMAKE_SOURCE_DIR}/../MiddlewareMy/usbx/common/usbx_stm32_device_controllers/ux_dcd_stm32_uninitialize.c
)
###########################################################################################################################################################################################################################

# Link directories setup
target_link_directories(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined library search paths
)

# Add linked libraries
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE
    # Add user defined libraries
)

# Validate that STM32CubeMX code is compatible with C standard
if((CMAKE_C_STANDARD EQUAL 90) OR (CMAKE_C_STANDARD EQUAL 99))
    message(ERROR "Generated code requires C11 or higher")
endif()









