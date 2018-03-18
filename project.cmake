macro(project_init)
    set(_PROJECT_NAME "gbpSID")
endmacro()

macro(project_options)
    #========= Set project-specific options, switchable through environment variables ========
    define_project_env_variable(USE_DOUBLE "Use double precision liberally"    OFF ON OFF)
    define_project_env_variable(SID_DEBUG  "Enable SID debugging information"  OFF ON OFF)
endmacro()

macro(project_dependencies)
    #=========== Add 3rd-party libraries ===========
    set_3rd_party_requested("GBP_DOCS_BUILD" ON)
    set_3rd_party_optional("MPI"    ON)
    set_3rd_party_optional("MPI_IO" OFF)
    set_3rd_party_optional("CUDA"   OFF)
endmacro()
