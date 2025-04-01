#!/bin/bash

project_dir=$(dirname $0)
source ${project_dir}/nxsh.sh

project=${1}

# echo ${@: 2};

log "build cmake project ${project}"
log "pass through args: ${@: 2}"

cpu_core=$(expr $(nproc) - 1)

cmake -S ${project} -B build/${project} \
	-DCMAKE_BUILD_TYPE=Release \
	-DBUILD_SHARED_LIBS=OFF ${@: 2}
cmake --build build/${project} -j ${cpu_core}
cmake --install build/${project} --prefix dist