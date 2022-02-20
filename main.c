#include <stdio.h>
#include <getopt.h>

int main(int argc, char *argv[]) {

    struct option long_options[] = {
        {"add", no_argument, 0, 'a'},
        {"remove", no_argument, 0, 'r'},
    };

    int option_index = 0;
    int c = getopt_long(argc, argv, "ar", long_options, &option_index);

    printf("The return vallue of getopt_long is: %i\n", c);
    printf("The option selected by 'option_index' is: %s\n", long_options[option_index].name);

    switch(c) {

        case 'a':
            printf("The command --add was initiated.\n");
        case 'r':
            printf("The command --remove was initiated.\n") ;
    };

    return 0;
}