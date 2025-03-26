build:
	./tools/build_cmake_project.sh freetype
	./tools/build_cmake_project.sh nx -DNX_STATIC=ON
	cmake -S. -Bbuild -DCMAKE_BUILD_TYPE=Debug -Dnx_DIR=./dist/lib/cmake/niu2x -Dfreetype_DIR=./dist/lib/cmake/freetype
	cmake --build build -j 2

update_version:
	change-version Node cmd_tools/package.json -i -v $(version)
	change-version CMake CMakeLists.txt -i -v $(version)

tolua++:
	tolua++5.1 -L src/main/basic.lua -o src/main/export_lua.cpp src/main/anyone.pkg

update-nx:
	cd nx && git fetch --all && git checkout origin/develop
	git add nx

.PHONY: build

