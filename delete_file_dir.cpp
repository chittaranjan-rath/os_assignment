#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// POSIX dependencies
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>

void removefile(const char path[] ){
	//char *full_path; 
	if (unlink(path) == 0)
            printf("Removed a file: %s\n", path);
        else
            printf("Can`t remove a file: %s\n", path);
}
void removedir(const char path[])
{
    size_t path_len;
    char *actual_path;
    DIR *dir;
    struct stat stat_path, stat_entry;
    struct dirent *entry;

    // stat for the path
    stat(path, &stat_path);

    // if path does not exists or is not dir - exit with status -1
    if (S_ISDIR(stat_path.st_mode) == 0) {
        fprintf(stderr, "%s: %s\n", "Is not directory", path);
	 removefile(path);
        exit(-1);
    }

    // if not possible to read the directory for this user
    if ((dir = opendir(path)) == NULL) {
        fprintf(stderr, "%s: %s\n", "Can`t open directory", path);
        exit(-1);
    }

    // the length of the path
    path_len = strlen(path);

    // iteration through entries in the directory
    while ((entry = readdir(dir)) != NULL) {

        // skip entries "." and ".."
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, ".."))
            continue;

        // determinate a full path of an entry
        actual_path = (char *)calloc(path_len + strlen(entry->d_name) + 1, sizeof(char));
        strcpy(actual_path, path);
        strcat(actual_path, "/");
        strcat(actual_path, entry->d_name);

        // stat for the entry
        stat(actual_path, &stat_entry);
	//printf("ful path si %s \n",actual_path);
        // recursively remove a nested directory
        if (S_ISDIR(stat_entry.st_mode) != 0) {
            removedir(actual_path);
            continue;
        }

        // remove a file object
        if (unlink(actual_path) == 0)
            printf("Removed a file: %s\n", actual_path);
        else
            printf("Can`t remove a file: %s\n", actual_path);
    }

    // remove the devastated directory and close the object of it
    if (rmdir(path) == 0)
        printf("Removed a directory: %s\n", path);
    else
        printf("Can`t remove a directory: %s\n", path);

    closedir(dir);
}


int main(const int argc, char const *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Missing single operand: path\n");
        return -1;
    }

    removedir(argv[1]);

    return 0;
}
