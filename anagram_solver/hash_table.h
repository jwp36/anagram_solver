
// TODO:
// Consider using a maximum hash table size here.
// When hashing, any hash values will simply be modding by the (maximum table size - 1) to ensure that it can be indexed.
//
// Research whether using a macro or a const is correct.
// Are these by convention always all uppercase?

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

// Creates a hash table.
// Returns the pointer to the hash table if successful. 
// Returns NULL if unsuccessful. 
hash_table_t* hash_table_create();

// Inserts a word into the hash table. 
// Returns the pointer to the hash table if successful. 
// Returns NULL if unsuccessful. 
hash_table_t* hash_table_insert_word(char* word, hash_table_t* hash_table);

// Hashes a word.
// Each letter from A to Z, regardless of case, is assigned a value starting from 1 and ending at 26.
// The hash value of a word is equivalent to the sum of the letters in the word. 
// Characters that are not letters in the latin alphabet are assigned to 0.
unsigned int hash_table_hash(char* word);