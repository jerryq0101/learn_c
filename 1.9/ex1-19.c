# include <stdio.h>

// Exercise 1-9: Write a function reverse that reverses the character string s. 
// Use it to write a program that reverses its input a line at a time.
#define EXIT_CHAR '~'
#define MAX_LEN 1000

int get_line(char s[], int lim);

int main(void) {
    int len, i, a;
    char arr[MAX_LEN];

    while ((len = get_line(arr, MAX_LEN)) > 0) {

        // Loop until the index of i is not some blank character
        for (i = len - 2; i >= 0 && (arr[i] == ' ' || arr[i] == '\t'); --i)
            ;

        // print the characters from there to the start
        for (a = i; a >= 0; a--) {
            printf("%c", arr[a]);
        }
        printf("\n");
    }
}

int get_line(char s[], int lim) {
    int i;
    int c;

    // Get characters until the last two
    for (i = 0; i <= lim - 2 && (c = getchar()) != EXIT_CHAR && c != '\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n'){

        s[i] = c;
        i++;
    }
    s[i] = '\0';

    return i;
}