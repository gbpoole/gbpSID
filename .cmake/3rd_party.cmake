
# The functions & macros in this file are used to process
# the initialization of external (ie. 3rd party) libraries

# ==== These are the functions users should call directly ====

# Declare that a 3rd-party library is *required*
function(set_3rd_party_required lib_name )
    # Check if USE_lib_name has been set in the environment.  Validate value if so.
    if(DEFINED ENV{USE_${lib_name}})
        if(NOT "$ENV{USE_${lib_name}}")
            message(FATAL_ERROR "A required library (${lib_name}) has been switched-off in the environment.")
        endif()
    endif()

    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    set(USE_${lib_name} ON)
    if(${n_optional_args} GREATER 0)
        eval("init_3rd_party_${lib_name}(${lib_name} \"REQUIRED\" ${optional_args})")
    else()
        eval("init_3rd_party_${lib_name}(${lib_name} \"REQUIRED\" )")
    endif()
endfunction()

# Declare that a 3rd-party library is *optional*
# Build will *fail* if val is 'ON' and package load fails
function(set_3rd_party_optional lib_name val )
    # Check if USE_lib_name has been set in the environment.  Set to value if so.
    if(DEFINED ENV{USE_${lib_name}})
        set(val_env "$ENV{USE_${lib_name}}")
        if(NOT val_env STREQUAL val)
            set(val "${val_env}")
            message(STATUS "   -> Optional library ${lib_name} has been turned ${val} from the environment.")
        endif()
    endif()

    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    option(USE_${lib_name} "Use ${lib_name} (If ON, build will fail if library load fails)" ${val})
    if(USE_${lib_name})
        if(${n_optional_args} GREATER 0)
            eval("init_3rd_party_${lib_name}(${lib_name} \"SELECTED\" ${optional_args})")
        else()
            eval("init_3rd_party_${lib_name}(${lib_name} \"SELECTED\" )")
        endif()
    else()
        if(${n_optional_args} GREATER 0)
            eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" ${optional_args})")
        else()
            eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" )")
        endif()
    endif()
endfunction()

# Declare that a 3rd-party library is *requested*
# Build will *continue* if val is 'ON' and package load fails
function(set_3rd_party_requested lib_name val)
    # Check if USE_lib_name has been set in the environment.  Set to value if so.
    if(DEFINED ENV{USE_${lib_name}})
        set(val_env "$ENV{USE_${lib_name}}")
        if(NOT val_env STREQUAL val)
            set(val "${val_env}")
            message(STATUS "   -> Requested library ${lib_name} has been turned ${val} from the environment.")
        endif()
    endif()

    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    option(USE_${lib_name} "Use ${lib_name} (If ON, build will continue if library load fails)" ${val})
    if(USE_${lib_name})
        if(${n_optional_args} GREATER 0)
            eval("init_3rd_party_${lib_name}(${lib_name} \"REQUESTED\" ${optional_args})")
        else()
            eval("init_3rd_party_${lib_name}(${lib_name} \"REQUESTED\" )")
        endif()
    else()
        if(${n_optional_args} GREATER 0)
            eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" ${optional_args})")
        else()
            eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" )")
        endif()
    endif()
endfunction()

# Add a github submodule.  This is meant to be called from 'extern.cmake' files.
macro(add_external_submodule extern_dir submodule_name filename_check )
    # Make sure we have updated the Clara submodule
    set(filename_check_path "${extern_dir}/${filename_check}")
    if(NOT EXISTS "${filename_check_path}")
        message(STATUS "  -> Checking out submodule: ${submodule_name}")
        execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${extern_dir})
    else()
        message(STATUS "   -> ${submodule_name} submodule has already been checked out")
    endif()

    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    # If one optional arg is given and it tests TRUE, then
    # process this external as a gbpBuild project.
    if(${n_optional_args} GREATER 0)
        if(${optional_args})
            process_project( ${extern_dir} FALSE)
        endif()
    endif()

endmacro()

# =================== Some helper functions ==================

# Evaluate expression
# Suggestion from the Wiki: http://cmake.org/Wiki/CMake/Language_Syntax
# Unfortunately, no built-in stuff for this: http://public.kitware.com/Bug/view.php?id=4034
# This was found here: https://cmake.org/Wiki/CMake/Language_Syntax
macro(temp_name fname)
  if(${ARGC} GREATER 1) # Have to escape ARGC to correctly compare
    set(_base ${ARGV1})
  else(${ARGC} GREATER 1)
    set(_base ".cmake-tmp")
  endif(${ARGC} GREATER 1)
  set(_counter 0)
  while(EXISTS "${_base}${_counter}")
    math(EXPR _counter "${_counter} + 1")
  endwhile(EXISTS "${_base}${_counter}")
  set(${fname} "${_base}${_counter}")
endmacro(temp_name)
macro(eval expr)
  temp_name(_fname)
  file(WRITE ${_fname} "${expr}")
  include(${_fname})
  file(REMOVE ${_fname})
endmacro(eval)

