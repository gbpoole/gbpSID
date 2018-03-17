# Set options and dependencies
set(_PROJECT_NAME  "gbpSID")
macro(project_options_and_dependencies)

    #========= Set project-specific options, switchable through environment variables ========
    define_project_env_variable(USE_DOUBLE "Use double precision liberally"    OFF ON OFF)
    define_project_env_variable(SID_DEBUG  "Enable SID debugging information"  OFF ON OFF)

    #=========== Add 3rd-party libraries ===========
    # (look in gbpBuild/cmake/3rd_party.cmake for a list of supported libraries)
    message(STATUS "")
    message(STATUS "Initializing 3rd-party libraries...")
    
    # List of *requested* 3rd-Party libraries (and their defaults)
    set_3rd_party_requested("GBP_DOCS_BUILD" ON)
    
    # List of *optional* 3rd-Party libraries (and their defaults)
    set_3rd_party_optional("MPI"    ON)
    set_3rd_party_optional("MPI_IO" OFF)
    set_3rd_party_optional("CUDA"   OFF)
    
    # Print status message
    message(STATUS "Finished initializing 3rd-party libraries.")
endmacro()
