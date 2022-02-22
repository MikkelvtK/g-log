#define LENGTH 255

// Represents a game entry in the backlog
typedef struct {
    char game[LENGTH];
    char status[LENGTH];
    char added_on[LENGTH];
    char updated_on[LENGTH];
} game_entry;

// Represents a node in a linked list
typedef struct node {
    int entry;
    struct node *next;
} node;