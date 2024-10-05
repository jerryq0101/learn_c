#include <stdio.h>
#include <string.h>

/*
Exercise 2-4. Write an alternative version of squeeze(s1,s2) that deletes each character in
s1 that matches any character in the string s2.
*/

void squeeze(char s1[], char s2[]);
int contains(char arr[], int a);

int main(void) {
        char arr1[6];
        char arr2[6]; 

        // Should remove the third character
        strcpy(arr1, "abcde");
        strcpy(arr2, "fgahi");

        squeeze(arr1, arr2);

        printf("%s", arr1);
        
}

void squeeze(char s1[], char s2[]) {
        int i, j;
        i = j = 0;

        while (s1[i] != '\0') {
                if (contains(s2, s1[i])) {
                        i++;
                }
                else // Doesn't contain
                {
                        s1[j++] = s1[i++];
                }
        }

        // Delete the rest of the remaining characters
        while (s1[j] != '\0') {
                s1[j++] = '\0';
        }
}

int contains(char arr[], int a) {
        int i = 0;
        while (arr[i] != '\0') {
                if (arr[i++] == a) {
                        return 1;
                }
        }
        return 0;
}