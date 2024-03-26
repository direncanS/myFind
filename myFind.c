#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/wait.h>

// Function to search for a file in a directory
// This function is called recursively if the -R option is provided
int search_file(const char *path, const char *filename, int recursive, int case_insensitive) {
    DIR *dir;
    struct dirent *entry;
    int found = 0;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return 0;
    }

    while ((entry = readdir(dir)) != NULL) {
        // Check for case-insensitive match if -i option is provided
        if (case_insensitive) {
            if (strcasecmp(entry->d_name, filename) == 0) {
                found = 1;
                break;
            }
        } else {
            if (strcmp(entry->d_name, filename) == 0) {
                found = 1;
                break;
            }
        }

        // If -R option is provided, search recursively in sub-directories
        if (recursive && entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char new_path[1024];
            snprintf(new_path, sizeof(new_path), "%s/%s", path, entry->d_name);
            found = search_file(new_path, filename, recursive, case_insensitive);
            if (found) {
                break;
            }
        }
    }

    closedir(dir);
    return found;
}

int main(int argc, char *argv[]) {
    int recursive = 0;
    int case_insensitive = 0;
    char *searchpath = NULL;
    int opt;

    // Parse command line options using getopt()
    while ((opt = getopt(argc, argv, "Ri")) != -1) {
        switch (opt) {
            case 'R':
                recursive = 1;
                break;
            case 'i':
                case_insensitive = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-R] [-i] searchpath filename1 [filename2] ... [filenameN]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    if (optind < argc) {
        searchpath = argv[optind++];
    } else {
        fprintf(stderr, "Searchpath is required\n");
        exit(EXIT_FAILURE);
    }

    // Fork child processes for each filename for parallel search
    for (int i = optind; i < argc; i++) {
        pid_t pid = fork();
        if (pid == 0) {  // Child process
            if (search_file(searchpath, argv[i], recursive, case_insensitive)) {
                printf("%d: %s: %s/%s\n", getpid(), argv[i], searchpath, argv[i]);
            }
            exit(EXIT_SUCCESS);
        } else if (pid < 0) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process waits for all child processes to terminate to prevent zombie processes
    while (wait(NULL) > 0);

    return 0;
}