# This package file was obtained from a blog entry by Eric Scott Barr here:
#   https://eb2.co/blog/2012/03/sphinx-and-cmake-beautiful-documentation-for-c---projects/

find_program(Sphinx_EXECUTABLE NAMES sphinx-build
    HINTS
    $ENV{Sphinx_DIR}
    PATH_SUFFIXES bin
    DOC "Sphinx documentation generator"
)

# Handle REQUIRED, QUIET and set <packagename>_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Sphinx DEFAULT_MSG
    Sphinx_EXECUTABLE
)

# Pass an optional theme
if(NOT DEFINED Sphinx_THEME)
    set(Sphinx_THEME default)
endif()
 
# Pass an optional theme location
if(NOT DEFINED Sphinx_THEME_DIR)
    set(Sphinx_THEME_DIR)
endif()
 
# Configured documentation tools, intermediate build results, etc.
set(Sphinx_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build-docs")
set(Sphinx_LATEX_DIR "${Sphinx_BUILD_DIR}/latex")
 
# Sphinx cache with pickled ReST documents
set(Sphinx_CACHE_DIR "${Sphinx_BUILD_DIR}/sphinx_cache")
 
# Directory where all final generated documents will be stored
set(Sphinx_RESULTS_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

# Perform variable substitution into the Sphinx config file
set(PRJ_DOCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs )
configure_file(
    "${PRJ_DOCS_DIR}/conf.py"
    "${Sphinx_BUILD_DIR}/conf.py"
    @ONLY)

SET(Sphinx_EXECUTABLE  "${Sphinx_EXECUTABLE}"   CACHE INTERNAL "Sphinx executable")
SET(Sphinx_BUILD_DIR   "${Sphinx_BUILD_DIR}"    CACHE INTERNAL "Sphinx build directory")
SET(Sphinx_LATEX_DIR   "${Sphinx_LATEX_DIR}"    CACHE INTERNAL "Sphinx latex build directory")
SET(Sphinx_CACHE_DIR   "${Sphinx_CACHE_DIR}"    CACHE INTERNAL "Sphinx cache directory")
SET(Sphinx_RESULTS_DIR "${Sphinx_RESULTS_DIR}"  CACHE INTERNAL "Sphinx results directory")
SET(PRJ_DOCS_DIR       "${PRJ_DOCS_DIR}"        CACHE INTERNAL "Documentation root source directory")

