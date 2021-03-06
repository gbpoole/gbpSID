# This is the CMakeList.txt file used to build the project
#    - We use this old version because it is the  -
#    -   latest version availale on Travis CI     -
cmake_minimum_required(VERSION 3.8)

# ==== Set paths ====
# Add the 'cmake' directory in the project directory to the module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR};${CMAKE_SOURCE_DIR}/.cmake")

# Load all macros and functions
message(STATUS "Loading macros & functions...")
include ("validate_project") # Project validation and initialization macros
include ("compilers")        # Compiler set-up macros
include ("3rd_party")        # 3rd party library support functions
include ("build")            # Main build macros
include ("custom_targets")   # Custom-target macros
message(STATUS "Done.")

# Initialize this project (needs to come before project() to get _PROJECT_NAME)
include ("project")
validate_project( )

# Add a bunch of common library prefix paths from the environment
include ("init_paths")

# Set default compilers; must come before project()
init_compilers()

# ===================

# Declare the project name
project (${_PROJECT_NAME})

# Clear default install directory (user should use
# DESTDIR with make to set installation directory)
set( CMAKE_INSTALL_PREFIX "./" )

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
# file.  This needs to be done before 
# process_project() is called below to make
# sure that this project's environment
# variable settings take precidence.
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
process_project( ${CMAKE_SOURCE_DIR} FALSE)

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
