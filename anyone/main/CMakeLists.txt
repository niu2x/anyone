add_library(anyone_main "")

file(GLOB_RECURSE src_files 
	"./*.cpp"
)

target_sources(anyone_main PRIVATE
	# ${src_files}
	core.cpp
	export_lua.cpp
)

target_include_directories(anyone_main PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(anyone_main PUBLIC 
	# glad
	tolua
	freetype
	anyone_base
	anyone_platform_api
)

anyone_init_cxx_target(anyone_main)

target_compile_definitions(anyone_main PUBLIC 
	ANYONE_TARGET_LINUX
)