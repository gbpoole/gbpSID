# Add a bunch of common library prefix paths from the environment
list(APPEND CMAKE_PREFIX_PATH  $ENV{LD_LIBRARY_PATH})
list(APPEND CMAKE_INCLUDE_PATH $ENV{CPATH})
list(APPEND CMAKE_INCLUDE_PATH $ENV{INCLUDE})
string(REPLACE ":" ";" CMAKE_PREFIX_PATH "${CMAKE_PREFIX_PATH}")
string(REPLACE ":" ";" CMAKE_INCLUDE_PATH "${CMAKE_INCLUDE_PATH}")

# Remove Anaconda from the PATH environment variable.  This is to
# avoid problems like: https://github.com/pism/pism/issues/356
if(DEFINED ENV{REMOVE_ANACONDA_FROM_PATH})
    option(REMOVE_ANACONDA_FROM_PATH "Remove Anaconda from the environment variable 'PATH' to prevent compile/linking conflicts." "$ENV{REMOVE_ANACONDA_FROM_PATH}")
else()
    option(REMOVE_ANACONDA_FROM_PATH "Remove Anaconda from the environment variable 'PATH' to prevent compile/linking conflicts." ON)
endif()
if(REMOVE_ANACONDA_FROM_PATH)
    set(_TMP_LIST "$ENV{PATH}")
    string(REPLACE ":" ";" _TMP_LIST "${_TMP_LIST}")
    list(FILTER _TMP_LIST EXCLUDE REGEX "(anaconda)")
    string(REPLACE ";" ":" _TMP_LIST "${_TMP_LIST}")
    set(ENV{PATH} "${_TMP_LIST}")
endif()
