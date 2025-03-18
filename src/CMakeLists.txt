add_subdirectory(lua)
add_subdirectory(tolua)
add_subdirectory(main)
add_subdirectory(platform/linux)

target_sources(${runtime} PRIVATE
	"version.cpp"
)

target_link_libraries(${runtime} PRIVATE 
	main
	platform_linux
	glad
)

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
	# target_link_libraries(${runtime} PRIVATE 
	# 	GL
	# )
endif()


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	target_link_libraries(${runtime} PRIVATE 
		GL
	)
endif()


