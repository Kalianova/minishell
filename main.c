#include <stdio.h>

int main(int argc, char **argv)
{
    int i;

    i = 0;
    printf("%i\n", argc);
    while (++i < argc)
    {
        printf("%s", argv[i]);
    }
    return (0);
}