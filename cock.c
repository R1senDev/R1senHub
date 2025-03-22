#include <stdio.h>
#include <stdlib.h>

const char *head = 
"   _____\n"
"  /  |  \\\n"
"  \\     /\n";

const char *base = "__/     \\__\n";

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("cock: Length is required\n");
        return 1;
    }

    int length;
    if (sscanf(argv[1], "%d", &length) != 1 || length < 0) {
        printf("cock: Invalid length value\n");
        return 1;
    }

    printf("%s", head);
    for (int i = 0; i < length; i++) {
        printf("   |   |\n");
    }
    printf("%s", base);

    return 0;
}