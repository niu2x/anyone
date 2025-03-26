cmake_minimum_required(VERSION 3.13.0 FATAL_ERROR)

project ( Anyone VERSION "1.0.2" LANGUAGES CXX C ) 

# add_subdirectory(nx)
# add_subdirectory(freetype)
# find_package(Boost REQUIRED)

find_package(nx REQUIRED)
find_package(freetype REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)
include(warning_as_error)
include(CMakePackageConfigHelpers)

# warning_as_error_enable(anyone)

set(runtime "anyone_rt")

add_executable(${runtime} "")

anyone_init_cxx_target(${runtime})

add_subdirectory(src)

target_include_directories(${runtime} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>  
)

target_include_directories(${runtime} PRIVATE src/)

target_link_libraries(${runtime} PRIVATE
    nx
)

