#!/bin/bash

# stop current process if any child process fail.
set -e


# slient pushd，popd
pushd() {
	command pushd "$@" > /dev/null
}

popd() {
	command popd > /dev/null
}


# log
log() {
	echo "[LOG]:" "$@" >&2
}


# assert not empty
assert_not_empty() {
	if [ -z "${!1}" ]; then
		abort "$1 is empty";
	fi
}


# abort
abort() {
	log "[ABORT]" "$@"
	exit 1
}

die() {
	abort "$*"
}

# project_dir=$(dirname $0)