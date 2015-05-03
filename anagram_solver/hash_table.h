#define default_hash_table_size 2

struct hash_node_s
{
    linked_list_node_t* head;
    linked_list_node_t* tail;
};

typedef struct hash_node_s hash_node_t;

struct hash_table_s
{
    unsigned int size;
    hash_node_t* table;
};

typedef struct hash_table_s hash_table_t;

// Create a hash table.
// Return a pointer to the hash table if successful. 
// Return NULL if unsuccessful. 
hash_table_t* hash_table_create();

// Insert a word into the hash table. 
// Return the pointer to the hash table if successful. 
// Return NULL if unsuccessful. 
hash_table_t* hash_table_insert_word(char* word, hash_table_t* hash_table);

// Hashe a word.
// Each letter from A to Z, regardless of case, is assigned a value starting from 1 and ending at 26 respectively.
// The hash value of a word is equivalent to the sum of the letters in the word. 
// Characters that are not letters in the latin alphabet are assigned to 0.
unsigned int hash_table_hash(char* word);

// Free all the nodes of a hash table. The contents inside the hash table are also freed.
void free_hash_table(hash_table_t* hash_table);