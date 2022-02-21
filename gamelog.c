#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    // Ensure command is given
    if (argc == 1) {
        printf("No command given\n");
        return 1;
    }

    // Initialise variable for index
    int option_index = 0;

    // Free memory for flag
    int *opt = malloc(sizeof(char));
    if (opt == NULL) {
        printf("Could not allocate memory for option\n");
        return 2;
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

    // Parse option
    getopt_long(argc, argv, "a:r:u:l::", long_options, &option_index);

    // Ensure option is valid
    if (*opt == '?') {
        printf("Invalid option\n");
        free(opt);
        return 3;
    }

    // Ensure only 1 option entered
    if (getopt_long(argc, argv, "a:r:u:l::", long_options, &option_index) != -1) {
        printf("Only one option allowed\n");
        free(opt);
        return 4;
    }

    switch(*opt) {

        // Add game 
        case 'a':
            printf("Option --add selected\n");
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
    }

    free(opt);
    return 0;
}

