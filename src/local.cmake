# Set empty defaults
set(LIBDIRS    "" )
set(SRCDIRS    "" )
set(INCFILES   "" )
set(SRCFILES   "" )
set(EXEFILES   "" )
set(TARGETDEPS "" )
set(DATAFILES  "" )
set(PASSDIRS   "" )
set(DATASUBDIR "" )

# Add subdirectories that are roots to libraries
# eg. list(APPEND LIBDIRS "dirname")
# -- NONE FOR THIS DIR --

# Add directories that contribute source files 
# eg. list(APPEND SRCDIRS "dirname")
# -- NONE FOR THIS DIR --

# Add header files
# eg. list(APPEND INCFILES "filename.ext")
list(APPEND INCFILES "gbpSID.h" )

# Add source files
# eg. list(APPEND SRCFILES "filename.ext")
list(APPEND SRCFILES "fread_verify.c" )
list(APPEND SRCFILES "gbp_va_start.c" )
list(APPEND SRCFILES "gbp_add_va_arg.c" )
list(APPEND SRCFILES "gbp_fetch_va_arg.c" )
list(APPEND SRCFILES "SID_init.c" )
list(APPEND SRCFILES "SID_test.c" )
list(APPEND SRCFILES "SID_exit.c" )
list(APPEND SRCFILES "SID_init_pcounter.c" )
list(APPEND SRCFILES "SID_mpi_gdb_here.c" )
list(APPEND SRCFILES "SID_check_pcounter.c" )
list(APPEND SRCFILES "SID_Type_size.c" )
list(APPEND SRCFILES "SID_Comm_split.c" )
list(APPEND SRCFILES "SID_Comm_init.c" )
list(APPEND SRCFILES "SID_Comm_free.c" )
list(APPEND SRCFILES "SID_Bcast.c" )
list(APPEND SRCFILES "SID_Reduce.c" )
list(APPEND SRCFILES "SID_Allreduce.c" )
list(APPEND SRCFILES "SID_Sendrecv.c" )
list(APPEND SRCFILES "SID_Send.c" )
list(APPEND SRCFILES "SID_Recv.c" )
list(APPEND SRCFILES "SID_Barrier.c" )
list(APPEND SRCFILES "SID_print_syntax.c" )
list(APPEND SRCFILES "SID_log.c" )
list(APPEND SRCFILES "SID_log_set_fp.c" )
list(APPEND SRCFILES "SID_set_verbosity.c" )
list(APPEND SRCFILES "SID_profile_start.c" )
list(APPEND SRCFILES "SID_profile_stop.c" )
list(APPEND SRCFILES "SID_free.c" )
list(APPEND SRCFILES "SID_free_array.c" )
list(APPEND SRCFILES "SID_malloc.c" )
list(APPEND SRCFILES "SID_realloc.c" )
list(APPEND SRCFILES "SID_malloc_array.c" )
list(APPEND SRCFILES "SID_calloc.c" )
list(APPEND SRCFILES "SID_out.c" )
list(APPEND SRCFILES "SID_log_error.c" )
list(APPEND SRCFILES "SID_log_warning.c" )
list(APPEND SRCFILES "SID_exit_error.c" )
list(APPEND SRCFILES "SID_fopen.c" )
list(APPEND SRCFILES "SID_fopen_chunked.c" )
list(APPEND SRCFILES "SID_fclose.c" )
list(APPEND SRCFILES "SID_fclose_chunked.c" )
list(APPEND SRCFILES "SID_remove_chunked.c" )
list(APPEND SRCFILES "SID_fread.c" )
list(APPEND SRCFILES "SID_fread_all.c" )
list(APPEND SRCFILES "SID_fread_all_buffer.c" )
list(APPEND SRCFILES "SID_fread_ordered.c" )
list(APPEND SRCFILES "SID_fread_chunked.c" )
list(APPEND SRCFILES "SID_fread_chunked_ordered.c" )
list(APPEND SRCFILES "SID_fread_chunked_all.c" )
list(APPEND SRCFILES "SID_fskip_chunked.c" )
list(APPEND SRCFILES "SID_fseek_chunked.c" )
list(APPEND SRCFILES "SID_frewind_chunked.c" )
list(APPEND SRCFILES "SID_fwrite.c" )
list(APPEND SRCFILES "SID_fwrite_all.c" )
list(APPEND SRCFILES "SID_fwrite_ordered.c" )
list(APPEND SRCFILES "SID_fwrite_shared.c" )
list(APPEND SRCFILES "SID_fwrite_chunked.c" )
list(APPEND SRCFILES "SID_fseek.c" )
list(APPEND SRCFILES "SID_fseek_end.c" )
list(APPEND SRCFILES "SID_fskip.c" )
list(APPEND SRCFILES "SID_frewind.c" )
list(APPEND SRCFILES "SID_cat_files.c" )
list(APPEND SRCFILES "init_SID_fp_buffer.c" )
list(APPEND SRCFILES "reset_SID_fp_buffer.c" )
list(APPEND SRCFILES "free_SID_fp_buffer.c" )
list(APPEND SRCFILES "check_mode_for_flag.c" )
list(APPEND SRCFILES "seconds2ascii.c" )

# Add executable source files (those with a main())
# eg. list(APPEND EXEFILES "filename.ext")
# -- NONE FOR THIS DIR --

# Add target dependencies 
# eg. list(APPEND TARGETDEPS "dep_name")
# -- NONE FOR THIS DIR --

# Add data files
# eg. list(APPEND TARGETDEPS "dep_name")
# -- NONE FOR THIS DIR --

# Add subdirectories that we want to decend into
#   but which we won't scan for sources, etc
# -- NONE FOR THIS DIR --
