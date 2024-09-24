# include <stdio.h>

/*
Exercise 1-17: Write a program to print all input lines that are longer than 80 characters

// My implementation allows printing for all lengths, not limited to 1000
*/

# define THRES 83
# define EXIT_CHAR '~'

int my_getline(char[], int);

int main(void) {
    int len, nextLen;
    char first[THRES];
    char continuous[THRES];

    while ((len = my_getline(first, THRES)) > 0) {
        
        if (len == THRES-1) {
            printf("%s", first);
            
            /*
            collect string part after the first time
            then print it,
            collect again,
            if string part after initial has length less thatn THRES, don't loop again, since its not needed

            alternative implementation
            while (1) {
                nextLen = my_getline(continuous, THRES);
                printf("%s", continuous);
                if (nextLen != THRES-1) {
                    break;
                }
            }
            */
            nextLen = THRES-1;
            while (nextLen == THRES-1) {
                nextLen = my_getline(continuous, THRES);
                printf("%s", continuous);
            }
        }
        len = 0;
    }
}

int my_getline(char s[], int lim) {
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