build:
	cmake -S. -Bbuild 
	cmake --build build -j 2

.PHONY: build

