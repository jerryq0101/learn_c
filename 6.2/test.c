#include <stdio.h>

struct thing1 {
        int a;
        char *b;
} p, *ptrp;

struct thing2 {
        struct thing1 a;
} q, *ptrq;

int main(void)
{
        ptrp = &p;
        ptrq = &q;
        q.a = p;

        p.a = 10;
        p.b = "abc";

        printf("thing before: %d \n", ptrp);

        char thing = *ptrp++->b;
        printf("char: %c \n", thing);
        printf("thing after: %d \n", ptrp);
}

