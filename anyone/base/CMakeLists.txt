add_library(anyone_base "")
target_sources(anyone_base PRIVATE "ref.cpp")
target_link_libraries(anyone_base PUBLIC nx)
anyone_init_cxx_target(anyone_base)

