#This is the CMakeList.txt file used by all gbpCode projects

cmake_minimum_required(VERSION 3.2)

#Include all the macros we will use
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/.cmake;${CMAKE_SOURCE_DIR}")
include("macros")

#Set default compilers(must come before project line)
set(CMAKE_C_COMPILER   "gcc")
set(CMAKE_CXX_COMPILER "g++")

# In case this is a TravisCI build, we need to add our 
# custom-installed MPI distribution to the search path
list(APPEND MPI_HINT_DIRS "${CMAKE_SOURCE_DIR}/mpich" )

#Declare the project name
project (gbpCode)

#Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
set(CMAKE_CXX_FLAGS "-std=c++11")

#The following line is needed to deal with this annoying problem:
#https: // developers.redhat.com/blog/2015/02/05/gcc5-and-the-c11-abi/
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

#Uncomment for a verbose run
#set(CMAKE_VERBOSE_MAKEFILE ON)

#Generate compile commands.json file
#(nneded by things like clang - tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#Use double precision liberally ?
option(USE_DOUBLE "Use double liberally" OFF)
if(USE_DOUBE)
    add_definitions(-DUSE_DOUBLE)
endif()

#== == == == == = Add 3rd - party libraries == == == == == =
message(STATUS "")
message(STATUS "Initializing 3rd-party libraries...")

#MPI
option(USE_MPI "Use MPI" OFF)
if(USE_MPI)
    add_definitions(-DUSE_MPI)
    find_package(MPI REQUIRED)
    include_directories(${MPI_INCLUDE_PATH})
    link_libraries(${MPI_C_LIBRARIES})
endif()

#CUDA & CUFFT
#Note that the CUDA version should be >= 7.5
#because c++ 11 support is needed !
option(USE_CUDA "Use CUDA" OFF)
if(USE_CUDA)
    find_package(CUDA REQUIRED)
    add_definitions(-DUSE_CUDA)
    option(USE_CUFFT "Use cuFFT" OFF)
    if(USE_CUFFT)
        add_definitions(-DUSE_CUFFT)
    endif()

    #Collect CUDA source code
    file(GLOB SOURCES_CU core/*.cu *.hh)
    set(SOURCES ${SOURCES_C} ${SOURCES_CU})

    # Pass options to NVCC
    set(CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
    set(CUDA_PROPAGATE_HOST_FLAGS ON)
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_30")

    ################################################################################
    # This ugly hack is needed to work around a bug in the fftw3.h header file
    #    see the following for a discussion: https://github.com/FFTW/fftw3/issues/18
    set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -D__INTEL_COMPILER")
    ################################################################################

    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUDA_C_FLAGS}")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUDA_EXE_LINKER_FLAGS}")

    ## Add an executable to the project
    #cuda_add_executable(target ${SOURCES})

    ## CUFFT
    #if(USE_CUFFT)
    #    CUDA_ADD_CUFFT_TO_TARGET(target)
    #endif()
endif()
message(STATUS "Finished initializeing 3rd-party libraries.")
message(STATUS "")
# ======= End of 3rd party initialization =======

# ============= Process the project =============
# (look in .cmake/macros.cmake for these functions)
process_headers( ${CMAKE_SOURCE_DIR} )
process_targets( ${CMAKE_SOURCE_DIR} )

# =========== Add some custom targets ===========
message(STATUS "")
message(STATUS "Adding custom targets...")

# Create a master list of all source and header files
set(ALL_FILES_PROJECT "" )
list(APPEND ALL_FILES_PROJECT ${INC_FILES_PROJECT} )
list(APPEND ALL_FILES_PROJECT ${SRC_FILES_PROJECT} )

# Clang-format
message(STATUS "  -> clang-format")
add_custom_target(
        clang-format
        COMMAND clang-format
        -style=file
        -i
        ${ALL_FILES_PROJECT}
)

# Clang-tidy
message(STATUS "  -> clang-tidy-suggest")
add_custom_target(
        clang-tidy-suggest
        COMMAND clang-tidy
        -p ${CMAKE_CURRENT_BINARY_DIR}
        ${SRC_FILES_PROJECT}
)
message(STATUS "  -> clang-tidy-fix")
add_custom_target(
        clang-tidy-fix
        COMMAND clang-tidy
        -p ${CMAKE_CURRENT_BINARY_DIR}
        -fix
        ${SRC_FILES_PROJECT}
)

message(STATUS "Finished initializing custom targets.")
message(STATUS "")
# ============ End of custom targets ============

