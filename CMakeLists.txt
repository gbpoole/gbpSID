# This is the CMakeList.txt file used to build the project
cmake_minimum_required(VERSION 3.2)

# Declare the project name
project (gbpSID)

# Set default compilers(must come before project line)
set(CMAKE_C_COMPILER   "gcc")
set(CMAKE_CXX_COMPILER "g++")

# Compiler flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=gnu99")
#set(CMAKE_CXX_FLAGS "-std=c++11")
set(CMAKE_CXX_STANDARD 11)

# Add the 'cmake' directory in the project directory to the module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR}/cmake;${CMAKE_SOURCE_DIR}")

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

# Use double precision liberally ?
option(USE_DOUBLE "Use double liberally" OFF)
if(USE_DOUBE)
    add_definitions(-DUSE_DOUBLE)
endif()

# Turn on debugging mode
option(SID_DEBUG "Enable SID debugging information" OFF)

# These options specify when (if ever) missing libraries
#   should be installed automatically by this build script
# !!! Not implemented yet
#option(INSTALL_FORCE   "Install all libraries automatically? (overrides INSTALL_MISSING)") 
#option(INSTALL_MISSING "Install missing libraries?") 

#=========== Add 3rd-party libraries ===========
# (look in .cmake/3rd_party.cmake for a list of supported libraries)
message(STATUS "")
message(STATUS "Initializing 3rd-party libraries...")

# List of *required* 3rd-Party libraries
#set_3rd_party_required("XXX")

# List of *requested* 3rd-Party libraries (and their defaults)
set_3rd_party_requested("GBP_DOCS_BUILD" ON)

# List of *optional* 3rd-Party libraries (and their defaults)
set_3rd_party_optional("MPI"    ON)
set_3rd_party_optional("MPI_IO" OFF)
set_3rd_party_optional("CUDA"   OFF)

# Print status message
message(STATUS "Finished initializing 3rd-party libraries.")

# ============= Process the project =============
# (look in cmake/build.cmake for these functions)

# Initialize &/or build any needed external libraries
process_externs( ${CMAKE_SOURCE_DIR} )

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

