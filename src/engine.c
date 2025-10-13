#include <time.h>
#include <stdbool.h>
#include "scripting.h"
#include "engine.h"

#define DEFAULT_FPS 60
#define MAX_SCRIPTS 1024
#define MAX_ITERATIONS 10
Module *modules[MAX_SCRIPTS];

int FPS = 0;
int iterations = 0;
bool running = true;

void run(char *PATH)
{

    FileList fl = scan_folder(PATH);
    start(fl);
    setup(fl);
    game_loop(fl);
}

void start(FileList fl)
{
    for (int i = 0; i < fl.count; ++i)
    {
        modules[i] = load_script(get_name(fl.files[i]), fl.files[i]);
        call_game_function(modules[i], "start");
    }
}

void setup(FileList fl)
{
    for (int i = 0; i < fl.count; ++i)
    {
        call_game_function(modules[i], "setup");
    }
}

void update(FileList fl)
{
    for (int i = 0; i < fl.count; ++i)
    {
        call_game_function(modules[i], "update");
    }
}

void game_loop(FileList fl)
{
    struct timespec start_time, end_time;
    double delta_time;
    while (running)
    {

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        update(fl);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        delta_time = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        FPS = 1 / delta_time;

        if (FPS < DEFAULT_FPS)
            printf("FPS Drop %d\n", FPS);
        iterations++;
        if (iterations >= MAX_ITERATIONS)
        {
            printf("DEBUG: Max Iterations reached - FPS: %d\n", FPS);
            running = false;
        }
    }
}