function(warning_as_error_enable target)
	if (MSVC)
		# warning level 4 and all warnings as errors
		target_compile_options(${target} PRIVATE /W4 /WX)
	else()
		# lots of warnings and all warnings as errors
		# target_compile_options(${target} PRIVATE -Wall -Wextra -Wpedantic -Werror)
		target_compile_options(${target} PRIVATE -Wall -Wextra -Werror -Wno-undefined-var-template)
	endif()
endfunction()



function(anyone_init_cxx_target target) 
	set_target_properties(${target} PROPERTIES 
		CXX_STANDARD 17
		C_VISIBILITY_PRESET hidden
		CXX_VISIBILITY_PRESET hidden
		VISIBILITY_INLINES_HIDDEN ON
		POSITION_INDEPENDENT_CODE ON
	)
endfunction()