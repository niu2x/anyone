cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project(Anyone VERSION 0.1.2 LANGUAGES CXX C)

add_subdirectory(nx)
find_package(Boost REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(warning_as_error)
include(CMakePackageConfigHelpers)

# warning_as_error_enable(anyone)

add_executable(anyone "")

set_target_properties(anyone PROPERTIES 
	CXX_STANDARD 17
	C_VISIBILITY_PRESET hidden
	CXX_VISIBILITY_PRESET hidden
	VISIBILITY_INLINES_HIDDEN ON
	POSITION_INDEPENDENT_CODE ON
)

add_subdirectory(src)

target_include_directories(anyone PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  
)

target_include_directories(anyone PRIVATE src/)

target_link_libraries(anyone PRIVATE
    nx
)