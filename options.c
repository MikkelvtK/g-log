#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "helpers.h"
#include "data.h"

const char *BUCKETS[4] = {"Backlog", "In progress", "Finished", "Paused"};

void add(char *game) {

    // Get current date
    char date[DATE_SIZE];
    format_date(date, DATE_SIZE);

    // Initialise new entry 
    entry new_entry;

    // Copy data over
    strcpy(new_entry.name, game);
    strcpy(new_entry.bucket, BUCKETS[0]);
    strcpy(new_entry.added_on, date);
    strcpy(new_entry.updated_on, date);

    // Insert new entry in linked list
    bool success = insert_data(new_entry);

    // Give feedback to user
    if (success) {
        printf("Succesfully added new game");
        return;
    }
    printf("Failed to add game");
}

void show_list(char *filter) {
    
    // Clear terminal
    system("cls");

    // Print table header
    print_table_header();

    // Fill table with data
    print_data(filter);

    // Print footer of table
    print_table_footer();
}
