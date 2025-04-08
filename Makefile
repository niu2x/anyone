build:
	./tools/build.sh

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

