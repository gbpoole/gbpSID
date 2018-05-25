# - Find FFTW
# Find the native FFTW includes and library
#
#  FFTW2_INCLUDES    - where to find dfftw.h
#  FFTW2_LIBRARIES   - List of libraries when using FFTW.
#  FFTW2_FOUND       - True if FFTW found.

if (FFTW2_INCLUDES)
  # Already in cache, be silent
  set (FFTW2_FIND_QUIETLY TRUE)
endif (FFTW2_INCLUDES)

# Find the mpi library
set(FFTW2_LIBRARIES "" )
if(USE_MPI)
    if(USE_DOUBLE)
        find_path(FFTW2_INCLUDES dfftw_mpi.h )
        include_directories(${FFTW2_INCLUDES})
        find_library(FFTW2_MPI_LIBRARY NAMES dfftw_mpi)
        list(APPEND FFTW2_LIBRARIES ${FFTW2_MPI_LIBRARY})
        find_library(FFTW2_MPI_LIBRARY_R NAMES drfftw_mpi)
        list(APPEND FFTW2_LIBRARIES ${FFTW2_MPI_LIBRARY_R})
    else()
        find_path(FFTW2_INCLUDES dfftw_mpi.h)
        include_directories(${FFTW2_INCLUDES})
        find_library(FFTW2_MPI_LIBRARY NAMES sfftw_mpi)
        list(APPEND FFTW2_LIBRARIES ${FFTW2_MPI_LIBRARY} )
        find_library(FFTW2_MPI_LIBRARY_R NAMES srfftw_mpi)
        list(APPEND FFTW2_LIBRARIES ${FFTW2_MPI_LIBRARY_R} )
    endif()
endif()

# Find the non-mpi library
if(USE_DOUBLE)
    find_path(FFTW2_INCLUDES dfftw.h)
    include_directories(${FFTW2_INCLUDES})
    find_library(FFTW2_LIBRARY NAMES dfftw)
    list(APPEND FFTW2_LIBRARIES ${FFTW2_LIBRARY} )
    find_library(FFTW2_LIBRARY_R NAMES drfftw)
    list(APPEND FFTW2_LIBRARIES ${FFTW2_LIBRARY_R} )
else()
    find_path(FFTW2_INCLUDES sfftw.h)
    include_directories(${FFTW2_INCLUDES})
    find_library(FFTW2_LIBRARY NAMES sfftw)
    list(APPEND FFTW2_LIBRARIES ${FFTW2_LIBRARY} )
    find_library(FFTW2_LIBRARY_R NAMES srfftw)
    list(APPEND FFTW2_LIBRARIES ${FFTW2_LIBRARY_R} )
endif()

# Add the libraries to the project
link_libraries(${FFTW2_LIBRARIES})

# handle the QUIETLY and REQUIRED arguments and set FFTW2_FOUND to GBP_TRUE if
# all listed variables are GBP_TRUE
include (FindPackageHandleStandardArgs)
find_package_handle_standard_args (FFTW2 DEFAULT_MSG FFTW2_LIBRARIES FFTW2_INCLUDES)

SET(FFTW2_LIBRARIES ${FFTW2_LIBRARIES} CACHE INTERNAL "FFTW2 library paths")
SET(FFTW2_INCLUDES  ${FFTW2_INCLUDES} CACHE INTERNAL "FFTW2 header paths")
mark_as_advanced (FFTW2_LIBRARIES FFTW2_INCLUDES)
