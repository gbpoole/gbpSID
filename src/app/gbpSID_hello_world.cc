#define _MAIN
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpSID.h>
#include <gbpSID_app.hh>

namespace gbpApp {

    // Define the arguments for this application
    struct arg_list {
        int  enthusiastic;
        char sender[64];
    };

    // Set default values
    arg_list args = {GBP_FALSE,"someone"};

    // Create a personalised derived class for this application from
    // the base class defined in "gbpApp.hh".
    class application : public gbpSID::application {
      public:
        // Define command line options for this application
        void define_arguments() {
            cli |= clara::Opt([&](bool) { args.enthusiastic = GBP_TRUE; })["-e"]["--enthusiastic"]("add enthusiasm to the message") |
                   clara::Arg(args.sender, "sender")("message sender");
        }

        // This method executes the application's logic
        int execute() {

            // Print message
            char msg[256];
            sprintf(msg,"Hello world, from %s",args.sender);
            if(args.enthusiastic)
                SID_log("%s!",SID_LOG_COMMENT,msg);
            else
                SID_log("%s.",SID_LOG_COMMENT,msg);

            // Exit cleanly
            return (SID_ERROR_NONE);
        }

        // Somewhat annoyingly, we must always define a derived-class constructor,
        // even-though the base-class constructor does everything we want.
        application(int argc, char **argv) : gbpSID::application(argc, argv){};
    };
} // namespace gbpApp

// Include main() for applications.  They must have a
// #define _MAIN declared before including gbpApp.hh
#include <gbpSID_app_main.hh>
