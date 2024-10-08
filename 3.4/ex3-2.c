#include <stdio.h>

/*
Exercise 3-2. Write a function escape(s,t) that converts characters like newline and tab
into visible escape sequences like \n and \t as it copies the string t to s. Use a switch. Write
a function for the other direction as well, converting escape sequences into the real characters.

Part 1 only.
*/

void escape(char s[], char t[]) {
        int i = 0;
        int j = 0;
        for (i = 0; s[i] != '\0'; i++) {
                switch (s[i]) {
                        case '\t': 
                                t[j++] = '\\';
                                t[j++] = 't';
                                break;
                        case '\n':
                                t[j++] = '\\';
                                t[j++] = 'n';
                                break;
                        default:
                                t[j] = s[i];
                                j++;
                                break;
                }
        }
        t[j] = '\0';
}


// Counts the number of spaces needed to visualize escape sequences
int count_spaces(char s[]) {
        int i;
        int count;

        i = count = 0;

        for (i = 0; s[i] != '\0'; i++) {
                switch (s[i]) {
                        case '\n': case '\t':
                                count++;
                        default:
                                count++;
                                break;
                }
        }
        return count;
}


int main(void) {
        char arr[6] = {'e', '\t', 'c', '\n', '\t', '\0'};
        int allocation = count_spaces(arr);
        char arr2[allocation + 1];

        escape(arr, arr2);

        printf("%s\n", arr2);
}
