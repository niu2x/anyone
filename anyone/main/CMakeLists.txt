add_library(anyone_main "")

file(GLOB_RECURSE src_files 
	"./*.cpp"
)

find_package(libjpeg-turbo REQUIRED)

target_sources(anyone_main PRIVATE
	# ${src_files}
	rml_ui.cpp
	core.cpp
	archive.cpp
	render_system.cpp
	model.cpp
	scene_node.cpp
	scene_manager.cpp
	camera.cpp
	material.cpp
	model_manager.cpp
	attachment.cpp
	texture_loader.cpp
	
	tolua_support.cpp
	export_lua.cpp

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
	libjpeg-turbo::turbojpeg-static
)

target_link_directories(anyone_main PUBLIC
	${BUILDING_DIST}/lib
)

anyone_init_cxx_target(anyone_main)