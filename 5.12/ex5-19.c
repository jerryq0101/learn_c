#include <stdio.h>

/*
Exercise 5-19. Modify undcl so that it does not add redundant parentheses to declarations.
*/

#include <string.h>
#include <ctype.h>
#define MAXTOKEN 100

enum
{
        NAME,
        PARENS,
        BRACKETS
};

void dcl(void);
void dirdcl(void);
int gettoken(void);
int is_next_basic_type(void);

int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

int error = 0;

int main() /* convert declaration to words */
{
        int type;
        char temp[MAXTOKEN];
        while (gettoken() != EOF)
        {
                strcpy(out, token); // beginning data type
                while ((type = gettoken()) != '\n')
                {
                        if (type == PARENS || type == BRACKETS){
                                strcat(out, token);
                        }
                        else if (type == '*')
                        {
                                // if the next character is a basic type, then don't need parentheses
                                if (is_next_basic_type())
                                {
                                        sprintf(temp, "*%s", out);        
                                }
                                else 
                                {
                                        sprintf(temp, "(*%s)", out);
                                }
                                strcpy(out, temp);
                        }
                        else if (type == NAME)
                        {
                                sprintf(temp, "%s %s", token, out);
                                strcpy(out, temp);
                        }
                        else
                        {
                                printf("invalid input at %s\n", token);
                        }
                }
                printf("%s \n", out);
        }
        return 0;
}

void push(char element);
char pop();

int is_next_basic_type(void) 
{
        int c, getch(void);
        void ungetch(int);
        
        int res = 0;
        int count = 0;

        while ((c = getch()) && !isalpha(c)){
                push(c);
                count++;
        }
        
        // guaranteed we are going to arrive at alphabet
        while (count > 0) 
        {
                char element = pop();
                if (element == '(' || element == ')' || element == '[' || element == ']')
                {
                        res = 0;
                }
                else 
                {
                        res = 1;
                }
                ungetch(element);
                count--;
        }
        
        return res;
}


// Implement a STACK
#define MAXSTACK 100
char STACK[MAXSTACK];

int next_free_spot = 0;

void push(char element)
{
        STACK[next_free_spot++];
}

char pop()
{
        return STACK[--next_free_spot];
}


// Functions
int gettoken(void) /* return next token */
{
        int c, getch(void);
        void ungetch(int);
        char *p = token;
        while ((c = getch()) == ' ' || c == '\t')
                ;
        if (c == '(')
        {
                if ((c = getch()) == ')')
                {
                        strcpy(token, "()");
                        return tokentype = PARENS;
                }
                else
                {
                        ungetch(c);
                        return tokentype = '(';
                }
        }
        else if (c == '[')
        {
                for (*p++ = c; (*p++ = getch()) != ']';)
                        ;
                *p = '\0';
                return tokentype = BRACKETS;
        }
        else if (isalpha(c))
        {
                for (*p++ = c; isalnum(c = getch());)
                        *p++ = c;
                *p = '\0';
                ungetch(c);
                return tokentype = NAME;
        }
        else
                return tokentype = c;
}



#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0; /* buffer for ungetch */
/* next free position in buf */
int getch(void) /* get a (possibly pushed-back) character */
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

// int error_handle(void)
// {
//         int c;
//         while ((c = gettoken()) != '\n')
//                 ;
//         error = 1;
//         return 0;
// }