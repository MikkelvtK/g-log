#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "data.h"

// Initialise linked list
node *data = NULL;

const char *PATHNAME = "D:/Development/C/cProjects/cs50FinalProject/data/gamelog.txt";

bool insert_data(entry g) {

    // Allocate memory for new node
    node *new_entry = malloc(sizeof(node));
    if (new_entry == NULL) {
        printf("Failed to allocate memory\n");
        return false;
    }

    // Fill new node with data
    new_entry->game = g;
    new_entry->next = NULL;

    // NULL check
    if (data == NULL) {
        data = new_entry;
        data->index = 0;
        return true;
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
    return true;
}

bool remove_data(int i) {

    // NULL check
    if (data == NULL) {
        return false;
    }

    // Initialise temp and cursor heads
    node *tmp = data;
    node *cursor = data;

    // Remove node if head itself has index
    if (cursor->index == i) {
        data = cursor->next;
        free(cursor);
        return true;
    }

    // Search for node with index
    while (cursor != NULL && cursor->index != i) {
            tmp = cursor;
            cursor = cursor->next;
    }

    // Return if node with index is not in list
    if (cursor == NULL) {
        return false;
    }

    // Remove node with index
    tmp->next = cursor->next;
    free(cursor);
    return true;
}

void print_data(char *filter) {
    
    // Initialise temp head
    node *tmp = data;
    
    // format row
    char *row = "\t\xBA%7i \xB3%25s \xB3%25s \xB3%25s \xB3%25s \xBA\n";

    // Check if results are found
    bool results = false;

    while (tmp != NULL) {

        int index = tmp->index;
        char *name = tmp->game.name;
        char *bucket = tmp->game.bucket;
        char *added_on = tmp->game.added_on;
        char *updated_on = tmp->game.updated_on;

        // Check if node matches filter
        if (filter == NULL || strcmp(filter, bucket) == 0) {
            results = true;

            // Print row
            printf(row, index, name, bucket, added_on, updated_on);
        }

        // Set temp to next node
        tmp = tmp->next;
    }

    // Print feedback if no results were found
    if (!results) {
        printf("\n\tNO RESULTS WERE FOUND\n\n");
    }
}

void unload_data() {

    // NULL check
    if (data == NULL) {
        return;
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
}

bool save_to_file() {

    FILE *f = NULL;

    // Open file to save data
    f = fopen(PATHNAME, "w");
    if (f == NULL) {
        return false;
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
    return true;
}

bool load_from_file() {

    FILE *f = NULL;

    // Open file to load data
    f = fopen(PATHNAME, "r");
    if (f == NULL) {
        return false;
    }

    // Load data from file
    entry buffer;
    while (fread(&buffer, sizeof(entry), 1, f)) {
        insert_data(buffer);
    } 
    fclose(f);
    return true;
}

void get_name(int i, char *s) {
    
    node *tmp = data;

    if (tmp->index == i) {
        char *name = tmp->game.name;
        strcpy(s, tmp->game.name);
        return;
    }

    while (tmp != NULL && tmp->index != i) {
        tmp = tmp->next;
    }

    if (tmp == NULL) {
        return;
    }

    strcpy(s, tmp->game.name);
}
