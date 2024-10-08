/*
Based on 4-3

Exercise 4-4. Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.
*/


#include <stdio.h>
#include <stdlib.h> /* for atof() */
#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

int getop(char[]);
void push(double);
double pop(void);

/* reverse Polish calculator */
int main(void)
{
        int type;
        double op2;
        double a;
        char s[MAXOP];
        while ((type = getop(s)) != EOF)
        {
                switch (type)
                {
                case NUMBER:
                        printf("%s \n", s);
                        printf("%f \n", atof(s));
                        push(atof(s));
                        break;
                case '+':
                        push(pop() + pop());
                        break;
                case '*':
                        push(pop() * pop());
                        break;
                case '-':
                        op2 = pop();
                        push(pop() - op2);
                        break;
                case '/':
                        op2 = pop();
                        if (op2 != 0.0)
                                push(pop() / op2);
                        else
                                printf("error: zero divisor\n");
                        break;

                case '%':
                        op2 = pop();
                        if (op2 != 0.0) {
                                push((int) pop() % (int) op2);}
                        else
                                printf("error: zero divisor");
                        break;
                case '\n':
                        printf("\t%.8g\n", pop());
                        break;
                default:
                        printf("error: unknown command %s\n", s);
                        break;
                }
        }
        return 0;
}

// ------------------------------ Stack Implementation

#define MAXVAL 100  /* maximum depth of val stack */
int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

/* push: push f onto value stack */
void push(double f)
{
        if (sp < MAXVAL)
                val[sp++] = f;
        else
                printf("error: stack full, can't push %g\n", f);
}
/* pop: pop and return top value from stack */
double pop(void)
{
        if (sp > 0)
                return val[--sp];
        else
        {
                printf("error: stack empty\n");
                return 0.0;
        }
}

void print_top_two(void) {
        for (int i = sp-1; i >= 0; i--) {
                printf("%d \n", val[i]);
        }
}

// Swap if there are >= 2 items in the stack 
void swap_top_two(void) {
        int temp;
        if (sp > 1) 
        {
                temp = val[sp-1];
                val[sp-1] = val[sp-2];
                val[sp-2] = temp;
        } 
}

// Assume dup has enough storage
void duplicate_stack(double dup[]) {
        for (int i = 0; i < sp; i++) {
                dup[i] = val[i];
        }
}

void clear_stack(void) {
        sp = 0;
}



// ------------------------------ Get Next Operator OR number implementation (Unclear about this mechanism)



#include <ctype.h>
int getch(void);
void ungetch(int);

/* getop: get next character or numeric operand */
int getop(char s[])
{
        int i, c;
        while ((s[0] = c = getch()) == ' ' || c == '\t')
                ;
        s[1] = '\0';
        if (!isdigit(c) && c != '.' && c != '-')
                return c; /* not a number */

        i = 0;
        // Catching the case where '-' is actually a subtraction operator
        // Check if the next character from the negative sign is a number, if not, return
        if (c == '-'){
                int digit = isdigit(c = getch());
                if (digit) {
                        s[1] = c;
                        i = 1;
                } else {
                        ungetch(c);
                        return '-';
                }
        }
        

        if (isdigit(c)) /* collect integer part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        
        // this thing did collect the decimal part
        
        if (c == '.') /* collect fraction part */
                while (isdigit(s[++i] = c = getch()))
                        ;
        s[i] = '\0';
        if (c != EOF)
                ungetch(c);
        return NUMBER;
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