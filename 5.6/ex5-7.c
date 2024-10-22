#include <stdio.h>
#include <string.h>

/*
Exercise 5-7. Rewrite readlines to store lines in an array supplied by main, rather than
calling alloc to maintain storage. How much faster is the program?
*/
#define MAXLEN 1000
#define maxline 5

int readlines(char *lineptr[], int maxlines, char BUFFER[]);

int main(void)
{
        char BUFFER[1000] = {'\0'};
        char *lineptr[5];

        readlines(lineptr, maxline, BUFFER);

        for (int i = 0; i < 5; i++) {
                printf("%s\n", lineptr[i]);
        }
}


int getline_ver(char s[], int lim);

/* readlines: read input lines */
int readlines(char *lineptr[], int maxlines, char *BUFFER)
{
        int len, nlines;
        char *p, line[MAXLEN];

        static int next_free_slot = 0;

        nlines = 0;

        while ((len = getline_ver(line, MAXLEN)) > 0)
        {
                p = (BUFFER+next_free_slot);
                if (nlines > maxlines - 1 || next_free_slot > MAXLEN - 1)
                        return -1;
                else
                {
                        line[len - 1] = '\0';
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                        next_free_slot += len;
                }
        }
        return nlines;
}

/* getline: get line into s, return length */
int getline_ver(char s[], int lim)
{
        int c, i;
        i = 0;
        while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
                s[i++] = c;
        if (c == '\n')
                s[i++] = c;
        s[i] = '\0';

        printf("%d\n", i);
        return i;
}