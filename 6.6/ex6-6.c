#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

/*
Exercise 6-6. Implement a simple version of the #define processor (i.e., no arguments)
suitable for use with C programs, based on the routines of this section. You may also find
getch and ungetch helpful.

Steps:
1. Scan words
2. if its a #define, then scan the 2 words after it and store in hashtab
3. if not a #define, then check if its in hashtab, if so, replace it with the value in hashtab
*/

struct nlist { /* table entry: */
        struct nlist *next; /* next entry in chain */
        char *name; /* defined name */
        char *defn; /* replacement text */
};

#define HASHSIZE 101
#define MAXWORD 100
static struct nlist *hashtab[HASHSIZE] = {NULL}; /* pointer table, initialized with null so no garbage values */


void undef(char* name, char* defn);
unsigned hash(char *s);
struct nlist *lookup(char *s);
struct nlist *install(char* name, char* defn);
void undef(char* name, char* defn);
int getword(char *word, int lim);

int main(void)
{
    int n;
    char word[MAXWORD];
    FILE *fp;
    freopen_s(&fp, "input.txt", "r", stdin);    // opening STDIN in windows compatible way vs ex6-2.c
    if (fp == NULL) 
    {
        printf("Error opening file\n");
        return 1;
    }

    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))   // it is a word
        {
            // Case 1: define keyword
            if (strcmp(word, "define") == 0)
            {
                printf("define");
                char name[MAXWORD];
                char defn[MAXWORD];
                getword(name, MAXWORD);
                printf(name);
                getword(defn, MAXWORD);
                printf(defn);
                install(name, defn);
            }
            // Case 2: check if a word is in hashtab
            else 
            {
                struct nlist* np = lookup(word);
                if (np != NULL)
                {
                    printf("%s", np->defn);
                }
                else
                {
                    printf("%s", word);
                }
            }
        }
    }
}


/* hash: form hash value for string s */
unsigned hash(char *s)
{
        unsigned hashval;
        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;
        return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
        struct nlist *np;
        for (np = hashtab[hash(s)]; np != NULL; np = np->next)
                if (strcmp(s, np->name) == 0) 
                        return np;      /* found */
        return NULL;                    /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char* name, char* defn)
{
        struct nlist *np;
        
        if ((np = lookup(name)) == NULL)        // name doesn't exist in hashtab yet
        {
                struct nlist *new_entry = (struct nlist *) malloc(sizeof (struct nlist));       // allocate memory for a new entry
                if (new_entry == NULL || (new_entry->name = strdup(name)) == NULL)              // set new name, and check if its null.
                {
                        return NULL;
                }
                np = new_entry;
                unsigned hashvalue = hash(name);         // get hash
                np->next = NULL;                        // set next to be null initially.
                hashtab[hashvalue] = np;        // put new value at array spot
        }
        else
        {
                free((void *) np->defn);        // cast the char ptr to void (I don't have to include this, any pointer just converts to void) and free it
        }

        // Set new replacement text for the definition for both cases
        if ((np->defn = strdup(defn)) == NULL)
        {
                return NULL;
        }

        return np;
}

/* undef: removes (name, defn) from the hashtable */
void undef(char* name, char* defn)
{
        struct nlist* np;
        struct nlist* prev = NULL;
        
        for (np = hashtab[hash(name)]; np != NULL; np = np->next)
        {
                if (strcmp(np->name, name) == 0)        // do something
                {
                        if (prev == NULL) // if this is the head
                        {
                                hashtab[hash(name)] = np->next;
                        }
                        else
                        {
                                prev->next = np->next;
                        }
                        free(np);
                }
        }
}


int getch(void);
void ungetch(int);


int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch())){
        putchar(c);
    }
    if (c != EOF)
        *w++ = c;
    if (!isalnum(c))
    {
        *w = '\0';
        putchar(c);
        return c;
    }
    for (; --lim > 0; w++)
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    *w = '\0';
    return word[0];
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
