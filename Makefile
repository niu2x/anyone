build:
	cmake -S. -Bbuild -DBoost_DIR=/home/niu2x/project/boost/dist/linux/lib/cmake/Boost-1.84.0
	cmake --build build -j 2

.PHONY: build

