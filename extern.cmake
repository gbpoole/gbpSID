macro (local_extern cur_dir )
    # Make sure we have updated the Clara submodule
    if(NOT EXISTS "${cur_dir}/extern/Clara/include/clara.hpp")
        message(STATUS "  -> Checking out Clara submodule")
        execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${cur_dir})
    else()
        message(STATUS "  -> Clara submodule has already been checked out")
    endif()
endmacro()
