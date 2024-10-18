#include "dir_utils.h"
#include <dirent.h> // @ID This is a Linux only lib

char *getCurrentDir()
{
    char cwd[PATH_MAX];
    return getcwd(cwd, PATH_MAX);
}

char **getAllFilesInTheDir(char *directory, int numberOfFiles)
{
    // printf("dir: %s\n", directory);
    char **returnArray = malloc(numberOfFiles * sizeof(char *));
    int auxiliar = 0;
    // https://www.youtube.com/watch?v=j9yL30R6npk
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        perror("Error loading Dir");
        return "Error Loading Dir";
    }

    for (int i = 0; i < numberOfFiles; i++)
    {
        returnArray[i] = malloc(PATH_MAX * sizeof(char));
        if (returnArray[i] == NULL)
        {
            perror("Failed to allocate memory for file name");
            return NULL;
        }
    }

    struct dirent *entity;
    entity = readdir(dir);

    while (entity != NULL)
    {
        char *auxiliarDirectory = malloc(PATH_MAX * sizeof(char));
        strncpy(auxiliarDirectory, directory, PATH_MAX);
        // printf("full name: %s\n", strcat(strcat(auxiliarDirectory, "/"), entity->d_name));
        if (strcmp(entity->d_name, ".") == 0)
        {
            entity = readdir(dir);
            continue;
        }
        else if (strcmp(entity->d_name, "..") == 0)
        {
            entity = readdir(dir);
            continue;
        }
        else if (entity->d_name[0] == '.')
        {
            entity = readdir(dir);
            continue;
        }
        else
        {
            // printf("%s\n", entity->d_name);
            switch (entity->d_type)
            {

            case DT_DIR:
                // https://stackoverflow.com/questions/1121383/counting-the-number-of-files-in-a-directory-using-c
                // printf("%s\n", strcat(strcat(auxiliarDirectory, "/"), entity->d_name));
                char **childDir = getAllFilesInTheDir(strcat(strcat(auxiliarDirectory, "/"), entity->d_name), 10);

                break;

            case DT_REG:
                if (entity == NULL)
                {
                    break;
                }
                strncpy(returnArray[auxiliar], strcat(strcat(auxiliarDirectory, "/"), entity->d_name), PATH_MAX);
                auxiliar = auxiliar + 1;
                break;
            }
        }
        if (auxiliar == numberOfFiles)
        {
            break;
        }
        entity = readdir(dir);
    }
    closedir(dir);
    for (auxiliar = 0; auxiliar < numberOfFiles; auxiliar++)
    {
        printf("%s\n", returnArray[auxiliar]);
    }

    return returnArray;
}