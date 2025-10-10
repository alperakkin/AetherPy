#include "utils.h"

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
    char *filename = strrchr(path, '/');
    if (filename)
        return filename + 1;
    return path;
}