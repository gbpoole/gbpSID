Installation
============

To aquire and build this library, you will need to have `git` and `cmake` installed.  You may also want one-or-more of the following optional 3rd-party libraries: an MPI distribution (eg. OpenMPI), CUDA (if you have an NVidia GPGPU installed).

With these installed, you will need to acquire the code from GitHub (ideally: clone it) and then build and install it with cmake.

Acquireing the code
-------------------

gbpSID is a "live-at-head" project.  In other words, it is intended that the latest commit will always be a useful development distribution.  To aquire it, simply clone it from GitHub::

    git clone https://github.com/gbpoole/gbpSID.git

However, if you want to download the latest version tagged as a stable release, try this::

    git clone --branch "`git ls-remote --tags https://github.com/gbpoole/gbpSID.git | sed 's|.*/\(.*\)$|\1|' | grep -v '\^' | sort -t. -k1,1nr -k2,2nr -k3,3nr`" https://github.com/gbpoole/gbpSID.git

Building the library
--------------------

Once cloned, create a build directory (for example)::

    mkdir build

Then move to that directory and run cmake

Building the documentation
--------------------------

With cmake run, documentation can be built with::

    make docs

