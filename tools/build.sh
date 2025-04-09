#!/bin/bash

project_dir=$(dirname $0)
source ${project_dir}/nxsh.sh

usage() { echo "Usage: $0 [-a]" 1>&2; exit 1; }

build_all=false

while getopts "a" o; do
    case "${o}" in
        a)
            # s=${OPTARG}
            build_all=true
            ;;
        *)
            usage
            ;;
    esac
done
shift $((OPTIND-1))

echo "build_all ${build_all}"


if [[ ${build_all} == true ]]; then

	./tools/build_cmake_project.sh RmlUi
	./tools/build_cmake_project.sh zlib -DZLIB_BUILD_STATIC=OFF
	./tools/build_cmake_project.sh kazmath -DKAZMATH_BUILD_TESTS=OFF \
											-DKAZMATH_BUILD_LUA_WRAPPER=OFF \
											-DKAZMATH_BUILD_JNI_WRAPPER=OFF \
											-DKAZMATH_BUILD_GL_UTILS=OFF \
											-DCMAKE_INSTALL_PREFIX=$(pwd)/dist
	./tools/build_cmake_project.sh libzip -DENABLE_OPENSSL=OFF \
											-DBUILD_TOOLS=OFF \
											-DZLIB_ROOT=$(pwd)/dist \
											-DBUILD_REGRESS=OFF \
											-DBUILD_OSSFUZZ=OFF \
											-DBUILD_EXAMPLES=OFF \
											-DBUILD_DOC=OFF
	./tools/build_cmake_project.sh assimp -DASSIMP_BUILD_TESTS=OFF \
											-DZLIB_DIR=$(pwd)/dist \
											-DZLIB_ROOT=$(pwd)/dist
	./tools/build_cmake_project.sh nx -DNX_STATIC=ON \
										-DNX_BUILD_LIBZIP=ON \
										-Dlibzip_DIR=$(pwd)/dist/lib/cmake/libzip/
fi;

cmake -S anyone -B build/anyone -DCMAKE_BUILD_TYPE=Debug \
								-DBUILDING_DIST=$(pwd)/dist \
								-Dnx_DIR=$(pwd)/dist/lib/cmake/niu2x \
								-DRmlUi_DIR=$(pwd)/dist/lib/cmake/RmlUi \
								-Dlibzip_DIR=$(pwd)/dist/lib/cmake/libzip/ \
								-Dassimp_DIR=$(pwd)/dist/lib/cmake/assimp-5.4/ \
								-Dfreetype_DIR=$(pwd)/dist/lib/cmake/freetype
cmake --build build/anyone -j 2

