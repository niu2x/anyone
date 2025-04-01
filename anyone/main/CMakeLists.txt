add_library(anyone_main "")

file(GLOB_RECURSE src_files 
	"./*.cpp"
)

target_sources(anyone_main PRIVATE
	# ${src_files}
	rml_ui.cpp
	core.cpp
	archive.cpp
	color.cpp
	export_lua.cpp
	render_system.cpp
	mesh.cpp
	mesh_manager.cpp
	embed/SpaceMono_Regular.cpp
	embed/builtin.cpp
)

target_include_directories(anyone_main PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}
)

target_link_libraries(anyone_main PUBLIC 
	# glad
	anyone_base
	anyone_platform_api
	RmlUi::RmlUi
	assimp::assimp
	freetype
	tolua
)

anyone_init_cxx_target(anyone_main)