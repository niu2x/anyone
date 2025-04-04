add_library(anyone_main "")

file(GLOB_RECURSE src_files 
	"./*.cpp"
)

target_sources(anyone_main PRIVATE
	# ${src_files}
	rml_ui.cpp
	core.cpp
	archive.cpp
	export_lua.cpp
	render_system.cpp
	model.cpp
	camera.cpp
	material.cpp
	model_manager.cpp

	embed/SpaceMono_Regular.cpp
	embed/builtin.cpp

	url-parser/url.cpp
)

target_include_directories(anyone_main PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
	${BUILDING_DIST}/include
)

target_link_libraries(anyone_main PUBLIC 
	# glad
	anyone_base
	anyone_platform_api
	RmlUi::RmlUi
	assimp::assimp
	# freetype
	tolua
	kazmath
)

target_link_directories(anyone_main PUBLIC
	${BUILDING_DIST}/lib
)

anyone_init_cxx_target(anyone_main)