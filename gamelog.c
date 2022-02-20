#include <stdio.h>
#include <getopt.h>
#include <string.h>

int main(int argc, char *argv[]) {

    // Ensure command is given
    if (argc == 1) {
        printf("No command given\n");
        return 1;
    }

    // Create command options
    struct option long_options[] = {
        {"add", required_argument, 0, 'a'},
        {"remove", required_argument, 0, 'r'},
        {"move", required_argument, 0, 'm'},
        {"update", required_argument, 0, 'u'},
        {"help", no_argument, 0, 'h'},
        {"list", optional_argument, 0, 'l'},
        {"version", no_argument, 0, 'v'},
        {0, 0, 0, 0},
    };

    // Parse chosen option
    int option_index = 0;
    int opt = getopt_long(argc, argv, "armu", long_options, &option_index);

    // Ensure option is valid
    if (opt == '?') {
        printf("Invalid option\n");
        return 2;
    }

    // Ensure only 1 option entered
    if (getopt_long(argc, argv, "armu", long_options, &option_index) != -1) {
        printf("Only one option allowed\n");
        return 3;
    }

    // Ensure max 1 argument is given
    if (argc > optind) {
        printf("Only one argument allowed\n");
        return 4;
    }

    switch(opt) {
        case 'a':
            printf("Option --add selected\n");
            break;
        case 'r':
            printf("Option --remove selected\n");
            break;
        case 'm':
            printf("Option --move selected\n");
            break;
        case 'u':
            printf("Option --update selected\n");
            break;
        case 'h':
            printf("Option --help selected\n");
            break;
        case 'l':
            printf("Option --list selected\n");
            break;
        case 'v':
            printf("Option --version selected\n");
            break;
    }
    return 0;
}