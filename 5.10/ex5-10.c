#include <stdio.h>
#include <ctype.h>

void push(int item);
int pop();

int main(int argc, char *argv[])
{
        int c;

        while (--argc > 0) {
                // gets the single character
                c = (*++argv)[0];
                // Digit
                if (isdigit(c))
                {
                        push((c - '0'));
                } 
                else if (c == '+' || c == '-' || c == '*' || c == '/')
                {
                        int a = pop(); // the second item
                        int b = pop(); // the first item
                        switch (c) {
                                case '+':
                                        printf("REACHED PLUS\n");
                                        push(b + a);
                                        break;
                                case '-':
                                        push(b-a);
                                        break;
                                case '*':
                                        printf("REACHED MULT\n");
                                        push(b*a);
                                        break;
                                case '/':
                                        push(b/a);
                                        break;
                        }
                }
        }
        printf("%d \n", pop());
}

// STACK Implementation
int BUFFER[100] = {0};
int next_free_pos = 0;

void push(int item) 
{
        BUFFER[next_free_pos++] = item;
}

int pop()
{
        return BUFFER[--next_free_pos];
}
