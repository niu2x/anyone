add_executable(anyone_rt "")
target_sources(anyone_rt PRIVATE "main.cpp")
anyone_init_cxx_target(anyone_rt)
target_link_libraries(anyone_rt PRIVATE anyone_main)

