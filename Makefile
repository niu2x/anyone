build:
	cmake -S. -Bbuild -DBoost_DIR=/home/niu2x/project/boost/dist/linux/lib/cmake/Boost-1.84.0 -DCMAKE_BUILD_TYPE=Debug
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

