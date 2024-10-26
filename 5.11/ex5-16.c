#include <stdio.h>
#include <string.h>
#include <ctype.h>

/*
Exercise 5-16. Add the -d (``directory order'') option, which makes comparisons only on
letters, numbers and blanks. Make sure it works in conjunction with -f.

Directory order means that when comparing characters we only care about the letters, numbers and blanks.
*/

#define MAXLINES 5000
char *lineptr[MAXLINES]; /* max #lines to be sorted */
/* pointers to text lines */

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);
void q_sort(void *v[], int left, int right,
           int (*comp)(void *, void *));
int numcmp(char *, char *);
int revstrcmp(char *s1, char *s2);
int revnumcmp(char *s1, char *s2);
int dirstrcmp(char *s1, char *s2);

/* sort input lines */
int main(int argc, char *argv[])
{
        int nlines;
        int numeric = 0; /* number of input lines read */
        int reverse = 0;
        int directory = 0;

        /* 1 if numeric sort */
        if (argc > 1){
                switch (argc) {
                        case(2):
                                if (strcmp(argv[1], "-n") == 0) {
                                        numeric = 1;
                                }
                                if (strcmp(argv[1], "-r") == 0) {
                                        reverse = 1;
                                }
                                if (strcmp(argv[1], "-d") == 0) {
                                        directory = 1;
                                }
                                break;
                        case(3):
                                if (strcmp(argv[1], "-r") == 0 && strcmp(argv[2], "-n") == 0) {
                                        numeric = 1;
                                        reverse = 1;
                                }
                                if (strcmp(argv[1], "-n") == 0 && strcmp(argv[2], "-r") == 0) {
                                        numeric = 1;
                                        reverse = 1;
                                }
                                break;
                }
        }
        
        if ((nlines = readlines(lineptr, MAXLINES)) >= 0)
        {
                q_sort((void **)lineptr, 0, nlines - 1,
                      (int (*)(void *, void *))((directory ? dirstrcmp : strcmp)));
                writelines(lineptr, nlines);
                return 0;
        }
        else
        {
                printf("input too big to sort\n");
                return 1;
        }
}
#define MAXSTRING 100
int dirstrcmp(char *s1, char *s2)
{
        char ns1[MAXSTRING];
        char ns2[MAXSTRING];

        int count = 0;
        while (*s1 != '\0')
        {
                if (isdigit(*s1) || islower(*s1) || isupper(*s1) || *s1 == ' ') {
                        ns1[count++] = *s1;
                }
                s1++;
        }
        count = 0;
        while (*s2 != '\0')
        {
                if (isdigit(*s2) || islower(*s2) || isupper(*s2) || *s2 == ' ') {
                        ns2[count++] = *s2;
                }
                s1++;
        }

        return strcmp(ns1, ns2);
}

int revstrcmp(char *s1, char *s2)
{
        return -strcmp(s1, s2);
}

int revnumcmp(char *s1, char *s2)
{
        return -numcmp(s1, s2);
}

/* qsort: sort v[left]...v[right] into increasing order */
void q_sort(void *v[], int left, int right,
           int (*comp)(void *, void *))
{
        int i, last;
        void swap(void *v[], int, int);
        if (left >= right) /* do nothing if array contains */
                return;    /* fewer than two elements */
        swap(v, left, (left + right) / 2);
        last = left;
        for (i = left + 1; i <= right; i++)
                if ((*comp)(v[i], v[left]) < 0)
                        swap(v, ++last, i);
        swap(v, left, last);
        q_sort(v, left, last - 1, comp);
        q_sort(v, last + 1, right, comp);
}

#include <stdlib.h>
/* numcmp: compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
        double v1, v2;
        v1 = atof(s1);
        v2 = atof(s2);
        if (v1 < v2)
                return -1;
        else if (v1 > v2)
                return 1;
        else
                return 0;
}

void swap(void *v[], int i, int j)
{
        void *temp;
        temp = v[i];
        v[i] = v[j];
        v[j] = temp;
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

void writelines(char *lineptr[], int maxlines) {
        for (int i = 0; i <maxlines; i++)
        {
                printf("%s\n", lineptr[i]);
        }
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