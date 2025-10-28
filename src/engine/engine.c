#include "engine/engine.h"

#define DEFAULT_FPS 60
#define MAX_SCRIPTS 1024
#define MAX_ITERATIONS 10000
Module *modules[MAX_SCRIPTS];
int MODULE_COUNT = 0;
double FPS = 0;
int iterations = 0;
bool running = true;

void run(char *PATH)
{
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
        call_game_function(modules[i]->start_func);
    }
}

void setup()
{
    for (int i = 0; i < MODULE_COUNT; ++i)
    {
        call_game_function(modules[i]->setup_func);
    }
}

void update()
{

    for (int i = 0; i < MODULE_COUNT; ++i)
    {
        call_game_function(modules[i]->update_func);
    }
}

void game_loop(Screen *screen)
{

    while (running)
    {
        if (!game_state.paused)
            update();

        if (render(screen) == false)
        {
            running = false;
        };

        iterations++;
        if (iterations >= MAX_ITERATIONS)
        {
            FPS = GetFPS();
            printf("DEBUG: Max Iterations reached - FPS: %.2f\n", FPS);

            running = false;
        }
    }
}