add_library(main "")

file(GLOB_RECURSE src_files 
	"./*.cpp"
)

target_sources(main PRIVATE
	${src_files}
)

target_include_directories(main PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(main PUBLIC nx)

anyone_init_cxx_target(main)