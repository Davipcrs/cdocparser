// @ID ## dir_utils.c @NL
// @ID This file contains the implementation for the directory utils @NL

#include "dir_utils.h"
#include <dirent.h> // @ID This is a Linux only lib @NL

char *getCurrentDir()
{
    char cwd[PATH_MAX];
    return getcwd(cwd, PATH_MAX);
}

char **getAllFilesInTheDir(char *directory)
{
    int fileCounter = 1;
    char **returnArray = malloc(1 * sizeof(char *));
    int auxiliar = 0;

    // https://www.youtube.com/watch?v=j9yL30R6npk
    DIR *dir = opendir(directory);
    if (dir == NULL)
    {
        perror("Error loading Dir");
        return NULL;
    }
    /*
    for (int i = 0; i < numberOfFiles; i++)
    {
        returnArray[i] = malloc(PATH_MAX * sizeof(char));
        if (returnArray[i] == NULL)
        {
            perror("Failed to allocate memory for file name");
            return NULL;
        }
    }
    */
    struct dirent *entity;
    entity = readdir(dir);

    while (entity != NULL)
    {
        char *auxiliarDirectory = malloc(PATH_MAX * sizeof(char));
        strncpy(auxiliarDirectory, directory, PATH_MAX);
        // printf("full name: %s\n", strcat(strcat(auxiliarDirectory, "/"), entity->d_name));
        if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0 || entity->d_name[0] == '.')
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
            {
                
                // https://stackoverflow.com/questions/1121383/counting-the-number-of-files-in-a-directory-using-c
                // printf("%s\n", strcat(strcat(auxiliarDirectory, "/"), entity->d_name));
                char **childDir = getAllFilesInTheDir(strcat(strcat(auxiliarDirectory, "/"), entity->d_name));

                int i = 0;
                while (childDir[i] != NULL) // Loop until you hit the NULL element
                {
                    fileCounter = fileCounter + 1;
                    allocStr(&returnArray, fileCounter);
                    returnArray[auxiliar] = malloc(PATH_MAX * sizeof(char));
                    if (returnArray[auxiliar] == NULL)
                    {
                        perror("Failed to allocate memory for file name");
                        return NULL;
                    }
                    strncpy(returnArray[auxiliar], childDir[i], PATH_MAX);
                    auxiliar = auxiliar + 1;
                    i = i + 1;
                }
                free(childDir);

                break;
            }
            case DT_REG:
            {
                if (entity == NULL)
                {
                    break;
                }
                fileCounter = fileCounter + 1;
                allocStr(&returnArray, fileCounter);
                returnArray[auxiliar] = malloc(PATH_MAX * sizeof(char));
                if (returnArray[auxiliar] == NULL)
                {
                    perror("Failed to allocate memory for file name");
                    return NULL;
                }
                strncpy(returnArray[auxiliar], strcat(strcat(auxiliarDirectory, "/"), entity->d_name), PATH_MAX);
                auxiliar = auxiliar + 1;
                break;
            }
            }
        }
        entity = readdir(dir);
    }
    closedir(dir);

    /*
    for (auxiliar = 0; auxiliar < fileCounter; auxiliar++)
    {
        printf("%s\n", returnArray[auxiliar]);
    }

    *numberOfFiles = fileCouter;
    */
    free(entity);
    returnArray[auxiliar] = NULL;
    return returnArray;
}

void allocStr(char ***array, int size)
{

    char **temp = realloc(*array, size * sizeof(char *));
    if (temp == NULL)
    {
        perror("Failed to realloc memory");
        return; // Return NULL on failure
    }
    *array = temp;
    return;
}

void printStrings(char **array)
{
    int i = 0;
    while (array[i] != NULL) // Loop until you hit the NULL element
    {
        printf("%s\n", array[i]); // Print each string
        i++;
    }
}