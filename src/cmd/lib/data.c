#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

const char *PATHNAME = "D:/Development/C/cProjects/cs50FinalProject/data/gamelog.txt";

int insert_data(entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        return 1;
    }

    // Fill new node with data
    new_entry->game = g;
    new_entry->next = NULL;

    // NULL check
    if (data == NULL) {
        data = new_entry;
        data->index = 0;
        return 0;
    }

    // Initialise temp head
    node *tmp = data;

    // Traverse the list to the end
    while (tmp->next != NULL) {
        tmp = tmp->next;
    }

    // Insert new node
    tmp->next = new_entry;
    new_entry->index = tmp->index + 1;
    return 0;
}

int remove_data(int i, char *name) {

    // NULL check
    if (data == NULL) {
        return 2;
    }

    // Initialise temp and cursor heads
    node *tmp = data;
    node *cursor = data;

    // Remove node if head itself has index
    if (cursor->index == i) {
        data = cursor->next;
        strcpy(name, cursor->game.name);
        free(cursor);
        return 0;
    }

    // Search for node with index
    while (cursor != NULL && cursor->index != i) {
            tmp = cursor;
            cursor = cursor->next;
    }

    // Return if node with index is not in list
    if (cursor == NULL) {
        return 3;
    }

    // Remove node with index
    tmp->next = cursor->next;
    strcpy(name, cursor->game.name);
    free(cursor);
    return 0;
}

void print_data(char *filter) {
    
    // Initialise temp head
    node *tmp = data;
    
    // format row
    char *row = "\t\xBA%7i \xB3%25s \xB3%25s \xB3%25s \xB3%25s \xBA\n";

    // Check if results are found
    int results = 1;

    while (tmp != NULL) {

        int index = tmp->index;
        char *name = tmp->game.name;
        char *bucket = tmp->game.bucket;
        char *added_on = tmp->game.added_on;
        char *updated_on = tmp->game.updated_on;

        // Check if node matches filter
        if (filter == NULL || strcmp(filter, bucket) == 0) {
            results = 0;

            // Print row
            printf(row, index, name, bucket, added_on, updated_on);
        }

        // Set temp to next node
        tmp = tmp->next;
    }

    // Print feedback if no results were found
    if (results != 0) {
        printf("\n\tNO RESULTS WERE FOUND\n\n");
    }
}

int unload_data() {

    // NULL check
    if (data == NULL) {
        return 5;
    }

    // Initialise temp and cursor heads
    node *tmp = data;
    node *cursor = data;

    while (cursor != NULL) {

        // Free memory of current node
        cursor = cursor->next;
        free(tmp);
        tmp = cursor;
    }

    return 0;
}

int save_to_file() {

    FILE *f = NULL;

    // Open file to save data
    f = fopen(PATHNAME, "w");
    if (f == NULL) {
        return 4;
    }

    // Initialise temp head
    node *tmp = data;

    while (tmp != NULL) {   

        // Write data to file
        entry buffer = tmp->game;
        fwrite(&buffer, sizeof(entry), 1, f);

        // Get next node
        tmp = tmp->next;
    }
    fclose(f);
    return 0;
}

int load_from_file() {

    FILE *f = NULL;

    // Open file to load data
    f = fopen(PATHNAME, "r");
    if (f == NULL) {
        return 4;
    }

    // Load data from file
    entry buffer;
    while (fread(&buffer, sizeof(entry), 1, f)) {
        insert_data(buffer);
    } 
    fclose(f);
    return 0;
}

int update_data(int i, char *status, char *date, char *name) {

    // Initialise temp head
    node *tmp = data;

    // Check if index is in first node
    if (tmp->index == i) {
        strcpy(tmp->game.bucket, status);
        strcpy(tmp->game.updated_on, date);
        strcpy(name, tmp->game.name);
        return 0;
    }

    // Traverse the list 
    while (tmp != NULL && tmp->index != i) {
        tmp = tmp->next;
    }

    // Check if index is in list
    if (tmp == NULL) {
        return 3;
    }

    // Update data of node
    strcpy(tmp->game.bucket, status);
    strcpy(tmp->game.updated_on, date);

    // Get name of game
    strcpy(name, tmp->game.name);
    return 0;
}
