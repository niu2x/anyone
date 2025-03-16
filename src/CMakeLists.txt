file(GLOB_RECURSE src_files 
	"platform/linux/*.cpp"
	"main/*.cpp"
)

add_subdirectory(glad)

target_sources(${runtime} PRIVATE
	${src_files}
)


find_package(SDL2 REQUIRED)
target_link_libraries(${runtime} PRIVATE 
	SDL2
	GL
	glad
)

