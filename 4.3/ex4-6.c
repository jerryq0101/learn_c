/*
Based on 4-4

Exercise 4-6
*/


#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <ctype.h>

#define MAXOP 100   /* max size of operand or operator */
#define NUMBER '0'  /* signal that a number was found */

double storage[27] = {0.0};

int getop(char[]);
void push(double);
double pop(void);
int is_char(double d);
char convert_char(double d);
void push_char(int f);
void print_top_two(void);

/* reverse Polish calculator */
int main(void)
{
        int type;
        double op2;
        double a, b;
        double var;
        char s[MAXOP];
        while ((type = getop(s)) != EOF)
        {
                switch (type)
                {
                case NUMBER:
                        printf("%f \n", atof(s));
                        push(atof(s));
                        break;
                case '+':
                        a = pop();
                        b = pop();
                        if (is_char(a)) {
                                a = storage[convert_char(a) - 'a'];
                        }
                        if (is_char(b)) {
                                b = storage[convert_char(b) - 'a'];
                        }
                        push(a + b);
                        break;
                case '*':
                        a = pop();
                        b = pop();
                        if (is_char(a)) {
                                a = storage[convert_char(a) - 'a'];
                        }
                        if (is_char(b)) {
                                b = storage[convert_char(b) - 'a'];
                        }
                        push(a * b);
                        break;
                case '-':
                        b = pop();
                        a = pop();
                        if (is_char(a)) {
                                a = storage[convert_char(a) - 'a'];
                        }
                        if (is_char(b)) {
                                b = storage[convert_char(b) - 'a'];
                        }
                        push(a - b);
                        break;
                case '/':
                        b = pop();
                        a = pop();
                        if (is_char(a)) {
                                a = storage[convert_char(a) - 'a'];
                        }
                        if (is_char(b)) {
                                b = storage[convert_char(b) - 'a'];
                        }

                        if (b != 0.0){
                                push(a / b);
                        }
                        else
                                printf("error: zero divisor\n");
                        break;

                case '%':
                        b = pop();
                        a = pop();
                        if (is_char(a)) {
                                a = storage[convert_char(a) - 'a'];
                        }
                        if (is_char(b)) {
                                b = storage[convert_char(b) - 'a'];
                        }
                        if (b != 0.0) {
                                push((int) a % (int) b);
                        }
                        else
                                printf("error: zero divisor");
                        break;


                case '=': // Assume valid notations
                        printf("%s \n", "we reach the equals sign");
                        op2 = pop();
                        var = pop();
                        var = convert_char(var);
                        // Var is the variable, and op2 is the value
                        storage[((int) var) - 'a'] = op2;
                        push(op2);
                        break;
                case '\n':
                        printf("\t%.8g\n", pop());
                        break;
                default:
                        // Need to push characters into stack as well
                        if (type >= 'a' && type <= 'z') {
                                printf("%c\n", type);
                                // Handle characters
                                push_char(type);
                        } else {
                                printf("error: unknown command %s\n", s);
                        }
                        break;
                }
        }
        return 0;
}

// ------------------------------ Stack Implementation

#define MAXVAL 100  /* maximum depth of val stack */
#define CHAR_OFFSET 10000000

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

/* push onto stack with char flag */
void push_char(int f)
{
        if (sp < MAXVAL)
                val[sp++] = f + CHAR_OFFSET;
        else
                printf("error: stack full, can't push %d\n", f);
}

int is_char(double d) {
        return d >= CHAR_OFFSET;
}

char convert_char(double d) {
        return (int) (d - CHAR_OFFSET);
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
                printf("%f \n", val[i]);
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