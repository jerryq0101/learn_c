#include <stdio.h>

# define EXIT_CHAR '~'
# define MAX_LEN 10

int my_getline(char line[], int maxline);
void copy(char to[], char from[]);

/* print the longest input line */
int main()
{
    int len;               /* current line length */
    int max;               /* maximum length seen so far */
    char line[MAX_LEN];    /* current input line */
    char longest[MAX_LEN]; /* longest line saved here */

    int nextLen;
    char nextLongest[MAX_LEN];

    max = 0;
    while ((len = my_getline(line, MAX_LEN)) > 0) {
        if (len == MAX_LEN - 1) {
            line[MAX_LEN-1] = '\n';
            nextLen = len;

            while (nextLen == MAX_LEN - 1) {
                nextLen = my_getline(nextLongest, MAX_LEN);
                len += nextLen;
            }
        }

        // Only saves the first MAX_LEN characters onto longest
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
    }
    if (max > 0) /* there was a line */
        printf("%s\n", longest);
        printf("%s %d\n", "Length", max);
    return 0;
}

/* getline: read a line into s, return length */
// * prefixed with my_ since newer c libraries uses the same name
int my_getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EXIT_CHAR && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}

/* copy: copy 'from' into 'to'; assume to is big enough */
void copy(char to[], char from[])
{
    int i;
    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}