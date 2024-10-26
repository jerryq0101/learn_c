#include <stdio.h>

/*
Exercise 5-18. Make dcl recover from input errors.
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
int error_handle(void);

int tokentype;           /* type of last token */
char token[MAXTOKEN];    /* last token string */
char name[MAXTOKEN];     /* identifier name */
char datatype[MAXTOKEN]; /* data type = char, int, etc. */
char out[1000];

int error = 0;

int main() /* convert declaration to words */
{
        while (gettoken() != EOF)
        {
                strcpy(datatype, token); /* 1st token on line */
                /* is the datatype */
                out[0] = '\0';
                dcl(); /* parse rest of line */
                if (tokentype != '\n')
                        printf("syntax error\n");
                if (!error) {
                        printf("%s: %s %s\n", name, out, datatype);
                } else {
                        printf("Invalid Input, try again\n");
                        error = 0;
                }
        }
        return 0;
}

// Functions

/* dirdcl: void dirdcl(void)
parse a direct declarator */
void dirdcl(void)
{
        int type;
        if (tokentype == '(')
        { /* ( dcl ) */
                dcl();
                if (tokentype != ')'){
                        printf("error: missing )\n");
                        error_handle();
                        return;
                }
        }
        else if (tokentype == NAME) 
        {/* variable name */
                strcpy(name, token);
        }
        else
        {
                printf("error: expected name or (dcl)\n");
                error_handle();
                return;
        }
        while ((type = gettoken()) == PARENS || type == BRACKETS)
        {
                if (type == PARENS)
                        strcat(out, " function returning");
                else
                {
                        strcat(out, " array");
                        strcat(out, token);
                        strcat(out, " of");
                }
        }
}


/* dcl: void dcl(void)
parse a declarator */
void dcl(void)
{
        int ns;
        for (ns = 0; gettoken() == '*';) /* count *'s */
                ns++;
        dirdcl();
        while (ns-- > 0)
                strcat(out, " pointer to");
}

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

int error_handle(void)
{
        int c;
        while ((c = gettoken()) != '\n')
                ;
        error = 1;
        return 0;
}