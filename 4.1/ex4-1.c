#include <stdio.h>

/*
Exercise 4-1. Write the function strindex(s,t) which returns the position of the rightmost
occurrence of t in s, or -1 if there is none.
*/

int strindex(char s[], char t) {
        int i = 0;
        int k = -1;

        for (i = 0; s[i] != '\0'; i++) {
                if (s[i] == t)
                        k = i;
        }

        return k;
}

int main(void) {
        char arr[6] = {'d', 't', 'v', '\n', 'x', '\0'};
        char t = 'd';

        printf("%d \n", strindex(arr, t));
}


