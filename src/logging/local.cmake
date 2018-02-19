# The following directive is used to organise
# how the Doxygen groups defined by this project
# will be organised in the documentation:
#
# set_active_API_module      logging Logging

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
list(APPEND INCFILES "gbpSID_logging.h")

# Add source files
# eg. list(APPEND SRCFILES "file" )
list(APPEND SRCFILES "SID_log.c")
list(APPEND SRCFILES "SID_log_error.c")
list(APPEND SRCFILES "SID_log_set_fp.c")
list(APPEND SRCFILES "SID_log_warning.c")
list(APPEND SRCFILES "SID_log_header.c")
list(APPEND SRCFILES "SID_log_footer.c")
list(APPEND SRCFILES "SID_set_verbosity.c")
list(APPEND SRCFILES "SID_Init_pcounter.c")
list(APPEND SRCFILES "SID_check_pcounter.c")

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

