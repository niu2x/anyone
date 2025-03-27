add_subdirectory(glad)

add_library(anyone_platform_linux "")

target_sources(anyone_platform_linux PRIVATE
	support.cpp
	render_api.cpp
	# main.cpp
	# anyone_platform_linux.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(anyone_platform_linux PUBLIC
	anyone_platform_api
	glad
	dl
	SDL2
)

anyone_init_cxx_target(anyone_platform_linux)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	target_include_directories(anyone_platform_linux PUBLIC
		${SDL2_INCLUDE_DIRS}
	)
	target_link_directories(anyone_platform_linux PUBLIC ${SDL2_LIBDIR})
endif()
