Installation
============

To aquire and build this library, you will need to have :code:`git` and :code:`cmake` installed.  You may also want one-or-more of the following optional 3rd-party libraries:

* an MPI distribution (eg. OpenMPI)

* CUDA (if you have an NVidia GPGPU installed).

With these installed, you will need to:

1) acquire the code from `GitHub`;

2) configure it with :code:`cmake`; and 

3) build it with :code:`make` 

Alternatively (an prehaps more-often-than-not), you may want to add *gbpSID* as a submodule to another project.  In either case, each of these steps is described in more detail below.

Acquireing the code
-------------------

*gbpSID* is a "live-at-head" project.  In other words, it is intended that the latest commit on the 'master' branch will always be the best version to develop with.  To aquire it, simply clone it from *GitHub*::

    git clone https://github.com/gbpoole/gbpSID.git

However, if you want to download the latest version specifically tagged as a standardized release, try this::

    git clone --branch "`git ls-remote --tags https://github.com/gbpoole/gbpSID.git | sed 's|.*/\(.*\)$|\1|' | grep -v '\^' | sort -t. -k1,1nr -k2,2nr -k3,3nr`" https://github.com/gbpoole/gbpSID.git

Configuring the library
-----------------------

Once cloned, create a build directory (for example)::

    cd gbpSID
    mkdir build

Then move to that directory and run :code:`cmake` on the project directory (i.e. the directory where the file `CMakeLists.txt` is located)::

    cd build
    cmake ..

Several options can be passed to :code:`cmake` to tailor *gbpSID* to your needs.  These are as follows:

ADD TABLE HERE.

Building the library
--------------------

Once configured with :code:`cmake`, the project can be built by moving to the build directory and running the following:: 

    make

To install the project, specify the installation directory as follows::

    make DESTDIR=<full-path-to_installation-location> install

Building the documentation
--------------------------

Once :code:`cmake` has been run, documentation can be built by running the following from the build directory::

    make docs

This will place a `.pdf` version of the documentation in the directory `docs` and an `html` version in `docs/html/docs`.

Installing as a submodule
-------------------------

ADD TEXT HERE.
