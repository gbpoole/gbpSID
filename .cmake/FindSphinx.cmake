# This package file was obtained from a blog entry by Eric Scott Barr here:
#   https://eb2.co/blog/2012/03/sphinx-and-cmake-beautiful-documentation-for-c---projects/

find_program(SPHINX_EXECUTABLE NAMES sphinx-build
    HINTS
    $ENV{SPHINX_DIR}
    PATH_SUFFIXES bin
    DOC "Sphinx documentation generator"
)
 
include(FindPackageHandleStandardArgs)
 
find_package_handle_standard_args(Sphinx DEFAULT_MSG
    SPHINX_EXECUTABLE
)

if(NOT DEFINED SPHINX_THEME)
    set(SPHINX_THEME default)
endif()
 
if(NOT DEFINED SPHINX_THEME_DIR)
    set(SPHINX_THEME_DIR)
endif()
 
# Configured documentation tools, intermediate build results, etc.
set(SPHINX_BUILD_DIR "${CMAKE_CURRENT_BINARY_DIR}/build-docs")
set(SPHINX_LATEX_DIR "${SPHINX_BUILD_DIR}/latex")
 
# Sphinx cache with pickled ReST documents
set(SPHINX_CACHE_DIR "${SPHINX_BUILD_DIR}/sphinx_cache")
 
# Directory where all final generated documents will be stored
set(SPHINX_RESULTS_DIR "${CMAKE_CURRENT_BINARY_DIR}/docs")

# Perform variable substitution into the Sphinx config file
set(PRJ_DOCS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/docs )
configure_file(
    "${PRJ_DOCS_DIR}/conf.py.in"
    "${SPHINX_BUILD_DIR}/conf.py"
    @ONLY)

mark_as_advanced(SPHINX_EXECUTABLE)

