add_subdirectory(glad)

add_library(platform_linux "")

target_sources(platform_linux PRIVATE
	main.cpp
	platform_linux.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(platform_linux PUBLIC
	glad
	main
	dl
	SDL2
)

anyone_init_cxx_target(platform_linux)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	target_include_directories(platform_linux PUBLIC
		${SDL2_INCLUDE_DIRS}
	)
	target_link_directories(platform_linux PUBLIC ${SDL2_LIBDIR})
endif()
