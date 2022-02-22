
// Define max length for entry fields
#define LENGTH = 255;

// Represents a game entry in the backlog
typedef struct {
    char *game;
    char *status;
    char *added_on;
    char *updated_on;
} game_entry;

// Represents a node in a linked list
typedef struct node {
    game_entry entry;
    node *next;
} node;