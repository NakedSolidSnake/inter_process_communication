add_library(shared_file "")

target_sources(shared_file 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/shared_file.c
)
target_include_directories(shared_file 
    PUBLIC 
    ${CMAKE_CURRENT_LIST_DIR}/
)