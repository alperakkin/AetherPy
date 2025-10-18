#include "utils.h"

#define MAX_LINE 256

char *join_scripts_path(const char *path)
{
    const char *suffix = "scripts";
    size_t n = strlen(path);
    int need_sep = (n == 0 || path[n - 1] == '/' || path[n - 1] == '\\') ? 0 : 1;
    size_t len = n + need_sep + strlen(suffix) + 1;

    char *out = malloc(len);
    if (!out)
        return NULL;

    strcpy(out, path);
    if (need_sep)
        strcat(out, "/");
    strcat(out, suffix);
    return out;
}

void get_settings(const char *path, Settings *settings)
{

    char settings_path[MAX_PATH];
    snprintf(settings_path, MAX_PATH, "%s/settings.aether", path);
    FILE *file = fopen(settings_path, "r");
    if (!file)
    {
        perror("Failed to open settings.aether");
        return;
    }

    char line[MAX_LINE];

    while (fgets(line, sizeof(line), file))
    {
        char *key = strtok(line, "=");
        char *value = strtok(NULL, "\n");

        if (!key || !value)
            continue;

        if (strcmp(key, "SCREEN_WIDTH") == 0)
            settings->SCREEN_WIDTH = atoi(value);
        else if (strcmp(key, "SCREEN_HEIGHT") == 0)
            settings->SCREEN_HEIGHT = atoi(value);
        else if (strcmp(key, "BACKGROUND") == 0)
            sscanf(value, "%d,%d,%d,%d",
                   &settings->background.R,
                   &settings->background.G,
                   &settings->background.B,
                   &settings->background.A);
    }

    fclose(file);

    printf("Width=%d, Height=%d, BG=(%d,%d,%d,%d)\n",
           settings->SCREEN_WIDTH, settings->SCREEN_HEIGHT,
           settings->background.R,
           settings->background.G,
           settings->background.B,
           settings->background.A);
}
FileList scan_folder(char *folder)
{
    FileList fl;
    fl.files = malloc(MAX_FILES * sizeof(char *));
    fl.count = 0;

    struct dirent *entry;
    DIR *dp = opendir(folder);
    if (!dp)
    {
        perror("opendir");
        return fl;
    }

    while ((entry = readdir(dp)))
    {
        if (strstr(entry->d_name, ".py"))
        {
            if (fl.count < MAX_FILES)
            {
                fl.files[fl.count] = malloc(MAX_PATH);
                snprintf(fl.files[fl.count], MAX_PATH, "%s/%s", folder, entry->d_name);
                fl.count++;
            }
        }
    }
    closedir(dp);
    return fl;
}

char *get_name(char *path)
{
    static char name[128];
    const char *base = strrchr(path, '/');
    if (!base)
        base = path;
    else
        base++;
    strcpy(name, base);
    char *dot = strrchr(name, '.');
    if (dot)
        *dot = '\0';
    return name;
}