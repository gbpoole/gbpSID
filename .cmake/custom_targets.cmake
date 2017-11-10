# This file contains all the macros that are used
#   by cmake to specify custom targets

# Create a master list of all source and header files
set(ALL_FILES_PROJECT "" )
list(APPEND ALL_FILES_PROJECT ${INC_FILES_PROJECT} )
list(APPEND ALL_FILES_PROJECT ${SRC_FILES_PROJECT} )

# Add clang-related targets
macro(add_custom_clang)
    # Clang-format
    add_custom_target(
        clang-format
        COMMAND clang-format
        -style=file
        -i
        ${ALL_FILES_PROJECT}
    )
    message(STATUS "   -> clang-format       ; apply the project style standards using clang-tidy")
    
    # Clang-tidy
    add_custom_target(
        clang-tidy-suggest
        COMMAND clang-tidy
        -p ${CMAKE_CURRENT_BINARY_DIR}
        ${SRC_FILES_PROJECT}
    )
    message(STATUS "   -> clang-tidy-suggest ; write clang-tidy suggestions to stdout")
    add_custom_target(
        clang-tidy-fix
        COMMAND clang-tidy
        -p ${CMAKE_CURRENT_BINARY_DIR}
        -fix
        ${SRC_FILES_PROJECT}
    )
    message(STATUS "   -> clang-tidy-fix     ; apply all clang-tidy suggestions in-place ... BE CAREFUL WITH THIS!")
endmacro()

# Add the targets used to generate documentation
macro(add_custom_docs)
    if(GBP_DOCS_BUILD_FOUND)
        # Generate Doxygen documentation for C/C++ code
        set(DOXYGEN_GENERATE_XML   YES)
        set(DOXYGEN_GENERATE_LATEX  NO)
        set(DOXYGEN_GENERATE_HTML   NO)
        set(DOXYGEN_GENERATE_MAN    NO)
        set(DOXYGEN_OUTPUT_DIRECTORY ${Sphinx_BUILD_DIR}/doxygen )
        doxygen_add_docs(docs-doxygen ${ALL_FILES_PROJECT} )
    
        # Convert Doxygen xml to rst for Sphinx
        add_custom_target(
            docs-breathe
            COMMAND mkdir -p ${Sphinx_BUILD_DIR}/breathe
            COMMENT "Perform initialization for Breathe")
    
        # Perform Spinx HTML build
        add_custom_target(
            docs-html 
            COMMAND ${Sphinx_EXECUTABLE}
                -q -b html 
                -c "${Sphinx_BUILD_DIR}"
                -d "${Sphinx_CACHE_DIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}"
                "${Sphinx_RESULTS_DIR}/html"
            COMMENT "Building HTML documentation with Sphinx")
    
        # Perform Spinx PDF build
        add_custom_target(
            docs-pdf
            COMMAND ${Sphinx_EXECUTABLE}
                -q -b latex
                -c "${Sphinx_BUILD_DIR}"
                -d "${Sphinx_CACHE_DIR}"
                "${CMAKE_CURRENT_SOURCE_DIR}"
                "${Sphinx_LATEX_DIR}"
            COMMAND mkdir -p ${Sphinx_RESULTS_DIR}
            COMMAND cd ${Sphinx_LATEX_DIR} && pdflatex ${CMAKE_PROJECT_NAME}
            COMMAND mv "${Sphinx_LATEX_DIR}/${CMAKE_PROJECT_NAME}.pdf" ${Sphinx_RESULTS_DIR}
            COMMENT "Building PDF documentation with Sphinx")
    
        # Generate documentation
        add_custom_target(
            docs
            COMMENT "Building project documentation")
        message(STATUS "   -> docs               ; generate PDF & HTML versions of project documentation")
    
        # Set build dependancies for documentation
        add_dependencies(docs-html docs-doxygen )
        add_dependencies(docs-pdf docs-doxygen )
        add_dependencies(docs-doxygen docs-breathe )
        add_dependencies(docs docs-pdf docs-html )
    else()
        message(STATUS "   -> docs *NOT* added (needed libraries not found)")
    endif()
endmacro()

