# This file contains all the macros that are used
#   by cmake to build header directory lists as 
#   well as all library and executable targets

# Macro to get all the information we
#    need about a given directory
macro(set_dir_state cur_dir)
    # Read a file which specifies the content
    #   and subdirectory structure of the
    #   given directory.
    include( ${cur_dir}/local.cmake )

    # Add the path to all header files
    set(INCFILES_WITH_PATH "" )
    foreach( _inc_file_nopath ${INCFILES} )
        list(APPEND INCFILES_WITH_PATH ${cur_dir}/${_inc_file_nopath} )
    endforeach()

    # Add the path to all source files
    set(SRCFILES_WITH_PATH "" )
    foreach( _src_file_nopath ${SRCFILES} )
        list(APPEND SRCFILES_WITH_PATH ${cur_dir}/${_src_file_nopath} )
    endforeach()

    # Add the path to all executable files
    set(EXEFILES_WITH_PATH "" )
    foreach( _exe_file_nopath ${EXEFILES} )
        list(APPEND EXEFILES_WITH_PATH ${cur_dir}/${_exe_file_nopath} )
    endforeach()
    foreach( _exe_file_nopath ${EXEFILES_GLOBAL} )
        list(APPEND EXEFILES_GLOBAL_WITH_PATH ${cur_dir}/${_exe_file_nopath} )
    endforeach()

    # Add the path to all data files
    set(DATAFILES_WITH_PATH "" )
    foreach( _data_file_nopath ${DATAFILES} )
        list(APPEND DATAFILES_WITH_PATH ${cur_dir}/data/${_data_file_nopath} )
    endforeach()

    # Create a list of all the subdirectories
    set(ALLDIRS "" )
    list(APPEND ALLDIRS ${LIBDIRS} )
    list(APPEND ALLDIRS ${SRCDIRS} )
    list(APPEND ALLDIRS ${PASSDIRS} )

    # Set the full path to the final 
    # data directory install destination
    set(DATADIR ${CMAKE_INSTALL_PREFIX}/data/${DATASUBDIR} )
endmacro()

# Macro which adds a directory to the project's
#    list of include direcories, if it is one
macro(add_header_directory cur_dir )
    if( INCFILES )
        # Create unique list of directories to add to the list
        set(_incdirs "" )
        foreach(_tmp_file ${INCFILES_WITH_PATH} )
            get_filename_component( _tmp_path ${_tmp_file} DIRECTORY ) 
            list(APPEND _incdirs ${_tmp_path})
        endforeach()
        list(REMOVE_DUPLICATES _incdirs)
        foreach(_tmp_dir ${_incdirs} )
            message(STATUS "   -> " ${_tmp_dir} )
        endforeach()
        # Add directories and files to the lists
        list(APPEND INC_DIRS_PROJECT ${_incdirs} )
        list(APPEND INC_FILES_PROJECT ${INCFILES_WITH_PATH} )
    endif()
endmacro()

# Macro for adding sources to a library build
macro(collect_library_sources lib_name cur_dir )
    set(LIBRARY_SOURCES "" )
    collect_library_sources_recurse( ${lib_name} ${cur_dir} )
endmacro()
macro(collect_library_sources_recurse lib_name cur_dir )
    set_dir_state( ${cur_dir} )

    # Report if there are any files being added from this directory
    if( SRCFILES )
        message(STATUS "   Adding source files in " ${cur_dir} " to " ${lib_name} )
    endif()

    # Check that there are no LIBDIRS sitting
    #    in the subdirectory structure of
    #    any other LIBDIRS
    if(LIBDIRS)
        message(FATAL_ERROR "Library directory ${cur_dir} sits in the subdirectory tree of library ${lib_name}")
    endif()

    # Add any source files in this directory
    #   to the library's file list
    foreach(_src ${SRCFILES_WITH_PATH} )
        list(APPEND LIBRARY_SOURCES ${_src} )
    endforeach()

    # Recurse over the source directories 
    foreach( _dir_name ${SRCDIRS} )
        collect_library_sources_recurse( ${lib_name} ${cur_dir}/${_dir_name}  )
    endforeach()
endmacro()

