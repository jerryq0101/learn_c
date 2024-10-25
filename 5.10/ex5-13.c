#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Exercise 5-13. Write the program tail, which prints the last n lines of its input. By default, n
is set to 10, let us say, but it can be changed by an optional argument so that

tail -n

prints the last n lines. The program should behave rationally no matter how unreasonable the
input or the value of n.

Write the program so it makes the best use of available storage; lines
should be stored as in the sorting program of Section 5.6, not in a two-dimensional array of
fixed size.

*/

#define MAXLINE 100

int n = 10;

int readlines(char *lineptr[], int maxlines);

int main(int argc, char *argv[])
{
        // Collect the initial parameters
        if (argc > 1) // if there is an optional n
        {
                int num = atoi((argv[1] + 1));
                n = num;
        }

        // collect lines
        char *lineptr[MAXLINE] = {0};
        int count = readlines(lineptr, MAXLINE);

        // printf("%s\n", lineptr[0]);
        // printf("%d\n", count);
        // printf("%d\n", n);

        // start at the count - nth line
        if (n > count) {
                for (int i = 0; i < count; i++)
                {
                        printf("%s\n", lineptr[i]);
                }
        }
        else // n is smaller than count
        {
                for (int i = count - n; i < count; i++) 
                {
                        printf("%s\n", lineptr[i]);
                }
        }
}

#define MAXLEN 100

int getline_v(char s[], int lim);
char *alloc(int len);

int readlines(char *lineptr[], int maxlines)
{
        int len, nlines;
        char *p, line[MAXLEN];

        nlines = 0;
        while ((len = getline_v(line, MAXLEN)) > 0)
        {
                if (nlines >= maxlines || (p = alloc(len)) == NULL)
                {
                        return -1;
                }
                else // store and give to lineptr
                {
                        line[len-1] = '\0';
                        strcpy(p, line);
                        lineptr[nlines++] = p;
                }
        }
        return nlines;
}

/* getline: read a line into s, return length int getline(char s[],int lim)
 */
int getline_v(char s[], int lim)
{
        int c, i;
        for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i){
                s[i] = c;
        }
        if (c == '\n')
        {
                s[i] = c;
                i++;
        }

        // printf("%s", s);
        s[i] = '\0';
        return i;
}


// Storage buffer
#define MAXCHARS 1000

char BUFFER[MAXCHARS];

int next_free_spot = 0;

char* alloc(int len)
{
        if (next_free_spot + len < MAXCHARS)
        {
                char *temp = &BUFFER[next_free_spot];
                next_free_spot += len;
                return temp;
        }
        return NULL;
}