# Set the variable 'required' to be "REQUIRED" or ""
# and the varibable 'required_txt' to something we 
# will use to print a status message
macro(set_required_variables required_in)
    if(required_in STREQUAL "REQUIRED" )
        set(required     "REQUIRED")
        set(required_txt "Required")
    elseif(required_in STREQUAL "REQUESTED" )
        set(required     "")
        set(required_txt "Requested")
    elseif(required_in STREQUAL "SELECTED" )
        set(required     "")
        set(required_txt "Optional")
    elseif(required_in STREQUAL "SKIPPED" )
        set(required     "")
        set(required_txt "Optional")
    else()
        message(FATAL_ERROR "Invalid input to 'set_required_variables': " ${required_in} )
    endif()
endmacro()

# Success/fail/skipped status messages
macro(check_3rd_party_status success )
    # Write a sucess/failure message and throw an error if needed
    if(${success})
        # Create a preprocessor macro that can be used in the code
        add_definitions(-DUSE_${lib_name})
        SET(USE_${lib_name} TRUE CACHE INTERNAL "${lib_name} is configured")
        message(STATUS "   -> ${required_txt} library initialized:  ${lib_name}")
    else()
        if((required_txt STREQUAL "Required") OR (required_txt STREQUAL "Optional") )
            message(FATAL_ERROR "${required_txt} library initialization failed: ${lib_name}")
        else()
            message(STATUS "${required_txt} library initialization failed: ${lib_name}")
        endif()
    endif()
endmacro()
macro(skip_3rd_party_status required_in)
    if(required_in STREQUAL "REQUIRED" )
        message(FATAL_ERROR "${required_txt} library initialization skipped: ${lib_name}")
    else()
        message(STATUS "   -> ${required_txt} library not selected: ${lib_name}")
    endif()
endmacro()

# ============== Library-specific stuff follows ==============
# If items are added to this list, don't forget to update the
# list in the 'project.cmake' template file.

