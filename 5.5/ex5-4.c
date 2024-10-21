#include <stdio.h>
#include <string.h>

/*
Exercise 5-4. Write the function strend(s,t), which returns 1 if the string t occurs at the
end of the string s, and zero otherwise.
*/

int strend(char *s, char *t);

int main(void) {
        char arr1[7];
        char arr2[4];

        strcpy(arr1, "abcdef");
        strcpy(arr2, "def");

        printf("%d", strend(arr1, arr2));
}

int strend(char *s, char *t)
{
        char *temp = t;

        // Increment to the last characters of s and t
        while (*s++)
                ;
        while (*t++)
                ;

        // Start incrementing backwards and comparing the two 
        while (*--s == *--t)
                ;
        
        return temp == ++t;
}