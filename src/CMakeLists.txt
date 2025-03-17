add_subdirectory(lua)
add_subdirectory(tolua)
add_subdirectory(main)
add_subdirectory(platform/linux)

target_sources(${runtime} PRIVATE
	"version.cpp"
)


find_package(SDL2 REQUIRED)
target_link_libraries(${runtime} PRIVATE 
	main
	platform_linux
	glad
	SDL2
	GL
)

