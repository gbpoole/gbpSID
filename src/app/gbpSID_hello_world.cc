#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gbpSID_app.hh>

using namespace gbpSID;

// Define the arguments for this application
struct arg_list {
    int  enthusiastic;
    char sender[64];
};

// Set default values
arg_list args = {GBP_FALSE,"someone"};

// Build command-line parser for this application.
// Note that options for help and the executable name
// are added to the parser by default.  No need to 
// worry about either of those.
void application::define_arguments() {
    cli |= clara::Opt([&](bool) { args.enthusiastic = GBP_TRUE; })["-e"]["--enthusiastic"]("add enthusiasm to the message");
    cli |= clara::Arg(args.sender, "sender")("message sender").required();
    instructions_text += "This program demonstrates how to configure and use an application program with the gbpSID application class.";
}

// This method executes the application's logic
int application::execute() {

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
