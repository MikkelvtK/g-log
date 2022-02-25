#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#include "cmd/cmd.h"

#define USAGE "Use --help to look up valid commands\n"

bool validate_arguments(int argc, struct option opt, int optind);

int main(int argc, char *argv[]) {

    // Ensure command is given
    if (argc == 1) {
        printf("No command given\n");
        return 1;
    }

    // Allocate memory for flag
    int *opt = malloc(sizeof(char));
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

    // Initialise variable for index
    int opt_i = 0;

    // Parse option in command line
    if (getopt_long(argc, argv, "a:r:u:l::hv", long_opts, &opt_i) != -1) {

        // Validate command line arguments 
        if (!validate_arguments(argc, long_opts[opt_i], optind)) {
            printf(USAGE);
            free(opt);
            return 1;
        } 

        // Initiate argument for later use
        char *argument;

        switch(*opt) {
            
            // Add game 
            case 'a':

                // Add game to backlog based on input
                argument = argv[optind - 1];
                if (!add(argument)) {
                    free(opt);
                    return 1;
                }

                break;

            // Remove game
            case 'r':

                // Remove game from data
                if (!remove_game()) {
                    free(opt);
                    return 1;
                }

                break;
            
            // update game
            case 'u':

                if (!update()) {
                    free(opt);
                    return 1;
                }

                break;

            // Show list of games
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
                printf("Option --version selected\n");
                break;

            // Show help
            case 'h':
                printf("Option --help selected\n");
                break;

            // Default when option is not recognized
            default: 
                printf(USAGE);
                free(opt);
                return 1;
        }   
    }

    free(opt);
    return 0;
}

bool validate_arguments(int argc, struct option opt, int optind) {

    // Validate for no arguments or required arguments
    if (argc > optind && (opt.has_arg == 0 || opt.has_arg == 1)) {
        return false;
    } 

    // Validate for optional arguments
    else if (argc > optind + 1 && opt.has_arg == 2) {
        return false;
    }
    return true;
}
