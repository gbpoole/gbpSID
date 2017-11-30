// This is the main intended to be used for all
//    gbpSID::application-inherited classes
int main(int argc, char *argv[]) {
    // Throw exceptions on high-level errors
    int r_val = EXIT_SUCCESS;
    try {
        // Create an application instance.  This calls SID_Init() and parses
        //    the arguments.  Later, the deconstructor calls SID_Finalize()
        gbpApp::application app(argc, argv);

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
