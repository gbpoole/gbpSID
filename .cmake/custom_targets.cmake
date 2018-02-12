# This file contains all the macros that are used
#   by cmake to specify custom targets

# Add clang-related targets
macro(add_custom_clang)
    # Create a master list of all source and header files
    # This needs to be done here (rather than when this file
    # is included) because we need to have processed the
    # project tree first, to have a list of files in place.
    set(ALL_FILES_PROJECT "" )
    list(APPEND ALL_FILES_PROJECT ${INC_FILES_PROJECT} )
    list(APPEND ALL_FILES_PROJECT ${SRC_FILES_PROJECT} )

    # Clang-format
    if(ALL_FILES_PROJECT)
        add_custom_target(
            clang-format-check
            COMMAND clang-format
            -style=file
            ${ALL_FILES_PROJECT}
        )
        message(STATUS "   -> clang-format-check ; write clang-format suggestions to stdout")

        add_custom_target(
            clang-format-fix
            COMMAND clang-format
            -style=file
            -i
            ${ALL_FILES_PROJECT}
        )
        message(STATUS "   -> clang-format-fix   ; apply the project style standards using clang-format")

        # Clang-tidy
        add_custom_target(
            clang-tidy-check
            COMMAND clang-tidy
            -p ${CMAKE_CURRENT_BINARY_DIR}
            ${SRC_FILES_PROJECT}
        )
        message(STATUS "   -> clang-tidy-check   ; write clang-tidy suggestions to stdout")
        add_custom_target(
            clang-tidy-fix
            COMMAND clang-tidy
            -p ${CMAKE_CURRENT_BINARY_DIR}
            -fix
            ${SRC_FILES_PROJECT}
        )
        message(STATUS "   -> clang-tidy-fix     ; apply all clang-tidy suggestions in-place ... BE CAREFUL WITH THIS!")
    else()
        add_custom_target(
            clang-format-check
            COMMAND echo No files to run clang-format on.
        )
        message(STATUS "   -> clang-format-check ; *** NO FILES TO PROCESS")

        add_custom_target(
            clang-format-fix
            COMMAND echo No files to run clang-format on.
        )
        message(STATUS "   -> clang-format-fix   ; *** NO FILES TO PROCESS")

        # Clang-tidy
        add_custom_target(
            clang-tidy-check
            COMMAND echo No files to run clang-tidy on.
        )
        message(STATUS "   -> clang-tidy-check   ; *** NO FILES TO PROCESS")
        add_custom_target(
            clang-tidy-fix
            COMMAND echo No files to run clang-tidy on.
        )
        message(STATUS "   -> clang-tidy-fix     ; *** NO FILES TO PROCESS")
    endif()
endmacro()

# Add the targets used to generate documentation
macro(add_custom_docs)
    if(GBP_DOCS_BUILD_FOUND)
        # Create a master list of all source and header files
        # This needs to be done here (rather than when this file
        # is included) because we need to have processed the
        # project tree first, to have a list of files in place.
        # Note that SRC_FILES_PROJECT includes executable files.
        set(ALL_FILES_PROJECT "" )
        list(APPEND ALL_FILES_PROJECT ${INC_FILES_PROJECT} )
        list(APPEND ALL_FILES_PROJECT ${SRC_FILES_PROJECT} )

        # Tell Doxygen to only configure XML.  Sphynx will do the rest.
        set(DOXYGEN_GENERATE_XML   YES)
        set(DOXYGEN_GENERATE_LATEX  NO)
        set(DOXYGEN_GENERATE_HTML   NO)
        set(DOXYGEN_GENERATE_MAN    NO)

        # List the file patterns to ignore when running Doxygen
        list(APPEND DOXYGEN_EXCLUDE_PATTERNS "*/extern/*" )
        list(APPEND DOXYGEN_EXCLUDE_PATTERNS "*/test/*" )
        list(APPEND DOXYGEN_EXCLUDE_PATTERNS "*/build-*/*" )
        list(APPEND DOXYGEN_EXCLUDE_PATTERNS "*/README.md" )

        # Finish Doxygen configuration
        set(DOXYGEN_OUTPUT_DIRECTORY ${PRJ_DOCS_DIR}/build/doxygen )
        doxygen_add_docs(docs-doxygen ${ALL_FILES_PROJECT} )
    
        # Convert Doxygen xml to rst for Sphinx
        add_custom_target(
            docs-breathe
            COMMENT "Perform initialization for Breathe")
    
        # Generate API documentation files
        add_custom_target(
            docs-api
            COMMENT "Generate API documentation files")
        message(STATUS "   -> docs-api           ; generate API documentation files")

        # Set build dependancies for documentation
        add_dependencies(docs-breathe docs-doxygen )
        add_dependencies(docs-api     docs-breathe )

    else()
        message(STATUS "   -> docs *NOT* added (needed libraries not found)")
    endif()
endmacro()
