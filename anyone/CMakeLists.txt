cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)
project ( Anyone VERSION "1.0.2" LANGUAGES CXX C )

find_package(nx REQUIRED)
find_package(freetype REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/../cmake)
include(warning_as_error)
include(CMakePackageConfigHelpers)


# set(runtime "anyone_rt")
# add_executable(${runtime} "")
# anyone_init_cxx_target(${runtime})

# target_include_directories(${runtime} PRIVATE
#     ${CMAKE_CURRENT_SOURCE_DIR}/
#     ${CMAKE_CURRENT_BINARY_DIR}/include
# )

add_subdirectory(3rd/lua)
add_subdirectory(3rd/tolua)

add_subdirectory(base)
add_subdirectory(main)
add_subdirectory(platform/api)
add_subdirectory(entry)


if("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
	add_subdirectory(platform/linux)
	target_compile_definitions(anyone_rt PRIVATE 
		ANYONE_TARGET_LINUX
	)
endif()