# Macros for adding sources to a library build
macro(collect_executables cur_dir )
    set(EXE_LIST "" )
    collect_executables_recurse( ${cur_dir} )
endmacro()
macro(collect_executables_recurse cur_dir )
    # Add any executables in this directory to the list
    set_dir_state( ${cur_dir} )
    foreach(_exe ${EXEFILES_WITH_PATH} )
        list(APPEND EXE_LIST ${_exe} )
    endforeach()

    # Recurse over the source directories 
    foreach( _dir_name ${SRCDIRS} )
        collect_executables_recurse( ${cur_dir}/${_dir_name}  )
    endforeach()
endmacro()

# Macros for adding sources to a library build
macro(collect_data_files cur_dir )
    set(DATAFILE_LIST "" )
    collect_data_files_recurse( ${cur_dir} )
endmacro()
macro(collect_data_files_recurse cur_dir )
    # Add any executables in this directory to the list
    set_dir_state( ${cur_dir} )
    foreach(_data_file ${DATAFILES_WITH_PATH} )
        list(APPEND DATAFILE_LIST ${_data_file} )
    endforeach()

    # Recurse over the source directories 
    foreach( _dir_name ${SRCDIRS} )
        collect_data_files_recurse( ${cur_dir}/${_dir_name}  )
    endforeach()
endmacro()

