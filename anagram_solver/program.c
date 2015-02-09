#include "stdafx.h"

int _tmain(int argc, _TCHAR* argv[])
{
    // Allow memory-leak checks to occur at each exit point in the program.
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    char* input_file_name = "../data/words";

    hash_table_t* hash_table;
    errno_t error;

    error = anagram_solver_create(&hash_table, input_file_name);
    if (error != 0)
    {
        getchar();
    }

    anagram_solver_solve(hash_table, "aowi3ruasl3irlj");

    getchar();

    //prompt user for words and stuff
    return 0;
}
