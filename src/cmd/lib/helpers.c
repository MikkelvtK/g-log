#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "helpers.h"

void format_date(char *d, int s) {

    // Create tmp to store date
    char tmp[s];

    // Get current time
    const time_t t = time(NULL);
    struct tm *now = localtime(&t);

    // Format date
    strftime(tmp, sizeof(tmp), "%x - %I:%M%p", now);

    // Copy string to argument
    strcpy(d, tmp);
}

void print_table_header() {

    // Print top line
    printf("\n\n\t");
    for (int i = 0; i < 118; i++) {
        printf("\xF0");
    }
    printf("\n");

    // Print columns
    char *row = "\t%8s %26s %26s %26s %26s \n";
    printf(row, "INDEX", "GAME", "BUCKET", "ADDED ON", "UPDATED ON");

    // Print bottom line
    printf("\t");
    for (int i = 0; i < 118; i++) {
        printf("\xF0");
    }
    printf("\n");
}

void print_table_footer() {

    // Print left corner
    printf("\t\xC8");

    // Print line
    for (int i = 0; i < 116; i++) {
        printf("\xCD");
    }

    // Print right corner
    printf("\xBC\n\n");
}

void to_upper(char *word) {

    // Change letters to uppercase
    for (int i = 0; i < strlen(word); i++) {
        word[i] = toupper(word[i]);
    }
}
