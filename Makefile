build:
	./tools/build_cmake_project.sh freetype
	./tools/build_cmake_project.sh nx -DNX_STATIC=ON
	cmake -S anyone -B build/anyone -DCMAKE_BUILD_TYPE=Debug \
									-Dnx_DIR=$(PWD)/dist/lib/cmake/niu2x \
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

.PHONY: build

