# Configure any external projects, submodules, etc.
macro(local_extern cur_dir )
    # gbpBuild provides the boilerplate for this project's development environment
    add_external_submodule( ${cur_dir} "gbpBuild" ${cur_dir}"/gbpBuild/README.md" )

    # Clara is a 3rd party header-only library, by Phil Nash 
    #
    # It is used in the Catch2 project: https://github.com/catchorg/Catch2
    # and is a "simple to use, composable, command line parser for
    # C++ 11 and beyond".  See the following links for more info:
    #
    #    https://github.com/philsquared/Clara
    #    https://www.youtube.com/watch?v=Od4bjLfwI-A
    #
    add_external_submodule( ${cur_dir} "Clara" ${cur_dir}"/extern/Clara/include/clara.hpp" )
endmacro()
