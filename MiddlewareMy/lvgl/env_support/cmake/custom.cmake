include("${CMAKE_CURRENT_LIST_DIR}/version.cmake")


# 禁用示例和演示代码
set(LV_CONF_BUILD_DISABLE_EXAMPLES ON)
set(LV_CONF_BUILD_DISABLE_DEMOS OFF)

# Option to define LV_LVGL_H_INCLUDE_SIMPLE, default: ON
option(LV_LVGL_H_INCLUDE_SIMPLE
       "Use #include \"lvgl.h\" instead of #include \"../../lvgl.h\"" ON)

# Option to define LV_CONF_INCLUDE_SIMPLE, default: ON
option(LV_CONF_INCLUDE_SIMPLE
       "Use #include \"lv_conf.h\" instead of #include \"../../lv_conf.h\"" ON)

# Option LV_CONF_PATH, which should be the path for lv_conf.h
# If set parent path LV_CONF_DIR is added to includes
if( LV_CONF_PATH )
    get_filename_component(LV_CONF_DIR ${LV_CONF_PATH} DIRECTORY)
endif( LV_CONF_PATH )

# Option to build shared libraries (as opposed to static), default: OFF
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

####################修改开始###############################################################################
# Set sources used for LVGL components
# file(GLOB_RECURSE SOURCES ${LVGL_ROOT_DIR}/src/*.c ${LVGL_ROOT_DIR}/src/*.S)
# file(GLOB_RECURSE EXAMPLE_SOURCES ${LVGL_ROOT_DIR}/examples/*.c)
# file(GLOB_RECURSE DEMO_SOURCES ${LVGL_ROOT_DIR}/demos/*.c)
# file(GLOB_RECURSE THORVG_SOURCES ${LVGL_ROOT_DIR}/src/libs/thorvg/*.cpp ${LVGL_ROOT_DIR}/src/others/vg_lite_tvg/*.cpp)

# 屏蔽上面的 file(GLOB_RECURSE....，因为我的CMake不支持，换成下面的

