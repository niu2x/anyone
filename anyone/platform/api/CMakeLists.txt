add_library(anyone_platform_api "")
anyone_init_cxx_target(anyone_platform_api)

target_sources(anyone_platform_api PRIVATE "support.cpp")

target_link_libraries(anyone_platform_api PUBLIC anyone_base)