C/C++ API
=========
Core
----

Class definitions
`````````````````
.. doxygengroup:: core_classes
   :project: gbpSID
   :content-only:
   :members:

Functions
`````````
.. doxygenfunction:: SID_Init
   :project: gbpSID

.. doxygenfunction:: SID_Finalize
   :project: gbpSID

.. doxygenfunction:: SID_exit_error
   :project: gbpSID

.. doxygenfunction:: SID_seconds2ascii
   :project: gbpSID

.. doxygenfunction:: SID_va_start
   :project: gbpSID

.. doxygenfunction:: SID_add_va_arg
   :project: gbpSID

.. doxygenfunction:: SID_fetch_va_arg
   :project: gbpSID

Error code definitions
``````````````````````
.. doxygengroup:: core_error_codes
   :project: gbpSID
   :content-only:
   :members:

Memory managment
----------------

Functions
`````````
.. doxygenfunction:: SID_malloc
   :project: gbpSID

.. doxygenfunction:: SID_calloc
   :project: gbpSID

.. doxygenfunction:: SID_realloc
   :project: gbpSID

.. doxygenfunction:: SID_free
   :project: gbpSID

Logging
-------

Functions
`````````
.. doxygenfunction:: SID_log
   :project: gbpSID

.. doxygenfunction:: SID_log_error
   :project: gbpSID

.. doxygenfunction:: SID_log_set_fp
   :project: gbpSID

.. doxygenfunction:: SID_log_warning
   :project: gbpSID

.. doxygenfunction:: SID_log_header
   :project: gbpSID

.. doxygenfunction:: SID_log_footer
   :project: gbpSID

.. doxygenfunction:: SID_set_verbosity
   :project: gbpSID

.. doxygenfunction:: SID_Init_pcounter
   :project: gbpSID

.. doxygenfunction:: SID_check_pcounter
   :project: gbpSID

Message Passing Interface (MPI)
-------------------------------

Functions
`````````
.. doxygenfunction:: SID_Comm_init
   :project: gbpSID

.. doxygenfunction:: SID_Comm_free
   :project: gbpSID

.. doxygenfunction:: SID_Comm_list
   :project: gbpSID

.. doxygenfunction:: SID_Comm_split
   :project: gbpSID

.. doxygenfunction:: SID_Type_size
   :project: gbpSID

.. doxygenfunction:: SID_Send
   :project: gbpSID

.. doxygenfunction:: SID_Isend
   :project: gbpSID

.. doxygenfunction:: SID_Ssend
   :project: gbpSID

.. doxygenfunction:: SID_Recv
   :project: gbpSID

.. doxygenfunction:: SID_Irecv
   :project: gbpSID

.. doxygenfunction:: SID_Sendrecv
   :project: gbpSID

.. doxygenfunction:: SID_Probe
   :project: gbpSID

.. doxygenfunction:: SID_Reduce
   :project: gbpSID

.. doxygenfunction:: SID_Allreduce
   :project: gbpSID

.. doxygenfunction:: SID_Allgather
   :project: gbpSID

.. doxygenfunction:: SID_Allgatherv
   :project: gbpSID

.. doxygenfunction:: SID_Gatherv
   :project: gbpSID

.. doxygenfunction:: SID_Scatterv
   :project: gbpSID

.. doxygenfunction:: SID_Barrier
   :project: gbpSID

.. doxygenfunction:: SID_Bcast
   :project: gbpSID

.. doxygenfunction:: SID_Wait
   :project: gbpSID

.. doxygenfunction:: SID_Waitall
   :project: gbpSID

.. doxygenfunction:: SID_Wtime
   :project: gbpSID

File I/O
--------

Functions
`````````
.. doxygenfunction:: SID_fopen
   :project: gbpSID

.. doxygenfunction:: SID_fclose
   :project: gbpSID

.. doxygenfunction:: SID_fread
   :project: gbpSID

.. doxygenfunction:: SID_fwrite
   :project: gbpSID

.. doxygenfunction:: SID_frewind
   :project: gbpSID

.. doxygenfunction:: SID_fseek
   :project: gbpSID

.. doxygenfunction:: SID_fskip
   :project: gbpSID

.. doxygenfunction:: SID_fseek_end
   :project: gbpSID

.. doxygenfunction:: SID_fread_all
   :project: gbpSID

.. doxygenfunction:: SID_fwrite_all
   :project: gbpSID

.. doxygenfunction:: SID_fread_all_buffer
   :project: gbpSID

.. doxygenfunction:: SID_fread_ordered
   :project: gbpSID

.. doxygenfunction:: SID_fwrite_ordered
   :project: gbpSID

.. doxygenfunction:: SID_fwrite_shared
   :project: gbpSID

.. doxygenfunction:: SID_fopen_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fclose_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fread_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fread_chunked_all
   :project: gbpSID

.. doxygenfunction:: SID_fread_chunked_ordered
   :project: gbpSID

.. doxygenfunction:: SID_frewind_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fseek_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fskip_chunked
   :project: gbpSID

.. doxygenfunction:: SID_fwrite_chunked
   :project: gbpSID

.. doxygenfunction:: SID_remove_chunked
   :project: gbpSID

.. doxygenfunction:: SID_cat_files
   :project: gbpSID

.. doxygenfunction:: SID_Init_fp_buffer
   :project: gbpSID

.. doxygenfunction:: SID_reset_fp_buffer
   :project: gbpSID

.. doxygenfunction:: SID_free_fp_buffer
   :project: gbpSID

.. doxygenfunction:: SID_fread_verify
   :project: gbpSID

Development tools
-----------------

Functions
`````````
.. doxygenfunction:: SID_mpi_gdb_here
   :project: gbpSID

.. doxygenfunction:: SID_test
   :project: gbpSID

.. doxygenfunction:: exchange_ring_buffer
   :project: gbpSID

.. doxygenfunction:: set_exchange_ring_ranks
   :project: gbpSID

