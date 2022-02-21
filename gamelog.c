#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

void parseGlobalOptions(int *opt, int argc, char *argv[]);

int main(int argc, char *argv[]) {

    // Ensure command is given
    if (argc == 1) {
        printf("No command given\n");
        return 1;
    }

    int option_index = 0;

    int *opt = malloc(sizeof(char));
    if (opt == NULL) {
        printf("Could not allocate memory for option\n");
        return 1;
    }

    // Create command options
    struct option long_options[] = {
        {"add", required_argument, opt, 'a'},
        {"remove", required_argument, opt, 'r'},
        {"move", required_argument, opt, 'm'},
        {"list", optional_argument, opt, 'l'},
        {0, 0, 0, 0},
    };

    getopt_long(argc, argv, "armu", long_options, &option_index);

    // Ensure option is valid
    if (*opt == '?') {
        printf("Invalid option\n");
        free(opt);
        return 2;
    }

    // Ensure only 1 option entered
    if (getopt_long(argc, argv, "armu", long_options, &option_index) != -1) {
        printf("Only one option allowed\n");
        free(opt);
        return 3;
    }

    // Ensure only 2 arguments when moving
    if (*opt == 'm' && argc != optind + 1) {
        printf("Only two arguments allowed\n");
        free(opt);
        return 4;
    }

    // Ensure max 1 argument for the rest
    else if (*opt != 'm' && argc != optind) {
        printf("Only one argument allowed\n");
        free(opt);
        return 5;
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
        
        // Move game
        case 'm':
            printf("Option --move selected\n");
            break;

        // Show list of games
        case 'l':
            printf("Option --list selected\n");
            break;
    }

    parseGlobalOptions(opt, argc, argv);
    free(opt);
    return 0;
}

void parseGlobalOptions(int *opt, int argc, char *argv[]) {
    struct option long_options[] = {
        {"help", no_argument, opt, 'h'},
        {"version", no_argument, opt, 'v'},
    };

    int option_index = 0;
    getopt_long(argc, argv, "", long_options, &option_index);

    if (*opt == '?') {
        printf("Invalid option\n"); 
    }

    if (getopt_long(argc, argv, "", long_options, &option_index) != -1) {
        printf("Only one option allowed\n");
    }

    switch (*opt) {
        case 'h':
            printf("Option --help selected\n");
            break;
        case 'v':
            printf("Option --version selected\n");
            break;
    }
}
