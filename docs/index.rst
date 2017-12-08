.. gbpSID documentation master file, created by
   sphinx-quickstart on Mon Nov  6 11:17:11 2017.
   You can adapt this file completely to your liking, but it should at least
   contain the root `toctree` directive.

gbpSID
======

*gbpSID* is a library which aids in the management of C/C++ high-performance computing projects.  It automates the configuration and initialization of resources managed under MPI &/or Cuda and provides the following:

* functions for generating clear and organised execution logs (with optional timing information);

* functions for efficient reading/writing of flat binary files;

* MPI wrappers permitting serial execution of parallel applictions in the absence of an MPI installation;

* a C++ application class which reduces application boiler-plate for projects developed with gbpSID, provides uniform treatment of command-line arguments using the Clara library, and ensures project-wide handling of exceptions and application-level RAII (and subsequent garbage collection).

.. toctree::
   :maxdepth: 2
   :caption: Contents:

.. include:: install.rst

.. include:: API.rst

.. include:: execs.rst

Indices and tables
==================

* :ref:`genindex`
* :ref:`search`
