add_library(anyone_platform_api "")
target_sources(anyone_platform_api PRIVATE "empty.cpp")
target_link_libraries(anyone_platform_api PUBLIC anyone_base)