add_library(lua "")
file(GLOB src_files "*.c")
target_sources(lua PRIVATE ${src_files})
target_include_directories(lua PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})