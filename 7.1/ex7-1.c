#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Non correct number of arguments\n");
        return 1;
    }

    int upper = argv[1][0] == 'u' ? 1 : 0;

    int c;
    while ((c = getchar()) != EOF)
    {
        if (upper)
        {
            if (c >= 'a' && c <= 'z')
            {
                c = c - 'a' + 'A';
            }
            putchar(c);

        }
        else
        {
            if (c >= 'A' && c <= 'Z')
            {
                c = c - 'A' + 'a';
            }
            putchar(c);
        }
    }
}