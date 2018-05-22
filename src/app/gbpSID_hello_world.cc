#include <stdio.h>
#include <stdlib.h>
#include <string>

// Define the arguments for this application.
// This needs to be done before including 'gbpSID_app.hh'
struct arg_list {
    std::string sender;
    int         enthusiastic;
};

// This include sets-up the application with the
// structure given above intended to be used to
// store all needed cmdl arguments and options.
#include <gbpSID_app.hh>
using namespace gbpSID;

// Build command-line parser for this application.
// Note that options for help and the executable name
// are added to the parser by default.  No need to 
// worry about either of those.
void application::define_arguments() {
    // Set default values
    args = {"someone",GBP_FALSE};
    // Add options
    cli |= clara::Opt([&](bool) { args.enthusiastic = GBP_TRUE; })["-e"]["--enthusiastic"]("add enthusiasm to the message");
    // Add arguments
    cli |= clara::Arg(args.sender, "sender")("message sender").required();
    // Add instructions text
    instructions_text += "This program demonstrates how to configure and use an application program with the gbpSID application class.";
}

// This method executes the application's logic
int application::execute() {

    // Compose message
    std::string msg="Hello world, from "+args.sender;
    if(args.enthusiastic)
        msg+="!";
    else
        msg+=".";

    // Print message
    SID_log(msg.c_str(),SID_LOG_COMMENT|SID_LOG_ALLRANKS);

    // Exit cleanly.  Make sure SID_ERROR_NONE is
    // returned on a clean exit.
    return (SID_ERROR_NONE);
}
