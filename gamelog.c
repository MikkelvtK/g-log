#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "helpers.h"
#include "options.h"
#include "data.h"

char *PATHNAME = "gamelog.txt";

int main(int argc, char *argv[]) {

    // Ensure command is given
    if (argc == 1) {
        printf("No command given\n");
        return 1;
    }

    // Load data from file
    FILE *file = NULL;
    load_from_file(file, PATHNAME);

    // Allocate memory for flag
    int *opt = malloc(sizeof(char));
    if (opt == NULL) {
        printf("Could not allocate memory for option\n");
        return 1;
    }

    // Create command options
    struct option long_options[] = {
        {"add", required_argument, opt, 'a'},
        {"remove", required_argument, opt, 'r'},
        {"update", required_argument, opt, 'u'},
        {"list", optional_argument, opt, 'l'},
        {"version", no_argument, opt, 'v'},
        {"help", no_argument, opt, 'h'},
        {0, 0, 0, 0},
    };

    // Initialise variable for index
    int option_index = 0;

    // Parse option in command line
    if (getopt_long(argc, argv, "a:r:u:l::hv", long_options, &option_index) != -1) {

        // ----- insert validate command function
        
        switch(*opt) {

            // Add game 
            case 'a':
                add(argv[optind - 1]);
                break;

            // Remove game
            case 'r':
                printf("Option --remove selected\n");
                break;
            
            // update game
            case 'u':
                printf("Option --update selected\n");
                break;

            // Show list of games
            case 'l':
                printf("Option --list selected\n");
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
                printf("Use --help to look up valid commands\n");
                free(opt);
                return 1;
        }   
    }

    print_data();

    // Save data to file and close app
    save_to_file(file, PATHNAME);
    unload_data();
    free(opt);
    return 0;
}

