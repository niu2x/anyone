add_library(anyone_platform_darwin "")
anyone_init_cxx_target(anyone_platform_darwin)

find_package(SDL2 REQUIRED)

target_sources(anyone_platform_darwin PRIVATE
	support.cpp
	render_api.mm
	render_impl.m
	../common/key_code_convert.cpp
)


target_link_libraries(anyone_platform_darwin PUBLIC
	anyone_platform_api
	anyone_main
	dl
	${SDL2_LIBRARIES}
)

target_include_directories(anyone_platform_darwin PUBLIC
	${SDL2_INCLUDE_DIRS}
)
target_link_directories(anyone_platform_darwin PUBLIC ${SDL2_LIBRARY_DIRS})

target_compile_options(anyone_platform_darwin PRIVATE
    "-fobjc-arc"
)


find_library(METAL_FRAMEWORK Metal)
target_link_libraries(anyone_platform_darwin PUBLIC ${METAL_FRAMEWORK})

find_library(FOUNDATION_FRAMEWORK Foundation)
find_library(QUARTZCORE_FRAMEWORK QuartzCore)

target_link_libraries(anyone_platform_darwin PUBLIC
    ${METAL_FRAMEWORK}
    ${FOUNDATION_FRAMEWORK}
    ${QUARTZCORE_FRAMEWORK}
)