#include <stdio.h>

/*
Exercise 2-10. Rewrite the function lower, which converts upper case letters to lower case,
with a conditional expression instead of if-else.
*/

void lower(char arr[]) {
        int i = 0;
        while (arr[i] != '\0') 
        {
                arr[i] = arr[i] >= 'A' && arr[i] <= 'Z' ? arr[i] + ('a' - 'A') : arr[i];
                i++;
        }
}

int main(void) {
        char s1[6] = {'A', 'B', 'C', 'B', 'E'};
        lower(s1);
        printf("%s", s1);
}