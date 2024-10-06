#include <stdio.h>

int bitcount(unsigned x);

int main(void)
{
        unsigned x = 0b1101;
        printf("%d", bitcount(x));

}

/* bitcount: count 1 bits in x */
int bitcount(unsigned x)
{
        int b;
        for (b = 0; x != 0; x >>= 1) // right shifts until there are no more digits on the rightest digit.
                if (x & 0b1) // tests if the right most is a non zero value.
                        b++;
        return b;
}