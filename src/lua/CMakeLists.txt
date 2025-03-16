add_library(lua "")
file(GLOB src_files "*.c")
target_sources(lua PRIVATE ${src_files})