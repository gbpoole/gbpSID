#include <clara.hpp>
#include <iostream>

// _MAIN absolutely must be declared before including gbpSID.h here
#define _MAIN
#include <gbpSID.h>

namespace gbpSID {
    class application {
      protected:
        // Arguments as passed from the command line
        int    _argc;
        char **_argv;

        // A flag indicating if the application's syntax needs to be printed
        bool   _print_syntax;

        // Command-line parser
        clara::Parser cli;
        std::string   instructions_text;

      public:
        // These two functions must be personalised for every application:
        // ---------------------------------------------------------------
        // 1) This function defines the application-specific command line arguments
        void define_arguments();
        // 2) This function executes the application.  Make sure to return SID_ERROR_NONE if no error.
        int execute();
        // ----------------------------------------------------------------------

        // Initialize the argument parser
        void init_arguments() {
            // Add executable name to Clara parser
            std::string pname(_argv[0]);
            cli |= clara::ExeName(pname);
        }

        // Finalize the argument parser
        void finalize_arguments() {
            // Add 'help' to the parser
            cli |= clara::Help(_print_syntax);
        }

        // Application constructor
        application(int argc, char *argv[]) : _argc(argc), _argv(argv), _print_syntax(GBP_FALSE) {
            // Initialize SID
            SID_Init(&_argc, &_argv, NULL);

            // Inititalize the argument parser
            init_arguments();
        }

        // Application destructor
        ~application() {
            SID_Finalize();
        }

        // This function performs the final command-line parsing
        int parse_arguments() {
            int  r_val  = SID_ERROR_NONE;
            auto result = cli.parse(clara::Args(_argc, _argv));
            if(!result) {
                if(SID.I_am_Master) {
                    std::cerr << "SYNTAX ERROR in {";
                    int i_arg = 0;
                    std::cerr << std::string(_argv[i_arg++]);
                    for(; i_arg < _argc; i_arg++)
                        std::cerr << " " << std::string(_argv[i_arg]);
                    std::cerr << "}" << std::endl << std::endl;
                }
                r_val |= SID_ERROR_SYNTAX | SID_ERROR_PRINT_SYNTAX;
            }
            if(_print_syntax)
                r_val |= SID_ERROR_PRINT_SYNTAX;
            return (r_val);
        }

        // This is the meat of the application
        int operator()() {
            // Initialize an error code
            int r_val = SID_ERROR_NONE;

            // Define application arguments
            define_arguments();

            // Finalize argument parser
            finalize_arguments();

            // Parse application arguments
            r_val |= parse_arguments();

            // Execute the application if things
            //   have run cleanly until now.
            if(r_val == SID_ERROR_NONE) {
                // Write the details of the run, etc. to log
                SID_log_header();
                // Execute functionality of application
                r_val |= execute();
                // Write summary of run statistics
                SID_log_footer();
            }

            // Display syntax information if needed
            else if(SID_CHECK_BITFIELD_SWITCH(r_val, SID_ERROR_PRINT_SYNTAX)) {
                display_help();
                // This flag is not meant to be part of any error codes
                SID_DISABLE_BITFIELD_SWITCH(r_val, SID_ERROR_PRINT_SYNTAX);
            }

            // Return an error code.  Make sure it is SID_ERROR_NONE for success.
            return (r_val);
        }

        // This method generates a syntax help message
        //    based on what is defined in the derived class'
        //    'parse_arguments()' function.
        void display_help() {
            if(SID.I_am_Master){
                // Display usage
                cli.writeToStream(std::cout);
                // The following space is needed for parsing in Sphinx docs
                std::cout << "\n";
                // Display instructions
                std::cout << instructions_text << std::endl;
            }
        }
    };

} // namespace gbpSID

// This is the main() used for all gbpSID applications
int main(int argc, char *argv[]) {
    // Throw exceptions on high-level errors
    int r_val = EXIT_SUCCESS;
    try {
        // Create an application instance.  This calls SID_Init() and parses
        //    the arguments.  Later, the deconstructor calls SID_Finalize()
        gbpSID::application app(argc, argv);

        // Execute the application
        int SID_r_val = app();

        // Check for a clean exit.  Throw an exception otherwise.
        if(SID_r_val != SID_ERROR_NONE)
            throw SID_r_val;
    }

    // Catch exceptions.  Set and report an error code
    //    if exceptions have been thrown.
    catch(std::exception &e) {
        std::cerr << "\nError: " << e.what() << "\n\n";
        r_val = EXIT_FAILURE;
    }

    // Return EXIT_SUCCESS or EXIT_FAILURE
    return r_val;
}
