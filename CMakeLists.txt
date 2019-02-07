cmake_minimum_required(VERSION 3.7 FATAL_ERROR )

############################################################################

option(CREATE_PHYS_LIB "Create library and not tests" OFF)

##########################################################################

if( NOT CREATE_PHYS_LIB )

	option(USE_CLANG "Use clang to build" OFF)

	# set w/ -DUSE_CLANG=ON
	# doesn't work unfortunately
	if(USE_CLANG)
		find_package(LLVM REQUIRED CONFIG)

		set(CMAKE_C_COMPILER clang)

		# fixes cmake warnings
		SET_PROPERTY(GLOBAL PROPERTY TARGET_SUPPORTS_SHARED_LIBS TRUE)

		message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
		message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
	endif(USE_CLANG)

############################################################################

	project (Physics)

############################################################################

	# configure build locations to be: /bin & /lib on all platforms 
	if(CMAKE_CONFIGURATION_TYPES)
		set(CMAKE_CONFIGURATION_TYPES Release RelWithDebInfo MinSizeRel Debug)
		set(CMAKE_CONFIGURATION_TYPES "${CMAKE_CONFIGURATION_TYPES}" CACHE STRING
			"Reset the configurations"
			FORCE)
	endif(CMAKE_CONFIGURATION_TYPES)

	# set output directories
	set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
	set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

	foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
		string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
			set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} 
					${PROJECT_SOURCE_DIR}/bin )
			set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} 
					${PROJECT_SOURCE_DIR}/lib )
			set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} 
					${PROJECT_SOURCE_DIR}/lib )
	endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

	# Json file of project structure for editors
	set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

###########################################################################

	# set compiler flags on all platforms

	set(CMAKE_C_STANDARD 11)

	include(CheckCCompilerFlag)
	check_c_compiler_flag(-Wall HAS_WALL)
	if( MSVC )
		check_c_compiler_flag(/O2 HAS_OPT2)
		check_c_compiler_flag(/O1 HAS_OPT1)
		check_c_compiler_flag(/Os HAS_OPT0S)
	else()
		check_c_compiler_flag(-O3 HAS_OPT3)
		check_c_compiler_flag(-O2 HAS_OPT2)
		check_c_compiler_flag(-Os HAS_OPT0S)
		check_c_compiler_flag(-g HAS_DEBUG)
	endif( MSVC )

###########################################################################

	# windows warnings
	if(MSVC)
		add_definitions("-D_CRT_SECURE_NO_WARNINGS")
	endif(MSVC)

###########################################################################

	set( HEADERS 
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsStructs.h"
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsInterface.h"
		"${CMAKE_CURRENT_LIST_DIR}/SimpleAssert.h"
		"${CMAKE_CURRENT_LIST_DIR}/stretchy_buffer.h"
		"${CMAKE_CURRENT_LIST_DIR}/BVH.h"
	)

	set( SOURCES
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsStructs.c"
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsInterface.c"
		"${CMAKE_CURRENT_LIST_DIR}/stretchy_buffer.c"
		"${CMAKE_CURRENT_LIST_DIR}/BVH.c"
	)

	if( MSVC )
		set( HEADERS ${HEADERS} "${CMAKE_CURRENT_LIST_DIR}/.clang-format" )
	endif( MSVC )

##########################################################################

	# run tests
	message( "\n--> Compiling physics library tests <--\n" )

	if( MSVC )
		add_executable( run_tests "${CMAKE_CURRENT_LIST_DIR}/tests.c" ${SOURCES} ${HEADERS} )
	else()
		add_executable( run_tests "${CMAKE_CURRENT_LIST_DIR}/tests.c" ${SOURCES} )
	endif( MSVC )

	target_include_directories( run_tests PRIVATE "${CMAKE_CURRENT_LIST_DIR}" )

	target_compile_options( run_tests PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX /Qvec-report:2 $<$<CONFIG:DEBUG>:/Od> $<$<CONFIG:RELEASE>:/O2> $<$<CONFIG:MINSIZEREL>:/Os> $<$<CONFIG:RELWITHDEBINFO>:/O1>> )
	target_compile_options( run_tests PRIVATE $<$<C_COMPILER_ID:CLANG>:-Wall -Werror -Wpedantic -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize $<$<CONFIG:DEBUG>:-ggdb> $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:MINSIZEREL>:-Os> $<$<CONFIG:RELWITHDEBINFO>:-O2 -ggdb> > )
	target_compile_options( run_tests PRIVATE $<$<C_COMPILER_ID:GNU>:-Wall -Werror -Wpedantic -no-pie -ftree-vectorize -fopt-info-vec-optimized -fopt-info-vec-missed $<$<CONFIG:DEBUG>:-ggdb> $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:MINSIZEREL>:-Os> $<$<CONFIG:RELWITHDEBINFO>:-O2 -ggdb> > )

	target_link_libraries( run_tests PRIVATE $<$<C_COMPILER_ID:GNU>:-lm> )
	target_link_libraries( run_tests PRIVATE $<$<C_COMPILER_ID:CLANG>:-lm> )

	# set visual studio startup project
	set_property(DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
				PROPERTY VS_STARTUP_PROJECT
				run_tests )

###########################################################################

	# clang-format
	if( UNIX )
		add_custom_target(
			cfmt_pl
			COMMAND /usr/bin/clang-format
			-style=file
			-i
			${HEADERS}
			${SOURCES}
		)
	endif( UNIX )

else()

	# create library
	message( "\n--> Compiling physics library <--\n" )

	set( SOURCES
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsStructs.c"
		"${CMAKE_CURRENT_LIST_DIR}/PhysicsInterface.c"
	)

	add_library( physics_lib SHARED ${SOURCES} )

	target_include_directories( physics_lib PRIVATE "${CMAKE_CURRENT_LIST_DIR}" )

	target_compile_definitions( physics_lib PRIVATE "_CRT_SECURE_NO_WARNINGS" )

	target_compile_options( physics_lib PRIVATE $<$<C_COMPILER_ID:MSVC>:/W4 /WX /Qvec-report:2 $<$<CONFIG:DEBUG>:/Od> $<$<CONFIG:RELEASE>:/O2> $<$<CONFIG:MINSIZEREL>:/Os> $<$<CONFIG:RELWITHDEBINFO>:/O1>> )
	target_compile_options( physics_lib PRIVATE $<$<C_COMPILER_ID:CLANG>:-Wall -Werror -Wpedantic -Rpass=loop-vectorize -Rpass-missed=loop-vectorize -Rpass-analysis=loop-vectorize $<$<CONFIG:DEBUG>:-ggdb> $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:MINSIZEREL>:-Os> $<$<CONFIG:RELWITHDEBINFO>:-O2 -ggdb> > )
	target_compile_options( physics_lib PRIVATE $<$<C_COMPILER_ID:GNU>:-Wall -Werror -Wpedantic -no-pie -ftree-vectorize -fopt-info-vec-optimized -fopt-info-vec-missed $<$<CONFIG:DEBUG>:-ggdb> $<$<CONFIG:RELEASE>:-O3> $<$<CONFIG:MINSIZEREL>:-Os> $<$<CONFIG:RELWITHDEBINFO>:-O2 -ggdb> > )

endif( NOT CREATE_PHYS_LIB )
