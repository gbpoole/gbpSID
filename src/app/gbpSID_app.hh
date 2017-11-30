#ifndef GBPSID_APP_H
#define GBPSID_APP_H

#include <clara.hpp>
#include <gbpSID_core.h>
#include <iostream>

namespace gbpSID {
    class application {
      protected:
        // Arguments as passed from the command line
        int    _argc;
        char **_argv;
        bool   _print_syntax;

        // Command-line parser
        clara::Parser cli;

      public:
        // Initialize the argument parser
        void init_arguments(){
            // Add executable name to Clara parser
            std::string pname(_argv[0]);
            cli |= clara::ExeName( pname );
        }

        // Finalize the argument parser
        void finalize_arguments(){
            // Add 'help' to the parser
            cli |= clara::Help(_print_syntax);
        }

        // Application constructor
        application(int argc, char **argv) : _argc(argc), _argv(argv), _print_syntax(GBP_FALSE) {
            // Initialize SID
            SID_Init(&_argc, &_argv, NULL);

            // Inititalize the argument parser
            init_arguments();
        }

        // Application destructor
        ~application() {
            SID_Finalize();
        }

        // These two virtual functions must be personalised for
        // every application:

        // 1) This function defines the application-specific command line arguments
        virtual void define_arguments() = 0;

        // 2) This function executes the application
        virtual int execute() = 0;

        // This function performs the final command-line parsing
        int parse_arguments() {
            int r_val = SID_ERROR_NONE;
            auto result = cli.parse(clara::Args(_argc, _argv));
            if(!result) {
                if(SID.I_am_Master){
                    std::cerr << "SYNTAX ERROR in {";
                    int i_arg=0;
                    std::cerr << std::string(_argv[i_arg++]);
                    for(;i_arg<_argc;i_arg++)
                        std::cerr << " " << std::string(_argv[i_arg]);
                    std::cerr << "}" << std::endl << std::endl;
                }
                r_val|=SID_ERROR_SYNTAX|SID_ERROR_PRINT_SYNTAX;
            }
            if(_print_syntax)
                r_val|=SID_ERROR_PRINT_SYNTAX;
            return(r_val);
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
                // TODO: Report syntax, run config, etc.
                r_val |= execute();
                // TODO: Report run summary, etc.
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
            if(SID.I_am_Master)
                cli.writeToStream(std::cout);
        }
    };

} // namespace gbpSID
#endif
