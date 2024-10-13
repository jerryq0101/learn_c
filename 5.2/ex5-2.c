#include <stdio.h>
#include <ctype.h>
#include <math.h>

/*
Exercise 5-1. 

Exercise 5-2. Write getfloat, the floating-point analog of getint. What type does
getfloat return as its function value?
*/

#define SIZE 100
#define EXIT_CHAR '~'

void print_double_array(double arr[], int size);

int main(void) {
        int n, getdouble(double *);
        double array[SIZE];
        for (n = 0; n < SIZE && getdouble(&array[n]) != EXIT_CHAR; n++)
                ;
        
        print_double_array(array, n);
}

void print_double_array(double arr[], int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%f%s", arr[i], (i < size - 1) ? ", " : "");
    }
    printf("]\n");
}


int getch(void);
void ungetch(int);

/* getint: get next integer from input into *pn */
int getdouble(double *pn)
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

                // Handle decimals
                int power = 0;
                if (c == '.') {
                        c = getchar();
                        if (isdigit(c)) {
                                for (;isdigit(c);) 
                                {
                                        *pn = 10 * *pn + (c - '0');
                                        c = getch();
                                        power++;
                                }
                        }
                        ungetch(c);
                        
                        *pn = *pn / pow(10, power);
                }
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