# Initialize documentation build
function(init_3rd_party_GBP_DOCS_BUILD lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( ${GBP_DOCS_BUILD_FOUND} )

    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize GSL
function(init_3rd_party_GSL lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( GSL_FOUND )

        # Personalized set-up:
        include_directories( ${GSL_INCLUDE_DIRS} )
        link_libraries( ${GSL_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize MPI
function(init_3rd_party_MPI lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})

        # In case we need to use a custom build, 
        # we need to add it to the search path
        list(APPEND MPI_HINT_DIRS "${CMAKE_SOURCE_DIR}/mpich" )

        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( ${MPI_CXX_FOUND} AND ${MPI_C_FOUND} )

        # Personalized set-up:
        include_directories(${MPI_C_INCLUDE_PATH} ${MPI_CXX_INCLUDE_PATH})
        link_libraries(${MPI_C_LIBRARIES} ${MPI_CXX_LIBRARIES})
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize MPI_IO
function(init_3rd_party_MPI_IO lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        if(NOT USE_MPI)
            message(FATAL_ERROR "${required_txt} library ${lib_name} can not be initialized without MPI.")
        endif()

        # Check status and print message    
        check_3rd_party_status( TRUE )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize CUDA
function(init_3rd_party_CUDA lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message
        check_3rd_party_status( ${CUDA_FOUND} AND ${CUDA_FOUND} )

        # Personalized set-up:

        # Add CUDA files to sources
        set(SOURCES ${SOURCES_C} ${SOURCES_CU})

        # Pass options to NVCC
        set(CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
        set(CUDA_PROPAGATE_HOST_FLAGS ON)
        set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_30")

        ################################################################################
        # This ugly hack is needed to work around a bug in the fftw3.h header file
        #    see the following for a discussion: https://github.com/FFTW/fftw3/issues/18
        set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -D__INTEL_COMPILER")
        ################################################################################

        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUDA_C_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUDA_EXE_LINKER_FLAGS}")
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize CUFFT
function(init_3rd_party_CUFFT lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        if(USE_CUDA)
            CUDA_ADD_CUFFT_TO_TARGET(target)
        else()
            message(FATAL_ERROR "${required_txt} library ${lib_name} can not be initialized without CUDA.")
        endif()

        # Check status and print message    
        check_3rd_party_status( TRUE )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize GDLIB
function(init_3rd_party_GD lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( GD_FOUND )

        # Personalized set-up:
        include_directories( ${GD_INCLUDE_DIRS} )
        link_libraries( ${GD_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize CFITSIO 
function(init_3rd_party_CFITSIO lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( Cfitsio_FOUND )

        # Personalized set-up:
        include_directories( ${CFITSIO_INCLUDE_DIRS} )
        link_libraries( ${CFITSIO_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize HDF5
function(init_3rd_party_HDF5 lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required} COMPONENTS C HL)

        # Check status and print message    
        check_3rd_party_status( HDF5_FOUND )

        # Personalized set-up:
        include_directories( ${HDF5_INCLUDE_DIRS} )
        link_libraries( ${HDF5_C_LIBRARIES} ${HDF5_C_HL_LIBRARIES} )
        add_definitions(${HDF5_DEFINITIONS})

        #THIS IS A TEMPORARY HACK TO OVERCOME A BUG IN SOME VERSIONS OF CMAKE
        if(NOT (${HDF5_C_HL_LIBRARIES} MATCHES "libhdf5_hl"))
            list(GET HDF5_C_LIBRARIES 0 HDF5_LIB)
            get_filename_component(HDF5_LIBDIR ${HDF5_LIB} DIRECTORY)
            link_libraries("${HDF5_LIBDIR}/libhdf5_hl.so")
        endif()
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize FFTW v2
function(init_3rd_party_FFTW2 lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Declare the version of FFTW that we are using
        if(FFTW_V3)
            message(FATAL_ERROR "Attempting to configure FFTW V2 when FFTW V3 is already configured.")
        endif()
        add_definitions(-DFFTW_V2)
        SET(FFTW_V2 TRUE CACHE INTERNAL "FFTW V2 configured")

        # Check status and print message    
        check_3rd_party_status( FFTW2_FOUND )

        # Personalized set-up:
        include_directories( ${FFTW2_INCLUDES} )
        link_libraries( ${FFTW2_LIBRARIES} )

        # Generalized FFTW declarations
        if(${FFTW2_FOUND})
            add_definitions(-DUSE_FFTW)
            add_definitions(-DFFTW_FOUND)
            SET(USE_FFTW TRUE CACHE INTERNAL "FFTW is configured")
            SET(FFTW_FOUND TRUE CACHE INTERNAL "FFTW is configured")
        endif()
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize FFTW v3
function(init_3rd_party_FFTW3 lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Declare the version of FFTW that we are using
        if(FFTW_V2)
            message(FATAL_ERROR "Attempting to configure FFTW V3 when FFTW V2 is already configured.")
        endif()
        add_definitions(-DFFTW_V3)
        SET(FFTW_V3 TRUE CACHE INTERNAL "FFTW V3 configured")

        # Check status and print message    
        check_3rd_party_status( FFTW3_FOUND )

        # Personalized set-up:
        include_directories( ${FFTW3_INCLUDES} )
        link_libraries( ${FFTW3_LIBRARIES} )

        # Generalized FFTW declarations
        if(${FFTW3_FOUND})
            add_definitions(-DUSE_FFTW)
            add_definitions(-DFFTW_FOUND)
            SET(USE_FFTW TRUE CACHE INTERNAL "FFTW (version 2 or 3) is configured")
            SET(FFTW_FOUND TRUE CACHE INTERNAL "FFTW (version 2 or 3) is configured")
        endif()
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize OpenMP
function(init_3rd_party_OpenMP lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( OpenMP_FOUND )

        # Personalized set-up:
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize SOCI
function(init_3rd_party_Soci lib_name required_in)
    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        if(${n_optional_args} GREATER 0)
            find_package(${lib_name} ${required} COMPONENTS "${optional_args}" )
        else()
            find_package(${lib_name} ${required} )
        endif()

        # Check status and print message    
        check_3rd_party_status( SOCI_FOUND )

        # Personalized set-up:
        include_directories( ${SOCI_INCLUDE_DIRS} )
        link_libraries( ${SOCI_LIBRARY} )

        # Add plugins
        if(${n_optional_args} GREATER 0)
            foreach(component_i ${optional_args})
                set(plugin_i SOCI_${component_i}_PLUGIN)
                link_libraries( "${${plugin_i}}" )
            endforeach()
        endif()
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize FindPostgreSQL
function(init_3rd_party_PostgreSQL lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( PostgreSQL_FOUND )

        # Personalized set-up:
        include_directories( ${PostgreSQL_INCLUDE_DIRS} )
        link_libraries( ${PostgreSQL_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize PugiXML
function(init_3rd_party_PugiXML lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( PUGIXML_FOUND )

        # Personalized set-up:
        include_directories( ${PUGIXML_INCLUDE_DIR} )
        link_libraries( ${PUGIXML_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize the system thread library
function(init_3rd_party_Threads lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # FindThreads does not provide a reliable way
        # to check that a threads library was found,
        # so just assume that it was. It will throw
        # its own error on failure.
        #if(CMAKE_THREAD_LIBS_INIT)
        #    set( Threads_FOUND TRUE)
        #else()
        #    set( Threads_FOUND FALSE)
        #endif()
        set( Threads_FOUND TRUE)

        # Check status and print message 
        check_3rd_party_status( Threads_FOUND )

        # Personalized set-up:
        link_libraries( Threads::Threads )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()

# Initialize Boost
function(init_3rd_party_Boost lib_name required_in )
    # Check for optional arguments
    set (optional_args ${ARGN})
    list(LENGTH optional_args n_optional_args)

    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        if(${n_optional_args} GREATER 0)
            find_package(${lib_name} ${required} COMPONENTS "${optional_args}" )
        else()
            find_package(${lib_name} ${required} )
        endif()

        # Check status and print message    
        check_3rd_party_status( Boost_FOUND )

        # Personalized set-up:
        include_directories( ${Boost_INCLUDE_DIRS} )
        link_libraries( ${Boost_LIBRARIES} )
    else()
        skip_3rd_party_status(required_in)
    endif()
endfunction()
