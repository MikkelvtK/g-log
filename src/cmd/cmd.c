#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cmd.h"
#include "lib/helpers.h"
#include "lib/data.h"
#include "lib/errors.h"

char *STATUS[] = {"Backlog", "In progress", "Finished", "Paused"};

bool add(char *game) {

    // Initialise to store error handling 
    int error;

    // Load data from file
    error = load_from_file();
    if (error != 0) {
        print_error(error);
        return false;
    }

    // Get current date
    char *date = malloc(DATE_SIZE);
    if (date == NULL) {
        print_error(1);
    }
    format_date(date, DATE_SIZE);

    // Initialise new entry 
    entry new_entry;

    // Copy data over
    strcpy(new_entry.name, game);
    strcpy(new_entry.status, STATUS[0]);
    strcpy(new_entry.added_on, date);
    strcpy(new_entry.updated_on, date);

    // Insert data to linked list
    error = insert_data(new_entry);
    if (error != 0) {
        print_error(error);
        free(date);
        unload_data();
        return false;
    }

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        print_error(error);
        free(date);
        unload_data();
        return false;
    }

    // Give feedback to user
    to_upper(game);
    printf("---SUCCESSFULLY ADDED %s---\n", game);

    // Free data from memory
    free(date);
    unload_data();
    return true;
}

bool show_list(char *filter, bool unload) {
    
    // Initialise to store error handling 
    int error;

    // Load data from file
    error = load_from_file();
    if (error != 0) {
        print_error(error);
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
    char *question;
    int index;
    int error;

    // Show all data
    show_list(NULL, false);

    // Ask for user input
    question = "Please enter the index of the game that you want to remove from G-Log";
    index = ask_input(question);

    // Allocate memory for name selected game
    char *game = malloc(LENGTH);
    if (game == NULL) {
        print_error(1);
        return false;
    }

    // Remove the game from the data
    error = remove_data(index, game);
    if (error != 0) {
        print_error(error);
        free(game);
        unload_data();
        return false;
    } 

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        print_error(error);
        free(game);
        unload_data();
        return false;
    }

    // Give user feedback
    to_upper(game);
    printf("---SUCCESSFULLY REMOVED %s---\n", game);

    // Free data from memory
    unload_data();
    free(game);
    return true;
}   

bool update() {

    // initialise variables
    char *question;
    int index_game;
    int index_status;
    int error;

    // Get date
    char *date = malloc(DATE_SIZE);
    if (date == NULL) {
        print_error(1);
        return false;
    }
    format_date(date, DATE_SIZE);

    // Print all data
    show_list(NULL, false);

    // Ask for user input
    question = "Please enter the index of the game that you want to update in G-Log";
    index_game = ask_input(question);

    // Print available statusses
    printf("Status choices:\n");
    for (int i = 0; i < 4; i++) {
        printf("%i. %s\n", i, STATUS[i]);
    }

    // Ask for user input
    question = "Please enter the index of the status you want to give";
    index_status = ask_input(question);

    // Allocate memory for name selected game
    char *game = malloc(LENGTH);
    if (game == NULL) {
        print_error(1);
        free(date);
        return false;
    }

    // Update data 
    error = update_data(index_game, STATUS[index_status], date, game);
    if (error != 0) {
        print_error(error);
        free(game);
        free(date);
        unload_data();
        return false;
    }

    // Save data to file
    error = save_to_file();
    if (error != 0) {
        print_error(error);
        free(game);
        free(date);
        unload_data();
        return false;
    }

    // Give feedback to user
    to_upper(game);
    printf("---SUCCESSFULLY UPDATED %s---\n", game);

    // Free memory
    unload_data();
    free(game);
    free(date);
    return true;
}

void print_version() {
    printf("G-Log / version 1.0.0 / <date>\n");
}