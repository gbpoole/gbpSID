# Initialize CUDA
#function(init_3rd_party_CUDA use_variable required)
#    if(${use_variable})
#        find_package(CUDA REQUIRED)
#        add_definitions(-DUSE_CUDA)
#        option(USE_CUFFT "Use cuFFT" OFF)
#        if(USE_CUFFT)
#            add_definitions(-DUSE_CUFFT)
#        endif()
#
#        #Collect CUDA source code
#        file(GLOB SOURCES_CU core/*.cu *.hh)
#        set(SOURCES ${SOURCES_C} ${SOURCES_CU})
#
#        # Pass options to NVCC
#        set(CUDA_HOST_COMPILER ${CMAKE_CXX_COMPILER})
#        set(CUDA_PROPAGATE_HOST_FLAGS ON)
#        set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -arch=sm_30")
#
#        ################################################################################
#        # This ugly hack is needed to work around a bug in the fftw3.h header file
#        #    see the following for a discussion: https://github.com/FFTW/fftw3/issues/18
#        set(CUDA_NVCC_FLAGS "${CUDA_NVCC_FLAGS} -D__INTEL_COMPILER")
#        ################################################################################
#
#        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${CUDA_C_FLAGS}")
#        set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${CUDA_EXE_LINKER_FLAGS}")
#
#        ## Add an executable to the project
#        #cuda_add_executable(target ${SOURCES})
#
#        ## CUFFT
#        #if(USE_CUFFT)
#        #    CUDA_ADD_CUFFT_TO_TARGET(target)
#        #endif()
#    endif()
#endfunction()

