build:
	./tools/build_cmake_project.sh RmlUi
	./tools/build_cmake_project.sh zlib -DZLIB_BUILD_STATIC=OFF
	./tools/build_cmake_project.sh kazmath -DKAZMATH_BUILD_TESTS=OFF \
											-DKAZMATH_BUILD_LUA_WRAPPER=OFF \
											-DKAZMATH_BUILD_JNI_WRAPPER=OFF \
											-DKAZMATH_BUILD_GL_UTILS=OFF \
											-DCMAKE_INSTALL_PREFIX=$(PWD)/dist
	./tools/build_cmake_project.sh libzip -DENABLE_OPENSSL=OFF \
											-DBUILD_TOOLS=OFF \
											-DZLIB_ROOT=$(PWD)/dist \
											-DBUILD_REGRESS=OFF \
											-DBUILD_OSSFUZZ=OFF \
											-DBUILD_EXAMPLES=OFF \
											-DBUILD_DOC=OFF
	./tools/build_cmake_project.sh assimp -DASSIMP_BUILD_TESTS=OFF \
											-DZLIB_DIR=$(PWD)/dist \
											-DZLIB_ROOT=$(PWD)/dist
	./tools/build_cmake_project.sh nx -DNX_STATIC=ON \
										-DNX_BUILD_LIBZIP=ON \
										-Dlibzip_DIR=$(PWD)/dist/lib/cmake/libzip/
	cmake -S anyone -B build/anyone -DCMAKE_BUILD_TYPE=Debug \
									-DBUILDING_DIST=$(PWD)/dist \
									-Dnx_DIR=$(PWD)/dist/lib/cmake/niu2x \
									-DRmlUi_DIR=$(PWD)/dist/lib/cmake/RmlUi \
									-Dlibzip_DIR=$(PWD)/dist/lib/cmake/libzip/ \
									-Dassimp_DIR=$(PWD)/dist/lib/cmake/assimp-5.4/ \
									-Dfreetype_DIR=$(PWD)/dist/lib/cmake/freetype
	cmake --build build/anyone -j 2

update_version:
	change-version Node cmd_tools/package.json -i -v $(version)
	change-version CMake CMakeLists.txt -i -v $(version)

tolua++:
	tolua++5.1 -L anyone/main/basic.lua -o anyone/main/export_lua.cpp anyone/main/anyone.pkg

update-nx:
	cd nx && git fetch --all && git checkout origin/develop
	git add nx

builtin.zip:
	rm -f ./builtin.zip;
	cd builtin && zip -r ../builtin.zip ./*

embed_builtin: builtin.zip
	bin2cpp builtin.zip builtin cpp
	mv builtin.h ./anyone/main/embed/
	mv builtin.cpp ./anyone/main/embed/
	rm -f builtin.zip

embed_font:
	bin2cpp SpaceMono-Regular.ttf SpaceMono_Regular cpp
	mv SpaceMono_Regular.h ./anyone/main/embed/
	mv SpaceMono_Regular.cpp ./anyone/main/embed/

embed: embed_builtin embed_font

.PHONY: build builtin.zip embed_builtin embed_font

