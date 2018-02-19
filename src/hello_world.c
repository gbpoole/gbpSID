#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SENDER_DEFAULT "gbpSID\0"
#define ERROR_SYNTAX 1

void print_help(int argc, char *argv[], _Bool flag_description);
void print_help(int argc, char *argv[], _Bool flag_description) {
    // Print usage information
    printf("usage:\n  %s <sender> [options]\n\n", argv[0]);
    printf("where options are:\n");
    printf("  -e, --enthusiastic    add enthusiasm to the message\n");
    printf("  -?, -h, --help        display usage information\n\n");
    if(flag_description)
        printf("This program prints a greeting from someone with optional entusiasm.\n");
}

int main(int argc, char *argv[]) {
    // Scan arguments for switches
    _Bool  flag_enthusiasm = 0;
    _Bool  flag_help       = 0;
    _Bool *parg_mask       = (_Bool *)malloc(argc * sizeof(_Bool));
    for(int i_arg = 1; i_arg < argc; i_arg++) {
        if(!strcmp(argv[i_arg], "-?") || !strcmp(argv[i_arg], "-h") || !strcmp(argv[i_arg], "--help")) {
            flag_help        = 1;
            parg_mask[i_arg] = 0;
        } else if(!strcmp(argv[i_arg], "-e") || !strcmp(argv[i_arg], "--enthusiastic")) {
            flag_enthusiasm  = 1;
            parg_mask[i_arg] = 0;
        } else if(!strcmp(argv[i_arg], "-")) {
            printf("Unrecognized option (%s).\n\n", argv[i_arg]);
            print_help(argc, argv, 0);
            free(parg_mask);
            return (ERROR_SYNTAX);
        } else
            parg_mask[i_arg] = 1;
    }

    // Print usage information if requested
    if(flag_help) {
        print_help(argc, argv, 1);
        free(parg_mask);
        return (EXIT_SUCCESS);
    }

    // Check the number of arguments and determine the sender
    int   n_flags = flag_enthusiasm + flag_help;
    int   n_pargs = argc - n_flags - 1;
    char *sender  = NULL;
    if(n_pargs == 1) {
        for(int i_arg = 0; i_arg < argc; i_arg++) {
            if(parg_mask[i_arg]) {
                sender = (char *)malloc(sizeof(char) * strlen(argv[i_arg]));
                strcpy(sender, argv[i_arg]);
                break;
            }
        }
    } else if(n_pargs == 0) {
        sender = (char *)malloc(sizeof(char) * strlen(SENDER_DEFAULT));
        sprintf(sender,"%s", SENDER_DEFAULT);
    } else {
        printf("Invalid number of positional arguments (%d).\n\n", n_pargs);
        print_help(argc, argv, 0);
        free(parg_mask);
        return (ERROR_SYNTAX);
    }

    // Print message
    printf("Hello world, from %s", sender);
    if(flag_enthusiasm)
        printf("!\n");
    else
        printf(".\n");

    free(sender);
    free(parg_mask);
    return (EXIT_SUCCESS);
}
