#include <time.h>
#include <stdbool.h>
#include "scripting.h"
#include "engine.h"
#include "graphics.h"

#define DEFAULT_FPS 60
#define MAX_SCRIPTS 1024
#define MAX_ITERATIONS 100
Module *modules[MAX_SCRIPTS];
int MODULE_COUNT = 0;
double FPS = 0;
int iterations = 0;
bool running = true;

void run(char *PATH)
{
    Color color;
    color.R = 0;
    color.G = 0;
    color.B = 0;

    Settings settings;
    settings.SCREEN_WIDTH = DEFAULT_SCREEN_WIDTH;
    settings.SCREEN_HEIGHT = DEFAULT_SCREEN_HEIGHT;
    settings.background = color;
    get_settings(PATH, &settings);
    FileList fl = scan_folder(join_scripts_path(PATH));
    load_modules(fl);
    start();
    setup();
    Screen *screen = init_screen(settings);
    game_loop(screen);

    destroy_screen(screen);
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

double get_delta_time(struct timespec start_time, struct timespec end_time)
{
    double delta_time;
    delta_time = (end_time.tv_sec - start_time.tv_sec) +
                 (end_time.tv_nsec - start_time.tv_nsec) / 1e9;
    if (delta_time <= 0)
        delta_time = 1e-9;
    FPS = 1.0 / delta_time;

    if (FPS < DEFAULT_FPS)
        printf("FPS Drop %.2f\n", FPS);
    return delta_time;
}

void game_loop(Screen *screen)
{
    struct timespec start_time, end_time;
    double delta_time;
    while (running)
    {

        clock_gettime(CLOCK_MONOTONIC, &start_time);
        update();
        render(screen);
        clock_gettime(CLOCK_MONOTONIC, &end_time);
        delta_time = get_delta_time(start_time, end_time);

        iterations++;
        if (iterations >= MAX_ITERATIONS)
        {
            printf("DEBUG: Max Iterations reached - FPS: %.2f\n", FPS);
            running = false;
        }
    }
}