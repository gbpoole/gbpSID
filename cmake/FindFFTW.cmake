# - Find FFTW
# Find the native FFTW includes and library
#
#  FFTW_INCLUDES    - where to find fftw3.h
#  FFTW_LIBRARIES   - List of libraries when using FFTW.
#  FFTW_FOUND       - True if FFTW found.

if (FFTW_INCLUDES)
  # Already in cache, be silent
  set (FFTW_FIND_QUIETLY TRUE)
endif (FFTW_INCLUDES)

# Find header files
find_path(FFTW_INCLUDES fftw3.h PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
find_path(FFTW_INCLUDES fftw3.h)
include_directories(${FFTW_INCLUDES})

# Find the mpi library
set(FFTW_LIBRARIES "" )
if(USE_MPI)
    if(USE_DOUBLE)
        find_library(FFTW_MPI_LIBRARY fftw3_mpi PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW_MPI_LIBRARY NAMES fftw3_mpi)
    else()
        find_library(FFTW_MPI_LIBRARY fftw3f_mpi PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW_MPI_LIBRARY NAMES fftw3f_mpi)
    endif()
    link_libraries(${FFTW_MPI_LIBRARIES})
    list(APPEND FFTW_LIBRARIES ${FFTW_MPI_LIBRARY} )
endif()

# Find the non-mpi library
if(USE_DOUBLE)
    find_library(FFTW_LIBRARY fftw3 PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW_LIBRARY NAMES fftw3)
else()
    find_library(FFTW_LIBRARY fftw3f PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW_LIBRARY NAMES fftw3f)
endif()
link_libraries(${FFTW_LIBRARIES})
list(APPEND FFTW_LIBRARIES ${FFTW_LIBRARY} )

# handle the QUIETLY and REQUIRED arguments and set FFTW_FOUND to GBP_TRUE if
# all listed variables are GBP_TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FFTW DEFAULT_MSG FFTW_LIBRARIES FFTW_INCLUDES)

mark_as_advanced (FFTW_LIBRARIES FFTW_INCLUDES)
