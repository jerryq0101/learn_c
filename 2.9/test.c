#include <stdio.h>

unsigned getbits(unsigned x, int p, int n);

int main(void) {
        printf("%u", getbits(101111, 2, 2));

}

/* getbits: get n bits from position p */
unsigned getbits(unsigned x, int p, int n)
{
return (x >> (p+1-n)) & ~(~0 << n);
}