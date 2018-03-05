# This is the CMakeList.txt file used to build the project
#    - We use this old version because it is the  -
#    -   latest version availale on Travis CI     -
cmake_minimum_required(VERSION 3.2)

# Read the file with the macro definitions which specify
# the behaviour specific to this project and then run
# the initialization macro
include(${CMAKE_SOURCE_DIR}/project.cmake)

# Add the 'cmake' directory in the project directory to the module path
set(CMAKE_MODULE_PATH "${CMAKE_MODULE_PATH};${CMAKE_SOURCE_DIR};${CMAKE_SOURCE_DIR}/.cmake")

# Load and run a macro to validate the initialization
include ("init_validate")
init_validate()

# Clear default install directory (user should use
# DESTDIR with make to set installation directory)
set( CMAKE_INSTALL_PREFIX "./" )

# Set default compilers; must come before project()
message(STATUS "")
message(STATUS "--- Configuring compiler ---")
message(STATUS "")
include ("compilers")
init_compilers()

# Declare the project name
project (${GBP_PROJECT_NAME})

# Compiler flags
set_compiler_flags()

# Validate compilers (minimum versions, etc)
validate_compilers()

message(STATUS "")
message(STATUS "--- Finished configuring compiler ---")
message(STATUS "")

# Load all macros and functions
message(STATUS "Loading macros & functions...")
include ("build")          # Main build macros
include ("3rd_party")      # 3rd party library support functions
include ("custom_targets") # Custom-target macros
message(STATUS "Done.")

# Generate compile commands.json file
# (needed by things like 'clang-tidy')
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# ===========================================
# Execute all project specific configurations
# (set options, library dependencies, etc.)
# ===========================================
project_options_and_dependencies()

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

# Enable testing
add_tests()

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
