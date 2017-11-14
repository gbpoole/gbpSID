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
list(APPEND INCFILES "gbpSID_mpi.h")

# Add source files
# eg. list(APPEND SRCFILES "file" )
list(APPEND SRCFILES "SID_Comm_init.c")
list(APPEND SRCFILES "SID_Comm_free.c")
list(APPEND SRCFILES "SID_Comm_list.c")
list(APPEND SRCFILES "SID_Comm_split.c")
list(APPEND SRCFILES "SID_Type_size.c")
list(APPEND SRCFILES "SID_Send.c")
list(APPEND SRCFILES "SID_Recv.c")
list(APPEND SRCFILES "SID_Sendrecv.c")
list(APPEND SRCFILES "SID_Reduce.c")
list(APPEND SRCFILES "SID_Allreduce.c")
list(APPEND SRCFILES "SID_Barrier.c")
list(APPEND SRCFILES "SID_Bcast.c")

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

