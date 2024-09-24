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

        // the c minus 2 index is to account for each line's \n and \0 characters
        for (i = c - 2; i >= 0 && (arr[i] == ' ' || arr[i] == '\t'); --i)
            ;
        arr[i + 1] = '\n'; 
        arr[i + 1] = '\0'; 

        printf("%s", arr);

        if (i > 0) {
            printf("\n");
            printf("%s %d \n", "index", i);
        }
    }

    return 0;
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