file(GLOB SOURCES

    ${LVGL_ROOT_DIR}/src/*.c
    ${LVGL_ROOT_DIR}/src/core/*.c
    ${LVGL_ROOT_DIR}/src/display/*.c
    ${LVGL_ROOT_DIR}/src/draw/*.c
    ${LVGL_ROOT_DIR}/src/draw/sw/*.c
    ${LVGL_ROOT_DIR}/src/draw/sw/blend/*.c
    ${LVGL_ROOT_DIR}/src/draw/sw/blend/arm2d/*.c
    ${LVGL_ROOT_DIR}/src/draw/sw/blend/helium/*.c
    ${LVGL_ROOT_DIR}/src/draw/sw/blend/neon/*.c
    ${LVGL_ROOT_DIR}/src/draw/vg_lite/*.c
    ${LVGL_ROOT_DIR}/src/font/*.c
    ${LVGL_ROOT_DIR}/src/indev/*.c
    ${LVGL_ROOT_DIR}/src/layouts/*.c
    ${LVGL_ROOT_DIR}/src/layouts/flex/*.c
    ${LVGL_ROOT_DIR}/src/layouts/grid/*.c
    ${LVGL_ROOT_DIR}/src/libs/*.c
    ${LVGL_ROOT_DIR}/src/libs/barcode/*.c
    ${LVGL_ROOT_DIR}/src/libs/bin_decoder/*.c
    ${LVGL_ROOT_DIR}/src/libs/bmp/*.c
    ${LVGL_ROOT_DIR}/src/libs/ffmpeg/*.c
    ${LVGL_ROOT_DIR}/src/libs/freetype/*.c
    ${LVGL_ROOT_DIR}/src/libs/fsdrv/*.c
    ${LVGL_ROOT_DIR}/src/libs/gif/*.c
    ${LVGL_ROOT_DIR}/src/libs/libjpeg_turbo/*.c
    ${LVGL_ROOT_DIR}/src/libs/libpng/*.c
    ${LVGL_ROOT_DIR}/src/libs/lodepng/*.c
    ${LVGL_ROOT_DIR}/src/libs/lz4/*.c
    ${LVGL_ROOT_DIR}/src/libs/qrcode/*.c
    ${LVGL_ROOT_DIR}/src/libs/rle/*.c
    ${LVGL_ROOT_DIR}/src/libs/rlottie/*.c
    ${LVGL_ROOT_DIR}/src/libs/thorvg/*.c
    ${LVGL_ROOT_DIR}/src/libs/tiny_ttf/*.c
    ${LVGL_ROOT_DIR}/src/libs/tjpgd/*.c
    ${LVGL_ROOT_DIR}/src/misc/*.c
    ${LVGL_ROOT_DIR}/src/misc/cache/*.c
    ${LVGL_ROOT_DIR}/src/osal/*.c
    ${LVGL_ROOT_DIR}/src/others/*.c
    ${LVGL_ROOT_DIR}/src/others/file_explorer/*.c
    ${LVGL_ROOT_DIR}/src/others/fragment/*.c
    ${LVGL_ROOT_DIR}/src/others/gridnav/*.c
    ${LVGL_ROOT_DIR}/src/others/ime/*.c
    ${LVGL_ROOT_DIR}/src/others/imgfont/*.c
    ${LVGL_ROOT_DIR}/src/others/monkey/*.c
    ${LVGL_ROOT_DIR}/src/others/observer/*.c
    ${LVGL_ROOT_DIR}/src/others/snapshot/*.c
    ${LVGL_ROOT_DIR}/src/others/sysmon/*.c
    ${LVGL_ROOT_DIR}/src/others/vg_lite_tvg/*.c
    ${LVGL_ROOT_DIR}/src/stdlib/*.c
    ${LVGL_ROOT_DIR}/src/stdlib/builtin/*.c
    ${LVGL_ROOT_DIR}/src/stdlib/clib/*.c
    ${LVGL_ROOT_DIR}/src/stdlib/micropython/*.c
    ${LVGL_ROOT_DIR}/src/stdlib/rtthread/*.c
    ${LVGL_ROOT_DIR}/src/themes/*.c
    ${LVGL_ROOT_DIR}/src/themes/default/*.c
    ${LVGL_ROOT_DIR}/src/themes/mono/*.c
    ${LVGL_ROOT_DIR}/src/themes/simple/*.c
    ${LVGL_ROOT_DIR}/src/tick/*.c
    ${LVGL_ROOT_DIR}/src/widgets/*.c
    ${LVGL_ROOT_DIR}/src/widgets/animimage/*.c
    ${LVGL_ROOT_DIR}/src/widgets/arc/*.c
    ${LVGL_ROOT_DIR}/src/widgets/bar/*.c
    ${LVGL_ROOT_DIR}/src/widgets/button/*.c
    ${LVGL_ROOT_DIR}/src/widgets/buttonmatrix/*.c
    ${LVGL_ROOT_DIR}/src/widgets/calendar/*.c
    ${LVGL_ROOT_DIR}/src/widgets/canvas/*.c
    ${LVGL_ROOT_DIR}/src/widgets/chart/*.c
    ${LVGL_ROOT_DIR}/src/widgets/checkbox/*.c
    ${LVGL_ROOT_DIR}/src/widgets/dropdown/*.c
    ${LVGL_ROOT_DIR}/src/widgets/image/*.c
    ${LVGL_ROOT_DIR}/src/widgets/imagebutton/*.c
    ${LVGL_ROOT_DIR}/src/widgets/keyboard/*.c
    ${LVGL_ROOT_DIR}/src/widgets/label/*.c
    ${LVGL_ROOT_DIR}/src/widgets/led/*.c
    ${LVGL_ROOT_DIR}/src/widgets/line/*.c
    ${LVGL_ROOT_DIR}/src/widgets/list/*.c
    ${LVGL_ROOT_DIR}/src/widgets/lottie/*.c
    ${LVGL_ROOT_DIR}/src/widgets/menu/*.c
    ${LVGL_ROOT_DIR}/src/widgets/msgbox/*.c
    ${LVGL_ROOT_DIR}/src/widgets/objx_templ/*.c
    ${LVGL_ROOT_DIR}/src/widgets/property/*.c
    ${LVGL_ROOT_DIR}/src/widgets/roller/*.c
    ${LVGL_ROOT_DIR}/src/widgets/scale/*.c
    ${LVGL_ROOT_DIR}/src/widgets/slider/*.c
    ${LVGL_ROOT_DIR}/src/widgets/span/*.c
    ${LVGL_ROOT_DIR}/src/widgets/spinbox/*.c
    ${LVGL_ROOT_DIR}/src/widgets/spinner/*.c
    ${LVGL_ROOT_DIR}/src/widgets/switch/*.c
    ${LVGL_ROOT_DIR}/src/widgets/table/*.c
    ${LVGL_ROOT_DIR}/src/widgets/tabview/*.c
    ${LVGL_ROOT_DIR}/src/widgets/textarea/*.c
    ${LVGL_ROOT_DIR}/src/widgets/tileview/*.c
    ${LVGL_ROOT_DIR}/src/widgets/win/*.c
    ${LVGL_ROOT_DIR}/src/*.S

)

file(GLOB DEMO_SOURCES
    ${LVGL_ROOT_DIR}/demos/widgets/*.c
    ${LVGL_ROOT_DIR}/demos/widgets/assets/*.c
)
# 禁用 ThorVG（C++ 文件，可能不兼容）
set(LV_CONF_BUILD_DISABLE_THORVG_INTERNAL ON)

######################修改结束#############################################################################



# Build LVGL library
add_library(lvgl ${SOURCES})
add_library(lvgl::lvgl ALIAS lvgl)

target_compile_definitions(
  lvgl PUBLIC $<$<BOOL:${LV_LVGL_H_INCLUDE_SIMPLE}>:LV_LVGL_H_INCLUDE_SIMPLE>
              $<$<BOOL:${LV_CONF_INCLUDE_SIMPLE}>:LV_CONF_INCLUDE_SIMPLE>)

# Add definition of LV_CONF_PATH only if needed
if(LV_CONF_PATH)
  target_compile_definitions(lvgl PUBLIC LV_CONF_PATH=${LV_CONF_PATH})
endif()

# Add definition of LV_CONF_SKIP only if needed
if(LV_CONF_SKIP)
  target_compile_definitions(lvgl PUBLIC LV_CONF_SKIP=1)
endif()

# Include root and optional parent path of LV_CONF_PATH
target_include_directories(lvgl SYSTEM PUBLIC 
  ${LVGL_ROOT_DIR} 
  ${LV_CONF_DIR} 
  ${CMAKE_CURRENT_BINARY_DIR} 
)
#sul
# target_link_libraries(lvgl PUBLIC FatFs)

if(NOT LV_CONF_BUILD_DISABLE_THORVG_INTERNAL)
    add_library(lvgl_thorvg ${THORVG_SOURCES})
    add_library(lvgl::thorvg ALIAS lvgl_thorvg)
    target_include_directories(lvgl_thorvg SYSTEM PUBLIC ${LVGL_ROOT_DIR}/src/libs/thorvg)
    target_link_libraries(lvgl_thorvg PUBLIC lvgl)
endif()

if(NOT (CMAKE_C_COMPILER_ID STREQUAL "MSVC"))
  set_source_files_properties(${LVGL_ROOT_DIR}/src/others/vg_lite_tvg/vg_lite_tvg.cpp PROPERTIES COMPILE_FLAGS -Wunused-parameter)
endif()

# Build LVGL example library
if(NOT LV_CONF_BUILD_DISABLE_EXAMPLES)
    add_library(lvgl_examples ${EXAMPLE_SOURCES})
    add_library(lvgl::examples ALIAS lvgl_examples)

    target_include_directories(lvgl_examples SYSTEM PUBLIC ${LVGL_ROOT_DIR}/examples)
    target_link_libraries(lvgl_examples PUBLIC lvgl)
endif()

# Build LVGL demos library
if(NOT LV_CONF_BUILD_DISABLE_DEMOS)
    add_library(lvgl_demos ${DEMO_SOURCES})
    add_library(lvgl::demos ALIAS lvgl_demos)

    target_include_directories(lvgl_demos SYSTEM PUBLIC ${LVGL_ROOT_DIR}/demos)
    target_link_libraries(lvgl_demos PUBLIC lvgl)
endif()

# Library and headers can be installed to system using make install
file(GLOB LVGL_PUBLIC_HEADERS
    "${LVGL_ROOT_DIR}/lvgl.h"
    "${LVGL_ROOT_DIR}/lv_version.h")

if(NOT LV_CONF_SKIP)
  if (LV_CONF_PATH)
    list(APPEND LVGL_PUBLIC_HEADERS
    ${LV_CONF_PATH})
  else()
    list(APPEND LVGL_PUBLIC_HEADERS
    "${CMAKE_SOURCE_DIR}/lv_conf.h")
  endif()
endif()

if("${LIB_INSTALL_DIR}" STREQUAL "")
  set(LIB_INSTALL_DIR "lib")
endif()
if("${RUNTIME_INSTALL_DIR}" STREQUAL "")
  set(RUNTIME_INSTALL_DIR "bin")
endif()
if("${INC_INSTALL_DIR}" STREQUAL "")
  set(INC_INSTALL_DIR "include/lvgl")
endif()

#Install headers
install(
  DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/src"
  DESTINATION "${CMAKE_INSTALL_PREFIX}/${INC_INSTALL_DIR}/"
  FILES_MATCHING
  PATTERN "*.h")

# Install headers from the LVGL_PUBLIC_HEADERS variable
install(
  FILES ${LVGL_PUBLIC_HEADERS}
  DESTINATION "${CMAKE_INSTALL_PREFIX}/${INC_INSTALL_DIR}/"
)

# install example headers
if(NOT LV_CONF_BUILD_DISABLE_EXAMPLES)
  install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/examples"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/${INC_INSTALL_DIR}/"
    FILES_MATCHING
    PATTERN "*.h")
endif()

# install demo headers
if(NOT LV_CONF_BUILD_DISABLE_DEMOS)
  install(
    DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/demos"
    DESTINATION "${CMAKE_INSTALL_PREFIX}/${INC_INSTALL_DIR}/"
    FILES_MATCHING
    PATTERN "*.h")
endif()


configure_file("${LVGL_ROOT_DIR}/lvgl.pc.in" lvgl.pc @ONLY)
configure_file("${LVGL_ROOT_DIR}/lv_version.h.in" lv_version.h @ONLY)

install(
  FILES "${CMAKE_CURRENT_BINARY_DIR}/lvgl.pc"
  DESTINATION "${LIB_INSTALL_DIR}/pkgconfig/")

# Install library lvgl
set_target_properties(
  lvgl
  PROPERTIES OUTPUT_NAME lvgl
             VERSION ${LVGL_VERSION}
             SOVERSION ${LVGL_SOVERSION}
             ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
             PUBLIC_HEADER "${LVGL_PUBLIC_HEADERS}")

install(
  TARGETS lvgl
  ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
  LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
  RUNTIME DESTINATION "${RUNTIME_INSTALL_DIR}"
  PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}")


# Install library thorvg
if(NOT LV_CONF_BUILD_DISABLE_THORVG_INTERNAL)
  set_target_properties(
    lvgl_thorvg
    PROPERTIES OUTPUT_NAME lvgl_thorvg
               VERSION ${LVGL_VERSION}
               SOVERSION ${LVGL_SOVERSION}
               ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
               PUBLIC_HEADER "${LVGL_PUBLIC_HEADERS}")

  install(
    TARGETS lvgl_thorvg
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    RUNTIME DESTINATION "${RUNTIME_INSTALL_DIR}"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}")
endif()

# Install library demos
if(NOT LV_CONF_BUILD_DISABLE_DEMOS)
  set_target_properties(
    lvgl_demos
    PROPERTIES OUTPUT_NAME lvgl_demos
               VERSION ${LVGL_VERSION}
               SOVERSION ${LVGL_SOVERSION}
               ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lvgl_demo"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lvgl_demo"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lvgl_demo"
               PUBLIC_HEADER "${LVGL_PUBLIC_HEADERS}")

  install(
    TARGETS lvgl_demos
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    RUNTIME DESTINATION "${RUNTIME_INSTALL_DIR}"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}")
endif()

#install library examples
if(NOT LV_CONF_BUILD_DISABLE_EXAMPLES)
  set_target_properties(
    lvgl_examples
    PROPERTIES OUTPUT_NAME lvgl_examples
               VERSION ${LVGL_VERSION}
               SOVERSION ${LVGL_SOVERSION}
               ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
               RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
               PUBLIC_HEADER "${LVGL_PUBLIC_HEADERS}")

  install(
    TARGETS lvgl_examples
    ARCHIVE DESTINATION "${LIB_INSTALL_DIR}"
    LIBRARY DESTINATION "${LIB_INSTALL_DIR}"
    RUNTIME DESTINATION "${RUNTIME_INSTALL_DIR}"
    PUBLIC_HEADER DESTINATION "${INC_INSTALL_DIR}")
endif()
