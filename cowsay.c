#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]) {
    const char *art = 
        "        \\   ^__^\n"
        "         \\  (oo)\\_______\n"
        "            (__)\\       )\\/\n"
        "                ||----w |\n"
        "                ||     ||\n";

    char line[256] = "Hello, World!";
    if (argc > 1) {
        strcpy(line, argv[1]);
        for (int i = 2; i < argc; i++) {
            strcat(line, " ");
            strcat(line, argv[i]);
        }
    }

    int len = strlen(line);
    printf("\n");
    printf("  ");
    for (int i = 0; i < len; i++) printf("-");
    printf(" \n");
    printf("< %s >\n", line);
    printf("  ");
    for (int i = 0; i < len; i++) printf("-");
    printf(" \n");
    printf("%s", art);

    return 0;
}