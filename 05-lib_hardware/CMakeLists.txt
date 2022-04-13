cmake_minimum_required( VERSION 3.7.0)

project (HARDWARE)

set (PROJECT_VERSION_MAJOR 0)
set (PROJECT_VERSION_MINOR 1)
set (PROJECT_VERSION_PATCH 0)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_BUILD_TYPE Debug)

include(GNUInstallDirs)

function (add_test_unit BIN_NAME BIN SOURCE)
    add_executable(${BIN} ${SOURCE})
    set_target_properties(${BIN}
        PROPERTIES 
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}
    )

    add_test (NAME ${BIN_NAME} COMMAND ${BIN})
endfunction ()

enable_testing()

add_library(hardware SHARED "")
target_link_libraries(hardware PUBLIC wiringPi)
target_sources(hardware
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/button.c
    ${CMAKE_CURRENT_LIST_DIR}/src/gpio.c
    ${CMAKE_CURRENT_LIST_DIR}/src/led.c
    )
target_include_directories(hardware 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/include
    )

add_test_unit (test test_hardware unit_test/test.c)
target_link_libraries (test_hardware PUBLIC hardware)

install(FILES include/button.h  DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES include/led.h     DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES include/gpio.h    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install (TARGETS hardware LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})