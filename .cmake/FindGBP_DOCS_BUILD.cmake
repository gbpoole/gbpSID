# - Find GBP_DOCS_BUILD

# This will look for all the libraries needed
# to build Doxygen/Sphinx documentation.

# We need version >= 3.9 to have access to the
# doxygen_add_docs() function, which we will
# want to use later.
if(${CMAKE_VERSION} VERSION_LESS "3.9.0")
    message(WARNING "CMake needs to be version >= 3.9 to build documentation.  Doc generation will not be supported.")
else()
    # Doxygen
    find_package(Doxygen)

    # Sphinx
    find_package(Sphinx)
endif()

# Handle REQUIRED, QUIET and set <packagename>_FOUND
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(GBP_DOCS_BUILD DEFAULT_MSG
    DOXYGEN_FOUND
    Sphinx_FOUND
)
SET(GBP_DOCS_BUILD_FOUND "${GBP_DOCS_BUILD_FOUND}" CACHE INTERNAL "GBP_DOCS_BUILD_FOUND")

