/*
Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.

Finding list of variables.

insert list into some tree (nodes with word lists), which should allow us to group stuff with same 6 letters.

find and print word lists.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXGROUP 10
#define ALPHABET 26

int getch(void);
void ungetch(int);
int isKeyword(char* str);

int getword(char *, int);

//////////////// BUILDING A PREFIX TREE TO FIND SIMILARLY NAMED WORDS //////////////////

// held_character: the character represented at this node
// children: the possible next characters
// strings: the strings that match this prefix
struct wnode {
        char held_character;
        struct wnode* children[ALPHABET];
        char* strings[10];
};

static struct wnode* tries[ALPHABET];

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
        
        // char *current_word;
        while (getword(word, MAXWORD) != EOF)
                // do stuff with the word.
                if (isalpha(word[0]))
                {
                        // Check if the word is a program keyword, then don't print it
                        if (!isKeyword(word) && strlen(word) >= 6)
                        {
                                printf("Variable name: %s", word);

                                // Situation: If they don't begin with the same initial char,
                                // They don't equal anyway.
                                
                                // see what is the initial character
                                        // make an initial node in the tries array with that character
                                
                                // while there are more characters in the word
                                        // use the same initial node to add a character.
                                        // put that node into an addnode function
                                        // save the latest node
                        }
                }
        fclose(fp);
}

// add node function
// if desired character node doesn't exist under this trie: just directly appends a value to the given node
// else: don't add a node, and just return the corresponding next character node
// BOTH CASES: should append the string to the node lists



/////////////// FINDING THE VARIABLE NAMES LONGER THAN 6 characters ////////////

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
        if (!isalpha(c)) // can't do all punct otherwise might absorb everything
        {
                *w = '\0';
                return c;
        }
        for (; --lim > 0; w++){
                *w = getch();
                if (*w == ';' || *w == ' ' || *w == '=') 
                {
                        ungetch(*w);
                        break;
                }
                else if (!isalnum(*w) && *w != '_') 
                // Other cases of not variable termination, so not variable
                // scan for next characters
                {
                        break;
                }
        }
        *w = '\0';
        return word[0];
}



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


// Function to check whether the given
// string is a keyword or not
// Returns 'true' if the string is a KEYWORD.
int isKeyword(char* str)
{
        if (!strcmp(str, "auto") || !strcmp(str, "default")
                || !strcmp(str, "signed") || !strcmp(str, "enum")
                || !strcmp(str, "extern") || !strcmp(str, "for")
                || !strcmp(str, "register") || !strcmp(str, "if")
                || !strcmp(str, "else") || !strcmp(str, "int")
                || !strcmp(str, "while") || !strcmp(str, "do")
                || !strcmp(str, "break") || !strcmp(str, "continue")
                || !strcmp(str, "double") || !strcmp(str, "float")
                || !strcmp(str, "return") || !strcmp(str, "char")
                || !strcmp(str, "case") || !strcmp(str, "const")
                || !strcmp(str, "sizeof") || !strcmp(str, "long")
                || !strcmp(str, "short") || !strcmp(str, "typedef")
                || !strcmp(str, "switch")
                || !strcmp(str, "unsigned") || !strcmp(str, "void")
                || !strcmp(str, "static") || !strcmp(str, "struct")
                || !strcmp(str, "goto") || !strcmp(str, "union")
                || !strcmp(str, "volatile")|| !strcmp(str, "stdio") 
                || !strcmp(str, "include") || !strcmp(str, "main"))
        {
                        return 1;
        }       
    return 0;
}