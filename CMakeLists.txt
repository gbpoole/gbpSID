# This is the CMakeList.txt file used to build the project
#    - We use this old version because it is the  -
#    -   latest version availale on Travis CI     -
cmake_minimum_required(VERSION 3.2)

# Read the file with the macro definitions which specify
# the behaviour specific to this project and then run
# the initialization macro
include(${CMAKE_SOURCE_DIR}/project.cmake)

# Check that the relative path (from the main project directory)
# to gbpBuild has been defined by project.cmake
if(NOT GBPBUILD_REL_PATH)
    message( FATAL_ERROR "GBPBUILD_REL_PATH has not been set by project.cmake")
endif()

# Add the 'cmake' directory in the project directory to the module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR};${CMAKE_SOURCE_DIR}/cmake")
message(STATUS "${CMAKE_MODULE_PATH}")

# Load and run a macro to validate the initialization
include ("init_validate")
init_validate()

# Declare the project name
project (${GBP_PROJECT_NAME})

# Clear default install directory (user should use
# DESTDIR with make to set installation directory)
set( CMAKE_INSTALL_PREFIX "./" )

# Set default compilers(must come before project line)
set(CMAKE_C_COMPILER   "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
set(CMAKE_CXX_STANDARD 11)

# Set the location of the gbpBuild submodule
set(GBP_BUILD_DIR "${CMAKE_SOURCE_DIR}/${GBPBUILD_REL_PATH}/" )

# Load all macros and functions
message(STATUS "Loading macros & functions...")
include ("build")          # Main build macros
include ("3rd_party")      # Party library support functions
include ("custom_targets") # Custom-target macros
message(STATUS "Done.")

# The following line is needed to deal with this annoying problem:
# https: // developers.redhat.com/blog/2015/02/05/gcc5-and-the-c11-abi/
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0")

# Generate compile commands.json file
# (needed by things like clang - tidy)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Initialize &/or build any needed external libraries.  This
# needs to be done before including 'project.cmake' because we
# need to make sure that 'gbpBuild' has been cloned, for example.
process_externs( ${CMAKE_SOURCE_DIR} )

# ===========================================
# Execute all project specific configurations
# (set options, library dependencies, etc.)
# ===========================================
project_options_and_dependancies()
# ===========================================

# ============= Process the project =============
# (look in cmake/build.cmake for these functions)

# Generate the list of directories where header files
# are located, as well as a list of all header files
process_headers( ${CMAKE_SOURCE_DIR} )

# Generate all library and executable targets
process_targets( ${CMAKE_SOURCE_DIR} )

# ============= Add custom targets ==============
# (look in cmake/custom_targets.cmake for these functions)

# Print status message
message(STATUS "")
message(STATUS "Adding custom targets...")

# Add clang-format, clang-tidy, etc
add_custom_clang()

# Add documentation build
add_custom_docs()

# Print status message
message(STATUS "Finished initializing custom targets.")
message(STATUS "")
