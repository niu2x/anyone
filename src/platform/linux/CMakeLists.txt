add_subdirectory(glad)

add_library(platform_linux "")

target_sources(platform_linux PRIVATE
	main.cpp
	platform_linux.cpp
)

target_link_libraries(platform_linux PUBLIC
	glad
	main
	dl
)

anyone_init_cxx_target(platform_linux)

