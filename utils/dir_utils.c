#include "dir_utils.h"
#include <unistd.h>
#include <linux/limits.h>
char *getCurrentDir()
{
    char cwd[PATH_MAX];
    return getcwd(cwd, PATH_MAX);
}
