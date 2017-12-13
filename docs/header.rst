gbpSID
======

*gbpSID* is a library which aids in the management of C/C++ high-performance computing projects.  It automates the configuration and initialization of resources managed under MPI &/or Cuda and provides the following:

* functions for generating clear and organised execution logs (with optional timing information);

* functions for efficient reading/writing of flat binary files;

* MPI wrappers permitting serial execution of parallel applictions in the absence of an MPI installation;

* a C++ application class which provides uniform treatment of command-line arguments (and their documentation) using the Clara library and ensures top-level exception handling and RAII garbage collection.
