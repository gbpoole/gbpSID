# The following directive is used to organise
# how the Doxygen groups defined by this project
# will be organised in the documentation:
#
# set_active_API_module      file_io File I/O

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
list(APPEND INCFILES "gbpSID_file_io.h")

# Add source files
# eg. list(APPEND SRCFILES "file" )
list(APPEND SRCFILES "SID_fopen.c")
list(APPEND SRCFILES "SID_fclose.c")
list(APPEND SRCFILES "SID_fread.c")
list(APPEND SRCFILES "SID_fwrite.c")
list(APPEND SRCFILES "SID_frewind.c")
list(APPEND SRCFILES "SID_fseek.c")
list(APPEND SRCFILES "SID_fskip.c")
list(APPEND SRCFILES "SID_fseek_end.c")
list(APPEND SRCFILES "SID_fread_all.c")
list(APPEND SRCFILES "SID_fwrite_all.c")
list(APPEND SRCFILES "SID_fread_all_buffer.c")
list(APPEND SRCFILES "SID_fread_ordered.c")
list(APPEND SRCFILES "SID_fwrite_ordered.c")
list(APPEND SRCFILES "SID_fwrite_shared.c")
list(APPEND SRCFILES "SID_fopen_chunked.c")
list(APPEND SRCFILES "SID_fclose_chunked.c")
list(APPEND SRCFILES "SID_fread_chunked.c")
list(APPEND SRCFILES "SID_fread_chunked_all.c")
list(APPEND SRCFILES "SID_fread_chunked_ordered.c")
list(APPEND SRCFILES "SID_frewind_chunked.c")
list(APPEND SRCFILES "SID_fseek_chunked.c")
list(APPEND SRCFILES "SID_fskip_chunked.c")
list(APPEND SRCFILES "SID_fwrite_chunked.c")
list(APPEND SRCFILES "SID_remove_chunked.c")
list(APPEND SRCFILES "SID_cat_files.c")
list(APPEND SRCFILES "SID_Init_fp_buffer.c")
list(APPEND SRCFILES "SID_reset_fp_buffer.c")
list(APPEND SRCFILES "SID_free_fp_buffer.c")
list(APPEND SRCFILES "SID_fread_verify.c")

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

