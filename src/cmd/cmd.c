#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "lib/helpers.h"
#include "lib/data.h"
#include "lib/errors.h"

char *BUCKETS[4] = {"Backlog", "In progress", "Finished", "Paused"};

bool add(char *game) {

    // Initialise to store error handling 
    int error;

    // Load data from file
    error = load_from_file();
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        return false;
    }

    // Get current date
    char *date = malloc(DATE_SIZE);
    if (date == NULL) {
        printf("Error: %i. %s\n", 0, errors[0]);
    }
    format_date(date, DATE_SIZE);

    // Initialise new entry 
    entry new_entry;

    // Copy data over
    strcpy(new_entry.name, game);
    strcpy(new_entry.bucket, BUCKETS[0]);
    strcpy(new_entry.added_on, date);
    strcpy(new_entry.updated_on, date);

    // Insert data to linked list
    error = insert_data(new_entry);
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(date);
        unload_data();
        return false;
    }

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(date);
        unload_data();
        return false;
    }

    // Free data from memory
    unload_data();

    // Give feedback to user
    char copy[strlen(game) + 1];
    strcpy(copy, game);
    to_upper(copy);
    printf("---SUCCESSFULLY ADDED %s---\n", copy);
    free(date);
    return true;
}

bool show_list(char *filter, bool unload) {
    
    // Initialise to store error handling 
    int error;

    // Load data from file
    error = load_from_file();
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
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

    // Free data from memory
    if (unload) {
        unload_data();
    }
    return true;
}

bool remove_game() {

    // initialise variables
    int index;
    int error;

    // Show all data
    show_list(NULL, false);

    // Ask for user input
    printf("\n");
    printf("Please enter the index of the game that you want to remove from G-Log\n");
    printf("Index: ");
    scanf("%i", &index);

    // Allocate memory for name selected game
    char *game = malloc(LENGTH);
    if (game == NULL) {
        printf("Error: %s", errors[0]);
        return false;
    }

    // Remove the game from the data
    error = remove_data(index, game);
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(game);
        unload_data();
        return false;
    } 

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(game);
        unload_data();
        return false;
    }

    // Free data from memory
    unload_data();

    // Give user feedback
    to_upper(game);
    printf("---SUCCESSFULLY REMOVED %s---\n", game);
    free(game);
    return true;
}   

bool update() {

    // initialise variables
    int index_game;
    int index_status;
    int error;

    // Get date
    char *date = malloc(DATE_SIZE);
    if (date == NULL) {
        printf("Error: %i. %s\n", 0, errors[0]);
    }
    format_date(date, DATE_SIZE);

    // Print all data
    show_list(NULL, false);

    // Ask for user input
    printf("\n");
    printf("Please enter the index of the game that you want to update in G-Log\n");
    printf("Index: ");
    scanf("%i", &index_game);
    system("cls");

    // Print available statusses
    for (int i = 0; i < 4; i++){
        printf("%i. %s\n", i, BUCKETS[i]);
    }

    // Ask for user input
    printf("\n");
    printf("Please enter the index of the status you want to give\n");
    printf("Index: ");
    scanf("%i", &index_status);
    printf("\n");

    // Allocate memory for name selected game
    char *game = malloc(LENGTH);
    if (game == NULL) {
        printf("Error: %s", errors[0]);
        free(date);
        return false;
    }

    // Update data 
    error = update_data(index_game, BUCKETS[index_status], date, game);
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(date);
        unload_data();
        return false;
    }

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        printf("Error: %i. %s\n", error, errors[error - 1]);
        free(game);
        free(date);
        unload_data();
        return false;
    }

    // Give feedback to user
    to_upper(game);
    printf("---SUCCESSFULLY UPDATED %s---\n", game);

    unload_data();
    free(game);
    free(date);
    return true;
}