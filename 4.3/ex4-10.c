/*
Based on 4-6

Exercise 4-10. An alternate organization uses getline to read an entire input line; this makes
getch and ungetch unnecessary. Revise the calculator to use this approach.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <math.h>
#include <ctype.h>

#define MAXOP 100 /* max size of operand or operator */
#define MAXLEN 1000
#define NUMBER '0' /* signal that a number was found */
#define PREVIOUS '$'
#define EXIT_CHAR 'q'

double storage[27] = {0.0};
double previous; // Store previous value

int getop(char[]);
void push(double);
double pop(void);
int is_char(double d);
char convert_char(double d);
void push_char(int f);
void print_top_two(void);
int get_line(char line[], unsigned int max_line_len);

// Index on current line
// - Resets when we reach a new line
int current_line_index = 0;

// For debugging purposes, this represents a single line.
char line[MAXOP] = {'\0'};

/* reverse Polish calculator */
int main(void)
{
        int type = 0;
        double op2 = 0.0;
        double a = 0.0, b = 0.0;
        double var = 0.0;
        char s[MAXOP] = {0};

        while (get_line(line, MAXLEN))
        {
                while ((type = getop(s)) != '\0')
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
                                if (is_char(a))
                                {
                                        a = storage[convert_char(a) - 'a'];
                                }
                                if (is_char(b))
                                {
                                        b = storage[convert_char(b) - 'a'];
                                }
                                push(a + b);
                                break;
                        case '*':
                                a = pop();
                                b = pop();
                                if (is_char(a))
                                {
                                        a = storage[convert_char(a) - 'a'];
                                }
                                if (is_char(b))
                                {
                                        b = storage[convert_char(b) - 'a'];
                                }
                                push(a * b);
                                break;
                        case '-':
                                b = pop();
                                a = pop();
                                if (is_char(a))
                                {
                                        a = storage[convert_char(a) - 'a'];
                                }
                                if (is_char(b))
                                {
                                        b = storage[convert_char(b) - 'a'];
                                }
                                push(a - b);
                                break;
                        case '/':
                                b = pop();
                                a = pop();
                                if (is_char(a))
                                {
                                        a = storage[convert_char(a) - 'a'];
                                }
                                if (is_char(b))
                                {
                                        b = storage[convert_char(b) - 'a'];
                                }

                                if (b != 0.0)
                                {
                                        push(a / b);
                                }
                                else
                                        printf("error: zero divisor\n");
                                break;
                        case '%':
                                b = pop();
                                a = pop();
                                if (is_char(a))
                                {
                                        a = storage[convert_char(a) - 'a'];
                                }
                                if (is_char(b))
                                {
                                        b = storage[convert_char(b) - 'a'];
                                }
                                if ((int)b != 0)
                                {
                                        push((int)a % (int)b);
                                }
                                else
                                        printf("error: zero divisor \n");
                                break;
                        case '=':
                                op2 = pop();
                                var = pop();
                                var = convert_char(var);
                                storage[((int)var) - 'a'] = op2;
                                push(op2);
                                break;
                        case '\n':
                                previous = pop();
                                printf("\t%.8g\n", previous);

                                // Get new line operation
                                current_line_index = 0;
                                get_line(line, MAXLEN);

                                break;
                        default:
                                // Need to push characters into stack as well
                                if (type >= 'a' && type <= 'z')
                                {
                                        printf("%c\n", type);
                                        // Handle characters
                                        push_char(type);
                                }
                                else
                                {
                                        printf("error: unknown command %s\n", s);
                                }
                                break;
                        }
                }
        }
        return 0;
}

// ------------------------------ Stack Implementation

#define MAXVAL 100 /* maximum depth of val stack */
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

int is_char(double d)
{
        return d >= CHAR_OFFSET;
}

char convert_char(double d)
{
        return (int)(d - CHAR_OFFSET);
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

void print_top_two(void)
{
        for (int i = sp - 1; i >= 0; i--)
        {
                printf("%f \n", val[i]);
        }
}

// Swap if there are >= 2 items in the stack
void swap_top_two(void)
{
        int temp;
        if (sp > 1)
        {
                temp = val[sp - 1];
                val[sp - 1] = val[sp - 2];
                val[sp - 2] = temp;
        }
}

// Assume dup has enough storage
void duplicate_stack(double dup[])
{
        for (int i = 0; i < sp; i++)
        {
                dup[i] = val[i];
        }
}

void clear_stack(void)
{
        sp = 0;
}

// ------------------------------ Get Next Operator OR number implementation (Unclear about this mechanism)

#include <ctype.h>

/* getop: get next character or numeric operand */
// char s[] : the string that is filled with the relevant operator or number
int getop(char s[])
{
        int i, c;
        i = 0;

        // i : last index in string being filled
        // c : latest character in line being filled
        // current_line_index : current index in line being read, resets accordingly

        while ((s[0] = c = line[current_line_index++]) == ' ' || c == '\t')
                ;

        s[1] = '\0';

        if (!isdigit(c) && c != '.' && c != '-' && c != PREVIOUS)
                return c; /* not a number */

        i = 0;
        // Catching the case where '-' is actually a subtraction operator
        // Check if the next character from the negative sign is a number, if not, return
        if (c == '-')
        {
                int digit = isdigit(c = line[current_line_index++]);
                if (digit)
                {
                        s[1] = c;
                        i = 1;
                }
                else
                {
                        current_line_index--;
                        return '-';
                }
        }

        // Replacing $ with the actual previous value
        if (c == PREVIOUS)
        {
                // Load Previous into the char array s
                sprintf(s, "%.3f", previous);

                // Search for the last digit in s
                while (s[++i] != '\0')
                        ;

                // Set that last digit char to c
                c = s[i - 1];
        }

        if (isdigit(c)) /* collect integer part */
                while (isdigit(s[++i] = c = line[current_line_index++]))
                        ;

        // this thing did collect the decimal part

        if (c == '.') /* collect fraction part */
                while (isdigit(s[++i] = c = line[current_line_index++]))
                        ;

        // This prevents atof from looking for more characters, saving need to reset s everytime look for operator
        s[i] = '\0';
        if (c != EOF)
                current_line_index--;
        return NUMBER;
}

// ------------------------------ get_line

int get_line(char line[], unsigned int max_line_len)
{
        // // Dummy implementation for testing
        // line[0] = '$';
        // line[1] = ' ';
        // line[2] = '5';
        // line[3] = ' ';
        // line[4] = '-';
        // line[5] = ' ';
        // line[6] = '6';
        // line[7] = ' ';
        // line[8] = '+';
        // line[9] = '\n';
        // return 0;
        int c, i;

        for (i = 0; i < max_line_len - 1 && (c = getchar()) != EXIT_CHAR && c != '\n'; ++i)
        {
                line[i] = c;
        }

        if (c == '\n')
        {
                line[i] = c;
                ++i;
        }

        line[i] = '\0';

        return i;
}