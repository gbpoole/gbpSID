# The following directive is used to organise
# how the Doxygen groups defined by this project
# will be organised in the documentation:
#
# set_active_API_module      core Core

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
# -- NONE FOR THIS DIR --

# Add header files
# eg. list(APPEND INCFILES "file" )
list(APPEND INCFILES "gbpSID_core.h")

# Add this file to the list of files that
#    get compiled when applications are created
#set(EXEFILES_APPLICATION "${local_dir}/gbpApp.cc")

# Add source files
# eg. list(APPEND SRCFILES "file" )
list(APPEND SRCFILES "SID_Init.c")
list(APPEND SRCFILES "SID_Finalize.c")
list(APPEND SRCFILES "SID_exit_error.c")
list(APPEND SRCFILES "SID_seconds2ascii.c")
list(APPEND SRCFILES "SID_va_start.c")
list(APPEND SRCFILES "SID_add_va_arg.c")
list(APPEND SRCFILES "SID_fetch_va_arg.c")

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

