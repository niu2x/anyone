add_library(anyone_base "")
anyone_init_cxx_target(anyone_base)

target_sources(anyone_base PRIVATE "ref.cpp")
target_include_directories(anyone_base PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)

target_link_libraries(anyone_base PUBLIC nx)



