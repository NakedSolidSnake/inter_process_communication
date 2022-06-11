add_library(fifo "")

target_sources(fifo 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/fifo.c 
)

target_include_directories(fifo 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/
)