# include <stdio.h>

/*
logic:

while (get_line returns something > 0) {

    go from the behind and check whether a slot is taken up by a blank / or tab or other character
    increment a index range. 
    make [0: index] the new string

    check if the line is just one index now, and if it is just blank.
        do nothing
    else: print
}
*/

#define MAX_CHAR 1000
#define EXIT_CHAR '~'

int get_line(char s[], int lim);

int main(void) {
    int c, i, a;
    char arr[MAX_CHAR];

    while ((c = get_line(arr, MAX_CHAR)) > 0) {
        // Loop until the index of i is not some blank character
        for (i = c - 1; i >= 0 && (arr[i] == ' ' || arr[i] == '\t' || arr[i] == '\n'); --i)
            ;
        
        // Null-terminate the string after the last non-blank character
        arr[i + 1] = '\0'; 

        for (a = 0; a <= i; a++) {
            printf("%c", arr[a]);
        }

        if (i > 0) {
            printf("\n");
            printf("%s %d \n", "index", i);
        }
    }
}

int get_line(char s[], int lim) {
    int i;
    int c;

    // Get characters until the last two
    for (i = 0; i <= lim - 2 && (c = getchar()) != EXIT_CHAR && c != '\n'; ++i) {
        s[i] = c;
    }

    // if terminated by a nextline, then add it for separation with next lines.
    // if not terminated by nextline, but by the maximum boundary, then don't add 
    // since we need to print the line together
    if (c == '\n'){

        s[i] = c;
        i++;
    }
    s[i] = '\0';

    return i;
}