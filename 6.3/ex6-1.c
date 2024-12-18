#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100

int getch(void);
void ungetch(int);

struct key
{
        char *word;
        int count;
} keytab[] = {
        // List is assumed to be sorted by binary search.
        "\"Enter\"", 0, // Capital letters are earlier in the ascii
        "#ifdef", 0,
        "*/", 0,        
        "/*", 0,
        "//", 0,
        "auto", 0,
        "break", 0,
        "case", 0,
        "char", 0,
        "const", 0,
        "continue", 0,
        "default", 0,
        "unsigned", 0,
        "user's", 0,
        "user_name", 0,
        "void", 0,
        "volatile", 0,
        "while", 0,
};

int getword(char *, int);
int binsearch(char *, struct key *, int);
#define NKEYS (sizeof keytab / sizeof(keytab[0]))


/* binsearch: find word in tab[0]...tab[n-1] */
int binsearch(char *word, struct key tab[], int n)
{

        int cond;
        int low, high, mid;
        low = 0;
        high = n - 1;
        while (low <= high)
        {
                mid = (low + high) / 2;
                if ((cond = strcmp(word, tab[mid].word)) < 0)
                        high = mid - 1;
                else if (cond > 0)
                        low = mid + 1;
                else
                        return mid;
        }
        return -1;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
        int c, getch(void);
        void ungetch(int);
        char *w = word; // passed in pointer to fill.
        while (isspace(c = getch()))
                ;
        if (c != EOF)
                *w++ = c;
        if (!isalpha(c) && c != '#' && c != '\"' && c != '/' && c != '*') // can't do all punct otherwise might absorb everything
        {
                *w = '\0';
                return c;
        }
        for (; --lim > 0; w++)
                if (!isalnum(*w = getch()) && *w != '_' && *w != '\"' && *w != '/' && *w != '\'' && *w != '*') 
                // only _  " / can appear at the end or in the middle of a possible word sequence
                // This is fine:
                // since if valid, _ will be for sure in the middle of a word sequence
                // " will also be for sure at the end, and we capture it to include "" (So capturing individual string constants is possible, but not multiple stuff)
                // / will always be in pairs, and be broken by a new space
                // /* and */ will also always be in pairs and be broken by a space after it
                // Relying on good formatting to parse through.
                {
                        ungetch(*w);
                        break;
                }
        *w = '\0';
        return word[0];
}

/* count C keywords */
int main(void)
{
        int n;
        char word[MAXWORD];

        FILE *fp = fopen("input.txt", "r");
        if (fp == NULL)
        {
                printf("Error opening file\n");
                return 1;
        }
        stdin = fp;
        while (getword(word, MAXWORD) != EOF)
                if (isalpha(word[0]) || ispunct(word[0]))
                        if ((n = binsearch(word, keytab, NKEYS)) >= 0)
                                keytab[n].count++;
        fclose(fp);

        for (n = 0; n < NKEYS; n++)
                if (keytab[n].count > 0)
                        printf("%4d %s\n",
                               keytab[n].count, keytab[n].word);
        return 0;

}


// ------------------------------ Buffer Read from Input Implementation


#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void)    /* get a (possibly pushed-back) character */
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}
