# Minimum CMake version required
cmake_minimum_required(VERSION 3.22)

# Define the USBX static library
add_library(usbx STATIC)

# Collect USBX source files

set(USBX_SOURCES

    ${CMAKE_CURRENT_SOURCE_DIR}/app/app_usbx_device.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app/ux_device_cdc_acm.c
    ${CMAKE_CURRENT_SOURCE_DIR}/app/ux_device_descriptors.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_alternate_setting_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_alternate_setting_set.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_class_register.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_class_unregister.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_clear_feature.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_configuration_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_configuration_set.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_control_request_process.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_descriptor_send.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_disconnect.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_endpoint_stall.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_get_status.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_host_wakeup.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_initialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_interface_delete.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_interface_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_interface_set.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_interface_start.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_microsoft_extension_register.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_set_feature.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_tasks_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_transfer_abort.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_transfer_all_request_abort.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_transfer_request.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_transfer_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_device_stack_uninitialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_system_error_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_system_initialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_system_tasks_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_system_uninitialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_descriptor_parse.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_long_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_long_put.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_allocate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_allocate_mulc_safe.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_byte_pool_create.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_byte_pool_search.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_compare.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_copy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_free.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_free_block_best_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_memory_set.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_short_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/src/ux_utility_string_length_check.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_activate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkin_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_bulkout_thread.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_control_request.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_deactivate.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_entry.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_initialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_ioctl.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_read.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_read_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_tasks_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_unitialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_write.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_write_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/src/ux_device_class_cdc_acm_write_with_callback.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_callback.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_create.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_destroy.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_reset.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_stall.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_endpoint_status.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_frame_number_get.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_function.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_initialize_complete.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_interrupt_handler.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_abort.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_request.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_transfer_run.c
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers/ux_dcd_stm32_uninitialize.c
)

# Add sources to the usbx library
target_sources(usbx PRIVATE ${USBX_SOURCES})

# Add include directories for USBX
target_include_directories(usbx PUBLIC


    ${CMAKE_CURRENT_SOURCE_DIR}/app
    ${CMAKE_CURRENT_SOURCE_DIR}/common/core/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_device_classes/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/common/usbx_stm32_device_controllers
    ${CMAKE_CURRENT_SOURCE_DIR}/ports/generic/inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/STM32H7RSxx_HAL_Driver/Inc
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Device/ST/STM32H7RSxx/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Drivers/CMSIS/Include
    ${CMAKE_CURRENT_SOURCE_DIR}/../../Appli/Core/Inc      
    
)

# Add compile definitions for USBX
target_compile_definitions(usbx PUBLIC
    STM32H7R7xx                   
    UX_DEVICE_CDC_ACM  # 显式启用 CDC ACM
    UX_INCLUDE_USER_DEFINE_FILE
    
)