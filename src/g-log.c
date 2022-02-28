#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "cmd/cmd.h"

#define USAGE "Use --help to look up valid commands\n"

bool validate_arguments(int argc, struct option opt, int optind, int response);

int main(int argc, char *argv[]) {

    // Allocate memory for flag
    int *opt = malloc(sizeof(int));
    if (opt == NULL) {
        printf("Could not allocate memory for option\n");
        return 1;
    }

    // Create command options
    struct option long_opts[] = {
        {"add", required_argument, opt, 'a'},
        {"remove", no_argument, opt, 'r'},
        {"update", no_argument, opt, 'u'},
        {"list", optional_argument, opt, 'l'},
        {"version", no_argument, opt, 'v'},
        {"help", no_argument, opt, 'h'},
        {0, 0, 0, 0},
    };

    // Initialise variable for options index
    int opt_i = 0;

    // Process command line input
    int response = getopt_long(argc, argv, "a:rul::hv", long_opts, &opt_i);

    // Validate command line input
    bool is_valid = validate_arguments(argc, long_opts[opt_i], optind, response);
    if (!is_valid) {
        printf(USAGE);
        free(opt);
        return 1;
    }

    // Initialize variable to store command line arguments
    char *argument;

    switch(*opt) {
        
        case 'a':

            // Add game to backlog based on input
            argument = argv[optind - 1];
            if (!add(argument)) {
                free(opt);
                return 1;
            }
            break;

        case 'r':

            // Remove game from data
            if (!remove_game()) {
                free(opt);
                return 1;
            }
            break;
        
        case 'u':

            // Update an entry in the backlog
            if (!update()) {
                free(opt);
                return 1;
            }
            break;

        case 'l':

            // Print list based on input
            argument = argc == 3 ? argv[optind] : NULL;
            if (!show_list(argument, true)) {
                free(opt);
                return 1;
            }
            break;

        // Show version
        case 'v':
            print_version();
            break;

        // Show help
        case 'h':
            print_help();
            break;
    }   

    free(opt);
    return 0;
}

bool validate_arguments(int argc, struct option opt, int optind, int response) {

    // Ensure no errors 
    if (response == -1 || response == 63) {
        return false;
    }

    // Validate for no arguments or required arguments
    else if (argc > optind && (opt.has_arg == 0 || opt.has_arg == 1)) {
        return false;
    } 

    // Validate for optional arguments
    else if (argc > optind + 1 && opt.has_arg == 2) {
        return false;
    }
    return true;
}
