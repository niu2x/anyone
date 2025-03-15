file(GLOB_RECURSE src_files "./*.cpp")

target_sources(anyone PRIVATE
	${src_files}
)