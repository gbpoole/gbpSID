# The following directive is used to organise
# how the Doxygen groups defined by this project
# will be organised in the documentation:
#
# set_active_API_module src Source

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
list(APPEND SRCDIRS "core" )
list(APPEND SRCDIRS "app" )
list(APPEND SRCDIRS "malloc" )
list(APPEND SRCDIRS "logging" )
list(APPEND SRCDIRS "mpi" )
list(APPEND SRCDIRS "file_io" )
list(APPEND SRCDIRS "dev" )

# Add header files
# eg. list(APPEND INCFILES "file" )
list(APPEND INCFILES "gbpSID.h" )

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

