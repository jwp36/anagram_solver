#include "stdafx.h"

linked_list_node_t* create_linked_list_node(char* word)
{
    linked_list_node_t* linked_list_node = calloc(1, sizeof(linked_list_node_t));

    if (linked_list_node == NULL)
    {
        return NULL;
    }
    else
    {
        linked_list_node->word = word;
        return linked_list_node;
    }
}

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