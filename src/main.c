#include <stdio.h>
#include "scripting.h"

int main(int argc, char *argv[])
{
    const char *PATH = "examples/player.py";
    const char *MODULE = "player";
    initialize_scripting_engine();
    Module *instance = load_script(MODULE, PATH);

    call_game_function(instance, "setup");
    call_game_function(instance, "update");
    finalize_scripting_engine();

    return 0;
}
