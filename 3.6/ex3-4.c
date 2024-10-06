#include <stdio.h>
#include <stdlib.h>

/*
Exercise 3-4. In a two's complement number representation, our version of itoa does not
handle the largest negative number, that is, the value of n equal to -(2**(wordsize)-1). Explain why
not. Modify it to print that value correctly, regardless of the machine on which it runs.
*/

#define MAX_LINE 1000


void reverse(char s[])
{
    int i, j;
    char temp;

    // Find the length of the string
    for (i = 0; s[i] != '\0'; i++)
        ;
    i--; // Move i back to the last character before '\0'

    // Reverse the string
    for (j = 0; j < i; j++, i--)
    {
        temp = s[j];
        s[j] = s[i];
        s[i] = temp;
    }
}


/* itoa: convert n to characters in s */
void itoa(int n, char s[])
{
        int i, sign;
        if ((sign = n) < 0) /* record sign */
                n = -n;     /* make n positive */
        i = 0;
        do
        {                              /* generate digits in reverse order */
                s[i++] = n % 10 + '0'; /* get next digit */
        } while ((n /= 10) > 0); /* delete it */

        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';

        reverse(s);
}

int main(void)
{
        char arr[MAX_LINE];

        itoa(0b1000, arr);

        printf("%s", arr);
}