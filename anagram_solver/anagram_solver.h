//All words should be allocated on the heap.

errno_t anagram_solver_create(hash_table_t** hash_table_addr, char* input_file_name);

// Find anagrams of a word using the hash table.
void anagram_solver_solve(hash_table_t* hash_table, char* word);

// Determine if a word is supported.
bool_t anagram_solver_word_is_supported(char* word);
