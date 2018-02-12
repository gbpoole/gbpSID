macro(init_validate)
    # Set this to ON if an error is found.
    # We will message with SEND_ERROR in what
    # follows so that we can check for all
    # needed macros and variables before quiting.
    set(ERROR_FOUND OFF)

    # Check that the macro project_options_and_dependancies()
    # has been defined in project.cmake
    if(NOT COMMAND project_options_and_dependancies)
        message( SEND_ERROR "project_options_and_dependancies() has not been set in project.cmake")
        set(ERROR_FOUND ON)
    endif()

    # Check that a project name has been defined
    if(NOT GBP_PROJECT_NAME)
        message( SEND_ERROR "GBP_PROJECT_NAME has not been set by project_init()")
        set(ERROR_FOUND ON)
    endif()

    # Stop Cmake if an error was encountered
    if(ERROR_FOUND)
        message( FATAL_ERROR "Please fix the project initialization in project.cmake.")
    endif()
endmacro()
