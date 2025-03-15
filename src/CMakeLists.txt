file(GLOB_RECURSE src_files "./*.cpp")

target_sources(${runtime} PRIVATE
	${src_files}
)