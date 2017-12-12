# The following directive is used to organise
# how the Doxygen groups defined by this project
# will be organised in the documentation:
#
# set_active_API_module root Project root

# Set empty defaults
set(LIBDIRS    "" )
set(SRCDIRS    "" )
set(INCFILES   "" )
set(SRCFILES   "" )
set(EXEFILES   "" )
set(DATAFILES  "" )
set(PASSDIRS   "" )
set(DATASUBDIR "" )

# Add subdirectories that are roots to libraries
# eg. list(APPEND LIBDIRS "dir" )
# -- NONE FOR THIS DIR --

# Add directories that contribute source files 
# eg. list(APPEND SRCDIRS "dir" )
list(APPEND SRCDIRS "src" )

# Add header files
# eg. list(APPEND INCFILES "file" )
# Clara is a 3rd party header-only library, by Phil Nash and is
#    used by the Catch2 project: https://github.com/catchorg/Catch2
#    It is a "simple to use, composable, command line parser for
#    C++ 11 and beyond".  See the following talk for more info:
#    https://www.youtube.com/watch?v=Od4bjLfwI-A
list(APPEND INCFILES   "extern/Clara/include/clara.hpp" )

# Add source files
# eg. list(APPEND SRCFILES "file" )
# -- NONE FOR THIS DIR --

# Add executable source files (those with a main())
# eg. list(APPEND EXEFILES "file" )
# -- NONE FOR THIS DIR --

# Add data files
# eg. list(APPEND DATAFILES "file" )
# -- NONE FOR THIS DIR --

# Set data subdirectory
# eg. set(DATASUBDIR "dir" )
# -- NONE FOR THIS DIR --

# Add subdirectories that we want to decend into
#   but which we won't scan for sources, etc
# eg. list(APPEND PASSDIRS "dir" )
# -- NONE FOR THIS DIR --

