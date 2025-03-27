add_subdirectory(glad)

add_library(anyone_platform_linux "")

target_sources(anyone_platform_linux PRIVATE
	support.cpp
	render_api.cpp
	../common/key_code_convert.cpp
)

find_package(SDL2 REQUIRED)

target_link_libraries(anyone_platform_linux PUBLIC
	anyone_platform_api
	anyone_main
	glad
	dl
	SDL2
)

anyone_init_cxx_target(anyone_platform_linux)

target_include_directories(anyone_platform_linux PUBLIC
	${SDL2_INCLUDE_DIRS}
)
target_link_directories(anyone_platform_linux PUBLIC ${SDL2__LIBRARY_DIRS})
