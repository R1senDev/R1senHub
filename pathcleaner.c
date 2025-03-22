#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <shellapi.h>
#include <stdbool.h>

BOOL IsUserAdmin() {
    BOOL isAdmin = FALSE;
    PSID adminGroup = NULL;
    SID_IDENTIFIER_AUTHORITY ntAuthority = SECURITY_NT_AUTHORITY;

    if (AllocateAndInitializeSid(&ntAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID,
                                 DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &adminGroup)) {
        CheckTokenMembership(NULL, adminGroup, &isAdmin);
        FreeSid(adminGroup);
    }

    return isAdmin;
}

void remove_nonexistent_paths(char *path) {
    char *token;
    char *new_path = (char *)malloc(strlen(path) + 1);
    if (new_path == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_path[0] = '\0';

    token = strtok(path, ";");
    while (token != NULL) {
        if (GetFileAttributes(token) != INVALID_FILE_ATTRIBUTES) {
            strcat(new_path, token);
            strcat(new_path, ";");
        } else {
            printf("Found unused PATH entry: %s\n", token);
        }
        token = strtok(NULL, ";");
    }

    size_t len = strlen(new_path);
    if (len > 0 && new_path[len - 1] == ';') {
        new_path[len - 1] = '\0';
    }

    if (SetEnvironmentVariable("PATH", new_path) == 0) {
        fprintf(stderr, "Failed to set PATH environment variable\n");
        free(new_path);
        exit(EXIT_FAILURE);
    }

    free(new_path);
}

int main(int argc, char *argv[]) {

    bool force = false;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-f") == 0) {
            force = true;
            break;
        }
    }

    if (!force) {
        printf("r1senhub/pathcleaner is under development and is unstable now. To be more specific, it removes important paths, lol. If you're not afraid, launch with the \"-f\" flag.");
        return 1;
    }

    if (!IsUserAdmin()) {
        fprintf(stderr, "This script must be run as an administrator.\n");
        return EXIT_FAILURE;
    }

    char *path = getenv("PATH");
    if (path == NULL) {
        fprintf(stderr, "Failed to get PATH environment variable\n");
        return EXIT_FAILURE;
    }

    char *path_copy = (char *)malloc(strlen(path) + 1);
    if (path_copy == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }
    strcpy(path_copy, path);

    remove_nonexistent_paths(path_copy);

    printf("Success!\n");

    free(path_copy);
    return EXIT_SUCCESS;
}