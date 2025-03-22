#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    const char art[] =
        "\n       |\\      _,,,---,,_\n"
        "ZZZzz /,`.-'`'    -.  ;-;;,_\n"
        "     |,4-  ) )-,_. ,\\ (  `'-'\n"
        "    '---''(_/--'  `-'\\_)\n\n";
    const char *choices[] = {
        "meow! you're such a kitten.",
        "purr... someone's calling me?",
        "nyaa~ need some fish first.",
        "hiss! just kidding, meow~",
        "purr... do you have catnip?",
    };

    size_t size = sizeof(choices) / sizeof(choices[0]);
    srand(time(NULL));
    int i = rand() % size;
    printf(art);
    printf("   %s", choices[i]);
    printf("\n\n");

    return 0;
}