
# The functions & macros in this file are used to process
# the initialization of external (ie. 3rd party) libraries

# ==== These are the functions users should call directly ====

# Declare that a 3rd-party library is *required*
function(set_3rd_party_required lib_name)
    set(USE_${lib_name} ON)
    eval("init_3rd_party_${lib_name}(${lib_name} \"REQUIRED\" )")
endfunction()

# Declare that a 3rd-party library is *optional*
# Build will *fail* if val is 'ON' and package load fails
function(set_3rd_party_optional lib_name val)
    option(USE_${lib_name} "Use ${lib_name} (If ON, build will fail if library load fails)" ${val})
    if(USE_${lib_name})
        eval("init_3rd_party_${lib_name}(${lib_name} \"SELECTED\" )")
    else()
        eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" )")
    endif()
endfunction()

# Declare that a 3rd-party library is *requested*
# Build will *continue* if val is 'ON' and package load fails
function(set_3rd_party_requested lib_name val)
    option(USE_${lib_name} "Use ${lib_name} (If ON, build will continue if library load fails)" ${val})
    if(USE_${lib_name})
        eval("init_3rd_party_${lib_name}(${lib_name} \"REQUESTED\" )")
    else()
        eval("init_3rd_party_${lib_name}(${lib_name} \"SKIPPED\" )")
    endif()
endfunction()

# Add a github submodule.  This is meant to be called from 'extern.cmake' files.
function( add_external_submodule cur_dir submodule_name filename_check )
    # Make sure we have updated the Clara submodule
    if(NOT EXISTS "${filename_check}")
        message(STATUS "  -> Checking out submodule: ${submodule_name}")
        execute_process(COMMAND git submodule update --init WORKING_DIRECTORY ${cur_dir})
    else()
        message(STATUS "  -> ${submodule_name} submodule has already been checked out")
    endif()
endfunction()

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
    if(${success})
        message(STATUS "   -> ${required_txt} library initialized:  ${lib_name}")
    else()
        if(required STREQUAL "REQUIRED" )
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

# Initialize FFTW
function(init_3rd_party_FFTW lib_name required_in)
    set_required_variables(${required_in})
    if(USE_${lib_name})
        add_definitions(-DUSE_${lib_name})
        find_package(${lib_name} ${required})

        # Check status and print message    
        check_3rd_party_status( FFTW_FOUND )

        # Personalized set-up:
        include_directories( ${FFTW_INCLUDES} )
        link_libraries( ${FFTW_LIBRARIES} )
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