# Macro for initializing a specific library
macro(build_library lib_name cur_dir )

    # Write a status message
    message(STATUS "" )
    message(STATUS "Initializing " ${lib_name} )

    # Collect the sources for the library
    collect_library_sources( ${lib_name} ${cur_dir} )

    # Add to the collection of project source files
    list(APPEND SRC_FILES_PROJECT ${LIBRARY_SOURCES} )

    # Add header files to the project, so CLion can integrate them
    list(APPEND LIBRARY_SOURCES ${INC_FILES_PROJECT} )

    # Add the library to the list of targets
    set_dir_state(${cur_dir}) # Needed to get DATADIR
    add_library(${lib_name} STATIC ${LIBRARY_SOURCES})
    target_compile_options(${lib_name} PRIVATE -DGBP_DATA_DIR=\"${DATADIR}\" )
    install(TARGETS ${lib_name} DESTINATION lib )

    # Take care of dependancies.  We are assuming that
    #   libraries were listed in order of dependancy.
    if(DEPLIST)
        message(STATUS "   Adding dependencies: " "${DEPLIST}" )
        add_dependencies(${lib_name} ${DEPLIST})
    endif()
    list(APPEND DEPLIST ${lib_name} )

    # The dependency list needs to be reversed so that 
    #   dependencies between dependencies are properly
    #   resolved.
    # n.b.: We are assuming that libraries are
    #       listed in order of dependancy.
    set(_DEPLIST_REV "" )
    list(APPEND  _DEPLIST_REV ${DEPLIST} )
    list(REVERSE _DEPLIST_REV)

    # Status message
    message(STATUS "Done." )
endmacro()

# Build list of executables
macro(build_executables cur_dir )
    # Collect the executables for this directory
    collect_executables( ${cur_dir} )

    # Add to the collection of project source files
    list(APPEND SRC_FILES_PROJECT ${EXE_LIST} )

    # Add each executable to the target list
    set_dir_state(${cur_dir}) # Needed for DATADIR
    foreach( _exe_file ${EXE_LIST} )
        get_filename_component( _exe_name ${_exe_file} NAME_WE )

        # Add executable to the target list
        message(STATUS "Adding executable " ${_exe_name} " (dependencies: " "${_DEPLIST_REV}" ")")
        if(USE_CUDA)
            cuda_add_executable(${_exe_name} ${_exe_file} ${EXEFILES_GLOBAL_WITH_PATH} ${INC_FILES_PROJECT})
        else()
            add_executable(${_exe_name} ${_exe_file} ${EXEFILES_GLOBAL_WITH_PATH} ${INC_FILES_PROJECT})
        endif()
        target_compile_options(${_exe_name} PRIVATE -DGBP_DATA_DIR=\"${DATADIR}\" )
        install(TARGETS ${_exe_name} DESTINATION bin )

        # Add dependencies. 
        target_link_libraries(${_exe_name} ${_DEPLIST_REV})
        if(DEPLIST)
            add_dependencies(${_exe_name} ${DEPLIST})
        endif()
    endforeach()
endmacro()

# Build list of data files
macro(build_data_files cur_dir )
    # Collect the data files for this directory
    collect_data_files( ${cur_dir} )

    # Add each data file to the target list
    set_dir_state(${cur_dir})
    foreach( _data_file ${DATAFILE_LIST} )
        get_filename_component( _data_name ${_data_file} NAME )
        message(STATUS "Adding data file " ${_data_name} )
        configure_file( ${_data_file} data/${DATASUBDIR}/${_data_name} COPYONLY )
    endforeach()
endmacro()

# Macro for initializing &/or building external dependencies
macro(process_externs cur_dir )

    if( ${cur_dir} STREQUAL ${CMAKE_SOURCE_DIR} )
        message(STATUS "" )
        message(STATUS "Checking for external dependencies..." )
    endif()

    # Check if the current directory has an 'extern.cmake' file
    if(EXISTS "${cur_dir}/extern.cmake")
        include( ${cur_dir}/extern.cmake )
        local_extern( ${cur_dir} )
    endif()

    # Recurse through all directories
    set_dir_state(${cur_dir})
    foreach(_dir_name ${ALLDIRS} )
        process_externs( ${cur_dir}/${_dir_name} ) 
    endforeach()

    if( ${cur_dir} STREQUAL ${CMAKE_SOURCE_DIR} )
        message(STATUS "Done." )
    endif()
endmacro()

# Macro to assemble a list of all directories
#    with a header file and their filenames
macro(process_headers cur_dir )
    # Perform some initialization on the first call
    if( ${cur_dir} STREQUAL ${CMAKE_SOURCE_DIR} )
        message(STATUS "" )
        message(STATUS "Assembling a list of project header directories..." )
        set(INC_DIRS_PROJECT "" )
        set(INC_FILES_PROJECT "" )
    endif()

    # Process this directory
    set_dir_state(${cur_dir})
    add_header_directory( ${cur_dir} )

    # Recurse through all directories
    foreach(_dir_name ${ALLDIRS} )
        process_headers( ${cur_dir}/${_dir_name} ) 
    endforeach()

    # Add the directories we have assembled to the project
    include_directories( ${INC_DIRS_PROJECT} )

    if( ${cur_dir} STREQUAL ${CMAKE_SOURCE_DIR} )
        message(STATUS "Done." )
    endif()
endmacro()

# Main macro which initializes all project targets
macro(process_targets cur_dir )
    # Perform some initialization on the first call
    if( ${cur_dir} STREQUAL ${CMAKE_SOURCE_DIR} )
        set(SRC_FILES_PROJECT "" )
    endif()

    # Build all targets associated with library directories
    set_dir_state(${cur_dir})
    foreach(_lib_name ${LIBDIRS} )
        build_library( ${_lib_name} ${cur_dir}/${_lib_name} ) 
        build_executables( ${cur_dir}/${_lib_name} ) 
        build_data_files( ${cur_dir}/${_lib_name} ) 
    endforeach()

    # Build targets associated with the current pass-through directory
    set_dir_state(${cur_dir})
    if(SRC_FILES OR SRCDIRS)
        get_filename_component( _lib_name ${cur_dir} NAME )
        build_library( ${_lib_name} ${cur_dir} )
    endif()
    build_executables( ${cur_dir} ) 
    build_data_files( ${cur_dir} ) 

    # Recurse over all pass-through directories
    set_dir_state(${cur_dir})
    foreach( _dir_i ${PASSDIRS} )
        process_targets( ${cur_dir}/${_dir_i} )
    endforeach()
endmacro()

# Macro for printing variables
macro(print_variable variableName)
    message(STATUS "${variableName}=${${variableName}}")
endmacro()
macro(print_all_variables)
    message(STATUS "print_all_variables------------------------------------------{")
    get_cmake_property(_variableNames VARIABLES)
    foreach (_variableName ${_variableNames})
        print_variable(${_variableName}) 
    endforeach()
    message(STATUS "print_all_variables------------------------------------------}")
endmacro()

