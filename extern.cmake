# Configure any external projects, submodules, etc.
macro(local_extern cur_dir )
    # Clara is a 3rd party header-only library, by Phil Nash 
    #
    # It is used in the Catch2 project: https://github.com/catchorg/Catch2
    # and is a "simple to use, composable, command line parser for
    # C++ 11 and beyond".  See the following links for more info:
    #
    #    https://github.com/philsquared/Clara
    #    https://www.youtube.com/watch?v=Od4bjLfwI-A
    #
    add_external_submodule( "${cur_dir}/extern/Clara/" "Clara" "include/clara.hpp" FALSE)
endmacro()
