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
project (gbpSID)

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

# Doxygen
# TODO: Add a cmake version check here (needs to be 3.9)
# TODO: Add checks to make sure all doc build tools are found (Doxygen, Breathe, Sphinx, pdflatex)
# TODO: Dont add custom targets if they are not found
find_package(Doxygen REQUIRED)

# Sphinx
find_package(Sphinx REQUIRED)

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
add_custom_target(
    clang-format
    COMMAND clang-format
    -style=file
    -i
    ${ALL_FILES_PROJECT}
)
message(STATUS "  -> clang-format       ; apply the project style standards using clang-tidy")

# Clang-tidy
add_custom_target(
    clang-tidy-suggest
    COMMAND clang-tidy
    -p ${CMAKE_CURRENT_BINARY_DIR}
    ${SRC_FILES_PROJECT}
)
message(STATUS "  -> clang-tidy-suggest ; write clang-tidy suggestions to stdout")
add_custom_target(
    clang-tidy-fix
    COMMAND clang-tidy
    -p ${CMAKE_CURRENT_BINARY_DIR}
    -fix
    ${SRC_FILES_PROJECT}
)
message(STATUS "  -> clang-tidy-fix     ; apply all clang-tidy suggestions in-place ... BE CAREFUL WITH THIS!")

# Generate the overall project documentation with Sphinx
add_custom_target(
    docs-breathe
    COMMAND mkdir -p ${SPHINX_BUILD_DIR}/breathe
    COMMENT "Perform initialization for Breathe")
add_custom_target(
    docs-html 
    COMMAND ${SPHINX_EXECUTABLE}
        -q -b html 
        -c "${SPHINX_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${SPHINX_RESULTS_DIR}/html"
    COMMENT "Building HTML documentation with Sphinx")
message(STATUS "  -> docs-html          ; generate HTML version of project documentation using Doxygen and Sphinx")
add_custom_target(
    docs-pdf
    COMMAND ${SPHINX_EXECUTABLE}
        -q -b latex
        -c "${SPHINX_BUILD_DIR}"
        -d "${SPHINX_CACHE_DIR}"
        "${CMAKE_CURRENT_SOURCE_DIR}"
        "${SPHINX_LATEX_DIR}"
    COMMAND mkdir -p ${SPHINX_RESULTS_DIR}
    COMMAND echo ${SPHINX_RESULTS_DIR}
    COMMAND cd ${SPHINX_LATEX_DIR} && pdflatex ${CMAKE_PROJECT_NAME}
    COMMAND mv "${SPHINX_LATEX_DIR}/${CMAKE_PROJECT_NAME}.pdf" ${SPHINX_RESULTS_DIR}
    COMMENT "Building PDF documentation with Sphinx")
message(STATUS "  -> docs-pdf           ; generate PDF version of project documentation using Doxygen and Sphinx")

# Generate Doxygen documentation for C/C++ code
set(DOXYGEN_GENERATE_XML   YES)
set(DOXYGEN_GENERATE_LATEX  NO)
set(DOXYGEN_GENERATE_HTML   NO)
set(DOXYGEN_GENERATE_MAN    NO)
set(DOXYGEN_OUTPUT_DIRECTORY ${SPHINX_BUILD_DIR}/doxygen )
doxygen_add_docs(docs-doxygen ${ALL_FILES_PROJECT} )
add_dependencies(docs-html docs-doxygen )
add_dependencies(docs-pdf docs-doxygen )
add_dependencies(docs-doxygen docs-breathe )

message(STATUS "Finished initializing custom targets.")
message(STATUS "")
# ============ End of custom targets ============

