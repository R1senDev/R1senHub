#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAGIC "RHPkgData"

char* read_zts(FILE *stream) {
    char *data = malloc(1);
    size_t length = 0;
    int byte;
    while ((byte = fgetc(stream)) != EOF && byte != '\0') {
        data = realloc(data, length + 2);
        data[length++] = byte;
    }
    data[length] = '\0';
    return data;
}

char** read_zts_list(FILE *stream, int *count) {
    char **data = malloc(sizeof(char*));
    *count = 0;
    int byte;
    char *current = malloc(1);
    size_t length = 0;
    while ((byte = fgetc(stream)) != EOF) {
        if (byte == '\0') {
            if (length == 0) break;
            current[length] = '\0';
            data = realloc(data, (*count + 1) * sizeof(char*));
            data[(*count)++] = current;
            current = malloc(1);
            length = 0;
        } else {
            current = realloc(current, length + 2);
            current[length++] = byte;
        }
    }
    free(current);
    return data;
}

int main() {
    FILE *file = fopen("C:/R1senTools/package.bin", "rb");
    if (!file) {
        printf("Failed to open file\n");
        return 1;
    }

    char magic[9];
    fread(magic, 1, 8, file);
    magic[8] = '\0';
    if (strcmp(magic, MAGIC) != 0) {
        printf("Invalid R1senHub installation :(\n");
        fclose(file);
        return 1;
    }

    int version[3];
    for (int i = 0; i < 3; i++) {
        version[i] = fgetc(file);
    }
    printf("\nR1senHub v%d.%d.%d\n", version[0], version[1], version[2]);

    int count;
    char **packages = read_zts_list(file, &count);
    printf("\nTools available in your installation:\n");
    for (int i = 0; i < count; i++) {
        if (strcmp(packages[i], "risenhub") == 0) {
            printf("\t- %s (this script!)\n", packages[i]);
        } else {
            printf("\t- %s\n", packages[i]);
        }
        free(packages[i]);
    }
    free(packages);

    fclose(file);
    return 0;
}