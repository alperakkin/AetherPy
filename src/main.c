#include <stdio.h>
#include "scripting.h"
#include "engine.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Please provide a Python script folder\n");
        return 1;
    }
    char *PATH = argv[1];

    initialize_scripting_engine();
    run(PATH);
    finalize_scripting_engine();

    return 0;
}
