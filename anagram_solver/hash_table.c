#include "stdafx.h"

hash_table_t* hash_table_create()
{
    hash_table_t* hash_table = malloc(sizeof(hash_table_t));

    if (hash_table == NULL)
    {
        return NULL;
    }

    hash_table->size = default_hash_table_size;
    hash_table->table = calloc(hash_table->size, sizeof(hash_node_t));

    if (hash_table->table == NULL)
    {
        return NULL;
    }
    else
    {
        return hash_table;
    }
}

// TODO: 
// Increasing the hash table size can be optimized by:
// Set the size as the current hash and rounded up to the nearest power of 2.
hash_table_t* hash_table_insert_word(char* word, hash_table_t* hash_table)
{
    unsigned int hash;
    hash = hash_table_hash(word);

    //If the hash is out of bounds, continually double the hash table size until it is in bounds.
    while (hash >= hash_table->size)
    {
        unsigned int new_size = hash_table->size * 2;
        hash_table->table = realloc(hash_table->table, sizeof(hash_node_t) * new_size);

        //Set the newly allocated memory to zero.
        //The amount of memory to memset is equal to the previous size of the has node mulitplied by the size of the hashnode. 
        //The table is being doubled in size, so half of it needs to be set to zero.
        memset(hash_table->table + hash_table->size, 0, sizeof(hash_node_t) * hash_table->size);

        hash_table->size = new_size;
    }

    hash_node_t* curr = hash_table->table + hash;
    
    //Check to see if a linked list exists at the node yet. 
    //If it doesn't exist, create one. Otherwise, just append the word to the linked list.
    if (curr->head == NULL)
    {
        curr->head = create_linked_list_node(word);
        curr->tail = curr->head;
    }
    else
    {
        curr->tail = append_to_linked_list(word, curr->tail);
    }

    //Safety check since creating or appending a linked list can return NULL if it fails.
    if ((curr->head == NULL) || (curr->tail == NULL))
    {
        return NULL;
    }
    else
    {
        return hash_table;
    }
}

unsigned int hash_table_hash(char* word)
{
    unsigned int sum = 0;

    int i;
    for (i = 0; i < strlen(word); i++)
    {
        unsigned char c = word[i];
        
        //If c is a letter...
        if (((c >= 0x41) && (c <= 0x5A)) || ((c >= 0x61) && (c <= 0x7A)))
        {
            //Zero out the upper three bits of the byte. The value of the byte becomes normalized to 1. 
            c = c & 0x1F;

            sum += c;
        }
    }

    return sum;
}

void free_hash_table(hash_table_t* hash_table)
{
    int i;
    for (i = 0; i < hash_table->size; i++)
    {
        hash_node_t* curr = hash_table->table + i;
        
        if (curr->head != NULL)
        {
            free_linked_list(curr->head);
        }
    }

    free(hash_table->table);
    free(hash_table);
}