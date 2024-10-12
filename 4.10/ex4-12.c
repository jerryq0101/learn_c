#include <stdio.h>

/*
Exercise 4-12. Adapt the ideas of printd to write a recursive version of itoa; that is, convert
an integer into a string by calling a recursive routine.
*/
#define MAX_LEN 100

void itoa_recur(int n, char s[]);

int main(void) {

        char s[MAX_LEN] = {'\0'};
        int n = 230;
        itoa_recur(-230, s);

        printf("%s \n", s);
}

/* itoa: recursive edition, 
n: integer being converted
s: char array holding the converted number

Should:
- handle negative values
- handle integers
*/
void itoa_recur(int n, char s[]) {

        if (n < 0) 
        {
                s[0] = '-';
                n = -n;
        }

        if (n / 10 > 0) 
        {
                itoa_recur(n / 10, s);
        }

        // Go to the latest non empty slot
        int i = 0;
        while (s[i] != '\0')
                i++;
        s[i] = n % 10 + '0';
}