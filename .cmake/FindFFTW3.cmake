# - Find FFTW3
# Find the native FFTW3 includes and library
#
#  FFTW3_INCLUDES    - where to find fftw3.h
#  FFTW3_LIBRARIES   - List of libraries when using FFTW3.
#  FFTW3_FOUND       - True if FFTW3 found.

if (FFTW3_INCLUDES)
  # Already in cache, be silent
  set (FFTW3_FIND_QUIETLY TRUE)
endif (FFTW3_INCLUDES)

# Find header files
find_path(FFTW3_INCLUDES fftw3.h PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
find_path(FFTW3_INCLUDES fftw3.h)
include_directories(${FFTW3_INCLUDES})

# Find the mpi library
set(FFTW3_LIBRARIES "" )
if(USE_MPI)
    if(USE_DOUBLE)
        find_library(FFTW3_FIND_QUIETLY_MPI_LIBRARY fftw3_mpi PATHS "${FFTW3_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW3_MPI_LIBRARY NAMES fftw3_mpi)
    else()
        find_library(FFTW3_MPI_LIBRARY fftw3f_mpi PATHS "${FFTW3_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW3_MPI_LIBRARY NAMES fftw3f_mpi)
    endif()
    link_libraries(${FFTW3_MPI_LIBRARIES})
    list(APPEND FFTW3_LIBRARIES ${FFTW3_MPI_LIBRARY} )
endif()

# Find the non-mpi library
if(USE_DOUBLE)
    find_library(FFTW3_LIBRARY fftw3 PATHS "${FFTW3_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW3_LIBRARY NAMES fftw3)
else()
    find_library(FFTW3_LIBRARY fftw3f PATHS "${FFTW3_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW3_LIBRARY NAMES fftw3f)
endif()
link_libraries(${FFTW3_LIBRARIES})
list(APPEND FFTW3_LIBRARIES ${FFTW3_LIBRARY} )

# handle the QUIETLY and REQUIRED arguments and set FFTW3_FOUND to GBP_TRUE if
# all listed variables are GBP_TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FFTW3 DEFAULT_MSG FFTW3_LIBRARIES FFTW3_INCLUDES)

mark_as_advanced (FFTW3_LIBRARIES FFTW3_INCLUDES)
