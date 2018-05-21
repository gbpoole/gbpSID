# This is the CMakeList.txt file used to build the project
#    - We use this old version because it is the  -
#    -   latest version availale on Travis CI     -
cmake_minimum_required(VERSION 3.8)

# ==== Set paths ====
# Add the 'cmake' directory in the project directory to the module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR};${CMAKE_SOURCE_DIR}/.cmake")

# Clear default install directory (user should use
# DESTDIR with make to set installation directory)
set( CMAKE_INSTALL_PREFIX "./" )
# ===================

# Load all macros and functions
message(STATUS "Loading macros & functions...")
include ("validate_project") # Project validation and initialization macros
include ("compilers")        # Compiler set-up macros
include ("3rd_party")        # 3rd party library support functions
include ("build")            # Main build macros
include ("custom_targets")   # Custom-target macros
message(STATUS "Done.")

# Initialize this project
include ("project")
validate_project( )

# Add a couple common library prefix paths
list(APPEND CMAKE_PREFIX_PATH $ENV{HOME})
list(APPEND CMAKE_PREFIX_PATH $ENV{HOME}/my_code)
list(APPEND CMAKE_PREFIX_PATH $ENV{HOME}/3rd_Party)

# For some reason, find_path does not search these paths ... add them.
list(APPEND CMAKE_INCLUDE_PATH $ENV{CPATH})
list(APPEND CMAKE_INCLUDE_PATH $ENV{INCLUDE})

# Set default compilers; must come before project()
init_compilers()

# Declare the project name
project (${_PROJECT_NAME})

# Validate compilers (minimum versions, etc)
validate_compilers()

# Compiler flags
set_compiler_flags()

# Generate compile commands.json file
# (needed by things like 'clang-tidy')
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===========================================
# Execute all project specific configurations
# (set options, library dependencies, etc.)
# These should be defined in a 'project.cmake'
# file.
# ===========================================
process_options( ${CMAKE_SOURCE_DIR} )
process_dependencies( ${CMAKE_SOURCE_DIR} )

# ====================================================
# Initialize &/or build any needed external libraries.
# ====================================================
process_externs( ${CMAKE_SOURCE_DIR} )

# ===================
# Process the project
# ===================
# (look in cmake/build.cmake for these functions)

# Generate the list of directories where header files
# are located, as well as a list of all header files
process_headers( ${CMAKE_SOURCE_DIR} )

# Generate all library and executable targets
process_targets( ${CMAKE_SOURCE_DIR} )

# Enable testing (defined in 'tests.cmake'; no tests if absent)
process_tests( ${CMAKE_SOURCE_DIR} )

# ==================
# Add custom targets 
# ==================
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
