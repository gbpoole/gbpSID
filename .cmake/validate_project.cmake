macro(validate_project)

    # Set this to ON if an error is found.
    # We will message with SEND_ERROR in what
    # follows so that we can check for all
    # needed macros and variables before quiting.
    set(ERROR_FOUND OFF)

    # Check that the macro project_options() has been defined in project.cmake
    if(NOT COMMAND project_options)
        message( SEND_ERROR "project_options() has not been set in project.cmake")
        set(ERROR_FOUND ON)
    endif()

    # Check that the macro project_dependencies() has been defined in project.cmake
    if(NOT COMMAND project_dependencies)
        message( SEND_ERROR "project_dependencies() has not been set in project.cmake")
        set(ERROR_FOUND ON)
    endif()

    # Check that a project name has been defined
    if(NOT COMMAND project_init)
        message( SEND_ERROR "project_init() has not been set in project.cmake")
        set(ERROR_FOUND ON)
    endif()

    # Check that a project name has been defined
    project_init()
    if(NOT _PROJECT_NAME)
        message( SEND_ERROR "_PROJECT_NAME has not been set by 'project_init()'.")
        set(ERROR_FOUND ON)
    endif()

    # Stop Cmake if an error was encountered
    if(ERROR_FOUND)
        message( FATAL_ERROR "Please fix the project initialization in project.cmake.")
    endif()
endmacro()
