add_library(anyone_platform_darwin "")
anyone_init_cxx_target(anyone_platform_darwin)

find_package(SDL2 REQUIRED)

target_sources(anyone_platform_darwin PRIVATE
	support.cpp
	render_api.cpp
)


target_link_libraries(anyone_platform_darwin PUBLIC
	anyone_platform_api
	dl
	${SDL2_LIBRARIES}
)

target_include_directories(anyone_platform_darwin PUBLIC
	${SDL2_INCLUDE_DIRS}
)
target_link_directories(anyone_platform_darwin PUBLIC ${SDL2_LIBRARY_DIRS})
