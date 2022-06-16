cmake_minimum_required( VERSION 3.7.0)

project(IPC)

set (CMAKE_C_FLAGS "-D_GNU_SOURCE -Wall -std=c99")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set (LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)
set (CMAKE_BUILD_TYPE Debug)

if (DEFINED ARCH)
    if (${ARCH} STREQUAL "RASPBERRY")
        message("--Created ${ARCH} compilation.")
        set (LIBS hardware bussiness shared_file)
        set (FOLDER "raspberry")
    elseif (${ARCH} STREQUAL "PC")
        message ("-- Created ${ARCH} compilation.")
        set (LIBS bussiness shared_file)
        set (FOLDER "pc")    
    elseif (${ARCH} STREQUAL "DOCKER")
        message ("-- Created ${ARCH} compilation.")
        set (LIBS bussiness shared_file)
        set (FOLDER "docker")
    endif ()
else ()
    message(WARNING "")
    message("-- You must specify the ARCH variable")
    message("-- cmake -DARCH=PC ..")
    message("-- or")
    message("-- cmake -DARCH=DOCKER ..")
    message("-- or")
    message("-- cmake -DARCH=RASPBERRY ..")
    message("")
    message(FATAL_ERROR "")
endif ()

add_subdirectory(lib)

# bussiness library
add_library(bussiness "")
target_sources(bussiness 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/consumer.c
    ${CMAKE_CURRENT_LIST_DIR}/src/producer.c
    )
target_include_directories(bussiness 
    PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/lib
    )

install (TARGETS bussiness DESTINATION bin)

# launch_processes
add_executable(launch_processes "")
target_sources(launch_processes 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/launch_processes.c
    )
target_include_directories(launch_processes
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/lib
    ) 
install (TARGETS launch_processes DESTINATION bin)

# led_process
add_executable(led_process "")
target_link_libraries(led_process PUBLIC ${LIBS})
target_sources(led_process
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/led/led_process.c
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/led/led_main.c
    )
target_include_directories(led_process
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src/platform
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/led
    ) 
install (TARGETS led_process DESTINATION bin)

# button_process
add_executable(button_process "")
target_link_libraries(button_process PUBLIC ${LIBS})
target_sources(button_process
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/button/button_process.c
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/button/button_main.c
    )
target_include_directories(button_process
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/include
    ${CMAKE_CURRENT_LIST_DIR}/src/platform
    ${CMAKE_CURRENT_LIST_DIR}/src/platform/${FOLDER}/button
    ) 
install (TARGETS button_process DESTINATION bin)

file (COPY script/kill_application.sh DESTINATION bin)