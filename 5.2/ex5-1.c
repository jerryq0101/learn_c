#include <stdio.h>
#include <ctype.h>

/*
Exercise 5-1. As written, getint treats a + or - not followed by a digit as a valid
representation of zero. Fix it to push such a character back on the input.
*/

#define SIZE 100
#define EXIT_CHAR '~'

void print_int_array(int arr[], int size);

int main(void) {
        int n, array[SIZE], getint(int *);
        for (n = 0; n < SIZE && getint(&array[n]) != EXIT_CHAR; n++)
                ;
        
        print_int_array(array, n);
}

void print_int_array(int arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", arr[i], (i < size - 1) ? ", " : "");
    }
    printf("]\n");
}


int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getint(int *pn)
{
        int c, sign;
        while (isspace(c = getch())) /* skip white space */
                ;
        if (!isdigit(c) && c != EXIT_CHAR && c != '+' && c != '-')
        {
                printf("not digit and not exit char \n");
                ungetch(c); /* it is not a number */
                return 0;
        }
        sign = (c == '-') ? -1 : 1;
        if (c == '+' || c == '-'){
                c = getch();
        }

        
        if (isspace(c)) {
                while (isspace(c = getch())) /* skip white space */
                        ;
        }
        if (isdigit(c)) {
                for (*pn = 0; isdigit(c); ) 
                {
                        *pn = 10 * *pn + (c - '0');
                        c = getch();
                }
                *pn *= sign;
        }
        
        if (c != EXIT_CHAR)
                ungetch(c);
        return c;
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
