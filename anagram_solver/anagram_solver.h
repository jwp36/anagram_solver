//All words should be allocated on the heap.

errno_t anagram_solver_create(hash_table_t** hash_table_addr, char* input_file_name);

void anagram_solver_solve(hash_table_t* hash_table, char* word);
