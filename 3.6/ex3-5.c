#include <stdio.h>

#define MAX_LINE 1000
/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.

Frick the negative number systems.
*/

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


void itob(unsigned n, char s[], int base) {
        // Since n will get converted into decimal form by C,
        // we can just continue dividing until we get the stuff
        int i = 0;
        int remainder = 0;

        do {
                s[i++] = (n % base) + '0';
        }
        while ((n /= base) != 0);
        
        s[i] = '\0';

        reverse(s);
}


int main(void) {
        char arr[MAX_LINE];

        itob(0b10100, arr, 8);

        printf("%s \n", arr);
}

