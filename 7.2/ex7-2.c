/*
Exercise 7-2. Write a program that will print arbitrary input in a sensible way. As a
minimum, it should print non-graphic characters in octal or hexadecimal according to local
custom, and break long text lines. 
*/

#include <stdio.h>
#include <ctype.h>

int main()
{
    int count;
    int c;
    while ((c = getchar()) != EOF)
    {
        if (!isgraph(c))
        {
            // c automatically has a decimal value,
            // printf prints decimal as a hex. 
            printf("%02x", c);
        }
        else
        {
            putchar(c);
        }
        
        count++;

        if (count == 10)
        {
            printf("\n");
            count = 0;
        }
    }
}
