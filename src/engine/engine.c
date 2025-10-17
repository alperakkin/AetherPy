#include <time.h>
#include <stdbool.h>
#include "scripting.h"
#include "engine.h"

#define DEFAULT_FPS 60
#define MAX_SCRIPTS 1024
#define MAX_ITERATIONS 10
Module *modules[MAX_SCRIPTS];
int MODULE_COUNT = 0;
double FPS = 0;
int iterations = 0;
bool running = true;

void run(char *PATH)
{

    FileList fl = scan_folder(PATH);
    load_modules(fl);
    start();
    setup();
    game_loop();
}

void load_modules(FileList fl)
{
    for (int i = 0; i < fl.count; ++i)
    {
        modules[i] = load_script(get_name(fl.files[i]), fl.files[i]);
        MODULE_COUNT++;
    }
}

void start()
{
    for (int i = 0; i < MODULE_COUNT; ++i)
    {
        call_game_function(modules[i], "start");
    }
}

void setup()
{
    for (int i = 0; i < MODULE_COUNT; ++i)
    {
        call_game_function(modules[i], "setup");
    }
}

void update()
{
    for (int i = 0; i < MODULE_COUNT; ++i)
    {
        call_game_function(modules[i], "update");
    }
}

void game_loop()
{
    struct timespec start_time, end_time;
    double delta_time;
    while (running)
    {

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        update();
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        delta_time = (end_time.tv_sec - start_time.tv_sec) +
                     (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
        if (delta_time <= 0)
            delta_time = 1e-9;
        FPS = 1.0 / delta_time;

        if (FPS < DEFAULT_FPS)
            printf("FPS Drop %.2f\n", FPS);
        iterations++;
        if (iterations >= MAX_ITERATIONS)
        {
            printf("DEBUG: Max Iterations reached - FPS: %.2f\n", FPS);
            running = false;
        }
    }
}