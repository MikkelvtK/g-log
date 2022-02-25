#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "lib/helpers.h"
#include "lib/data.h"

const char *BUCKETS[4] = {"Backlog", "In progress", "Finished", "Paused"};

bool add(char *game) {

    // Load data from file
    FILE *file = NULL;
    if (!load_from_file(file)) {
        printf("Failed to load data from file\n");
        return false;
    }

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

    // Insert data to linked list
    insert_data(new_entry);

    // Save data to file
    if (!save_to_file(file)) {
        printf("Failed to save data to file\n");
        unload_data();
        return false;
    }

    // Free data from memory
    unload_data();

    return true;
}

bool show_list(char *filter) {
    
    // Load data from file
    if (!load_from_file()) {
        printf("Failed to load data from file\n");
        return false;
    }

    // Clear terminal
    system("cls");

    // Print table header
    print_table_header();

    // Fill table with data
    print_data(filter);

    // Print footer of table
    print_table_footer();

    return true;
}
