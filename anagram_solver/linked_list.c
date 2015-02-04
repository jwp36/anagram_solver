
// Linked list for words.
// All words should be allocated on the heap.

#include "stdafx.h"

// Creates a linked list node.
// The node's word is initialized by the argument.
linked_list_node_t* create_linked_list_node(char* word)
{
    linked_list_node_t* linked_list_node = malloc(sizeof(linked_list_node_t));

    if (linked_list_node == NULL)
    {
        return NULL;
    }
    else
    {
        linked_list_node->word = word;
        linked_list_node->next = NULL;

        return linked_list_node;
    }
}

// Appends a word to a linked list. 
// The node parameter specifies a member of the linked list that will have a word appended to it.
// A new linked list node is created in this function.
// Returns a pointer to the tail of the linked list.
linked_list_node_t* append_to_linked_list(char* word, linked_list_node_t* node)
{
    linked_list_node_t* new_node = create_linked_list_node(word);

    if (new_node == NULL)
    {
        return NULL;
    }
    else
    {
        while (node->next != NULL)
        {
            node = node->next;
        }

        node->next = new_node;

        return new_node;
    }
}

// Frees a linked list.
// Each word in the linked list is also freed. 
void free_linked_list(linked_list_node_t* head)
{
    linked_list_node_t* prev;
    linked_list_node_t* curr = head;

    while (curr != NULL)
    {
        prev = curr;
        curr = curr->next;
        
        free(prev->word);
        free(prev);
    }
}