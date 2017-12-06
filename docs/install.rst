Installation
============

To aquire and build this library, you will need to have :code:`git` and :code:`cmake` installed.  You may also want one-or-more of the following optional 3rd-party libraries:

* an MPI distribution (eg. OpenMPI)

* CUDA (if you have an NVidia GPGPU installed).

With these installed, you will need to acquire the code from `GitHub` and then build and install it with :code:`cmake`.

Acquireing the code
-------------------

*gbpSID* is a "live-at-head" project.  In other words, it is intended that the latest commit on the 'master' branch will always be the best version to develop with.  To aquire it, simply clone it from *GitHub*::

    git clone https://github.com/gbpoole/gbpSID.git

However, if you want to download the latest version specifically tagged as a standardized release, try this::

    git clone --branch "`git ls-remote --tags https://github.com/gbpoole/gbpSID.git | sed 's|.*/\(.*\)$|\1|' | grep -v '\^' | sort -t. -k1,1nr -k2,2nr -k3,3nr`" https://github.com/gbpoole/gbpSID.git

Building the library
--------------------

Once cloned, create a build directory (for example)::

    cd gbpSID
    mkdir build

Then move to that directory and run :code:`cmake` on the project directory (i.e. the directory where the file `CMakeLists.txt` is located)::

    cd build
    cmake ..

and then build the project::

    make

To install the project, specify the installation directory as follows::

    make DESTDIR=<full-path-to_installation-location> install

Building the documentation
--------------------------

Once :code:`cmake` has been run, documentation can be built with::

    make docs

This will place a `.pdf` version of the documentation in the `docs` directory of the build directory and an `html` version in `docs/html/docs/`.
