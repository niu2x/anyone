#!/bin/bash

project_dir=$(dirname $0)
source ${project_dir}/nxsh.sh

project=${1}

# echo ${@: 2};

log "build cmake project ${project}"
log "pass through args: ${@: 2}"

get_job_num() {
	os_name=$(uname)
	# 判断是否是 macOS
	if [ "$os_name" = "Darwin" ]; then
		sysctl -n hw.ncpu
	else
		nproc
	fi
}

cpu_core=$(expr $(get_job_num) - 1)

cmake -S ${project} -B build/${project} \
	-DCMAKE_BUILD_TYPE=Release \
	-DBUILD_SHARED_LIBS=ON ${@: 2}
cmake --build build/${project} -j ${cpu_core}
cmake --install build/${project} --prefix dist