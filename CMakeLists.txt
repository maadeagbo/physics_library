cmake_minimum_required(VERSION 3.7 FATAL_ERROR )

# on windows use -T "llvm"

############################################################################

option(USE_CLANG "Use clang to build" OFF)

# set w/ -DUSE_CLANG=ON
# doesn't work unfortunately
if(USE_CLANG)
	find_package(LLVM REQUIRED CONFIG)

	set(CMAKE_C_COMPILER clang)
	set(CMAKE_CXX_COMPILER clang++)

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
check_c_compiler_flag(-pedantic HAS_PEDANTIC)
check_c_compiler_flag(-O3 HAS_OPT3)
check_c_compiler_flag(-O2 HAS_OPT2)
check_c_compiler_flag(-Os HAS_OPT0S)
check_c_compiler_flag(-g HAS_DEBUG)

if( UNIX AND NOT USE_CLANG )
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -no-pie")
endif( UNIX AND NOT USE_CLANG )

if(HAS_WALL)
	if(MSVC)
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -W4 -WX")
	else()
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -Wall -Werror")
	endif(MSVC)
endif(HAS_WALL)

if(HAS_OPT0S)
	set(CMAKE_C_FLAGS_MINSIZEREL "${CMAKE_C_FLAGS_MINSIZEREL} -Os")
endif(HAS_OPT0S)

if(HAS_DEBUG)
	set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -g")
endif(HAS_DEBUG)

if(HAS_OPT3)
	set(CMAKE_C_FLAGS_RELEASE "${CMAKE_C_FLAGS_RELEASE} -O3")
endif(HAS_OPT3)

if(HAS_OPT2)
	set(CMAKE_C_FLAGS_RELWITHDEBINFO "${CMAKE_C_FLAGS_RELWITHDEBINFO} -O2")
endif(HAS_OPT2)

###########################################################################

# windows warnings
if(MSVC)
	add_definitions("-D_CRT_SECURE_NO_WARNINGS")
endif(MSVC)

###########################################################################

set( HEADERS 
	"${PROJECT_SOURCE_DIR}/PhysicsStructs.h"
	"${PROJECT_SOURCE_DIR}/PhysicsInterface.h"
	"${PROJECT_SOURCE_DIR}/SimpleAssert.h"
)

set( SOURCES
	"${PROJECT_SOURCE_DIR}/PhysicsStructs.c"
	"${PROJECT_SOURCE_DIR}/PhysicsInterface.c"
)

if( MSVC )
	set( HEADERS ${HEADERS} "${PROJECT_SOURCE_DIR}/.clang-format" )
endif( MSVC )

##########################################################################

option(CREATE_PHYS_LIB "Create library and not tests" OFF)

if( NOT CREATE_PHYS_LIB )

# run tests
message( "\n--> Compiling physics library tests <--\n" )

if( MSVC )
    add_executable( run_tests "${PROJECT_SOURCE_DIR}/tests.c" ${SOURCES} ${HEADERS} )
else()
    add_executable( run_tests "${PROJECT_SOURCE_DIR}/tests.c" ${SOURCES} )
endif( MSVC )

target_include_directories( run_tests PRIVATE "${PROJECT_SOURCE_DIR}" )

if( NOT MSVC )
target_link_libraries( run_tests PRIVATE "-lm")
endif( NOT MSVC )

# vectorization diagnostics
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
	target_compile_options( run_tests PRIVATE
		-Rpass=loop-vectorize
#		-Rpass-missed=loop-vectorize
#		-Rpass-analysis=loop-vectorize
	)
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
	target_compile_options( run_tests PRIVATE
		-ftree-vectorize
		-fopt-info-vec-optimized
#		-fopt-info-vec-missed
	)
elseif( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( run_tests PRIVATE
		"/Qvec-report:1"
#		"/Qvec-report:2"
	)
endif( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )

# set visual studio startup project
set_property(DIRECTORY ${PROJECT_SOURCE_DIR}
			PROPERTY VS_STARTUP_PROJECT
			run_tests )

else()

# create library
message( "\n--> Compiling physics library <--\n" )

add_library( physics_lib STATIC ${SOURCES} )

# vectorization diagnostics
if( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )
	target_compile_options( physics_lib PRIVATE -Rpass=loop-vectorize )
elseif( CMAKE_CXX_COMPILER_ID MATCHES "GNU" )
	target_compile_options( physics_lib PRIVATE
		-ftree-vectorize
		-fopt-info-vec-optimized
	)
elseif( CMAKE_CXX_COMPILER_ID MATCHES "MSVC" )
	target_compile_options( physics_lib PRIVATE "/Qvec-report:1" )
endif( CMAKE_CXX_COMPILER_ID MATCHES "Clang" )

# set visual studio startup project
set_property(DIRECTORY ${PROJECT_SOURCE_DIR}
			PROPERTY VS_STARTUP_PROJECT
			physics_lib )

endif( NOT CREATE_PHYS_LIB )

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
