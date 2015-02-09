// Linked list for words.

// TODO: 
// Consider placing the length of the word in the node as well.


struct linked_list_node_s
{
    char* word;
    struct linked_list_node_s* next;
};

typedef struct linked_list_node_s linked_list_node_t;

// Creates a linked list node.
// The node's word is set to the argument of the function.
linked_list_node_t* create_linked_list_node(char* word);

// Appends a word to a linked list. 
// The node parameter specifies a member of the linked list that will have a word appended to it.
// A new linked list node is created in this function.
// Returns a pointer to the tail of the linked list.
linked_list_node_t* append_to_linked_list(char* word, linked_list_node_t* node);

// Frees a linked list and any malloc'd contents inside the node.
void free_linked_list(linked_list_node_t* head);