# - Find FFTW
# Find the native FFTW includes and library
#
#  FFTW2_INCLUDES    - where to find dfftw.h
#  FFTW2_LIBRARIES   - List of libraries when using FFTW.
#  FFTW2_FOUND       - True if FFTW found.

if (FFTW2_INCLUDES)
  # Already in cache, be silent
  set (FFTW_FIND_QUIETLY TRUE)
endif (FFTW2_INCLUDES)

# Find header files
find_path(FFTW2_INCLUDES dfftw.h PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
find_path(FFTW2_INCLUDES dfftw.h)
include_directories(${FFTW2_INCLUDES})

# Find the mpi library
set(FFTW2_LIBRARIES "" )
if(USE_MPI)
    if(USE_DOUBLE)
        find_library(FFTW_MPI_LIBRARY dfftw_mpi PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW_MPI_LIBRARY NAMES dfftw_mpi)
    else()
        find_library(FFTW_MPI_LIBRARY sfftw_mpi PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
        find_library(FFTW_MPI_LIBRARY NAMES sfftw_mpi)
    endif()
    link_libraries(${FFTW_MPI_LIBRARIES})
    list(APPEND FFTW2_LIBRARIES ${FFTW_MPI_LIBRARY} )
endif()

# Find the non-mpi library
if(USE_DOUBLE)
    find_library(FFTW_LIBRARY dfftw PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW_LIBRARY NAMES dfftw)
else()
    find_library(FFTW_LIBRARY sfftw PATHS "${FFTW_ROOT}/*" NO_DEFAULT_PATH)
    find_library(FFTW_LIBRARY NAMES sfftw)
endif()
link_libraries(${FFTW2_LIBRARIES})
list(APPEND FFTW2_LIBRARIES ${FFTW_LIBRARY} )

# handle the QUIETLY and REQUIRED arguments and set FFTW2_FOUND to GBP_TRUE if
# all listed variables are GBP_TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FFTW2 DEFAULT_MSG FFTW2_LIBRARIES FFTW2_INCLUDES)

mark_as_advanced (FFTW2_LIBRARIES FFTW2_INCLUDES)
