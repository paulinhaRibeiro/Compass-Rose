# Generated Cmake Pico project file

cmake_minimum_required(VERSION 3.13)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialise pico_sdk from installed location
# (note this can come from environment, CMake cache etc)

# == DO NOT EDIT THE FOLLOWING LINES for the Raspberry Pi Pico VS Code Extension to work ==
if(WIN32)
    set(USERHOME $ENV{USERPROFILE})
else()
    set(USERHOME $ENV{HOME})
endif()
set(sdkVersion 2.1.1)
set(toolchainVersion 14_2_Rel1)
set(picotoolVersion 2.1.1)
set(picoVscode ${USERHOME}/.pico-sdk/cmake/pico-vscode.cmake)
if (EXISTS ${picoVscode})
    include(${picoVscode})
endif()
# ====================================================================================
set(PICO_BOARD pico_w CACHE STRING "Board type")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(pico_sdk_import.cmake)

project(Project_Compass-Rose C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add executable. Default name is the project name, version 0.1

add_executable(Project_Compass-Rose Project_Compass-Rose.c 
                                        src_/joystick.c
                                        src_/page.c
                                        src_/server_http.c
                                        src_/wifi.c
)

pico_set_program_name(Project_Compass-Rose "Project_Compass-Rose")
pico_set_program_version(Project_Compass-Rose "0.1")

# Modify the below lines to enable/disable output over UART/USB
pico_enable_stdio_uart(Project_Compass-Rose 0)
pico_enable_stdio_usb(Project_Compass-Rose 1)

# Add the standard library to the build
target_link_libraries(Project_Compass-Rose
                        pico_stdlib
                        hardware_gpio
                        hardware_adc
                        pico_cyw43_arch_lwip_threadsafe_background
)

# Add the standard include files to the build
target_include_directories(Project_Compass-Rose PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        ${PICO_SDK_PATH}/lib/lwip/src/include
        ${PICO_SDK_PATH}/lib/lwip/src/include/arch
        ${PICO_SDK_PATH}/lib/lwip/src/include/lwip
        ${CMAKE_CURRENT_LIST_DIR}/include_headers
        ${CMAKE_CURRENT_LIST_DIR}/src_
)

target_sources(Project_Compass-Rose PRIVATE
    ${PICO_SDK_PATH}/lib/lwip/src/apps/http/httpd.c
    ${PICO_SDK_PATH}/lib/lwip/src/apps/http/fs.c
)

# Add any user requested libraries
target_link_libraries(Project_Compass-Rose 
)

pico_add_extra_outputs(Project_Compass-Rose)

