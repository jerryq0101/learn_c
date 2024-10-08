#include <stdio.h>

/*
Exercise 2-9. In a two's complement number system, x &= (x-1) deletes the rightmost 1-bit
in x. Explain why. Use this observation to write a faster version of bitcount.

This is because the operation subtracts x from 0b1,
and then AND's the result with the original.
* even if there wasn't a 1 in the 2^0 position, subtracting 1 in the rightest 1 
forces it to become 0 in x - 1, and makes 1s distribute to positions further to the right, which,
after anding, the rightest 1 becomes a 0 after one iteration.
* if there was a 1 in the 2^0 position, it deletes it and ands it with the original, removing a digit

*/


int bitcount(unsigned x) {
        int i = 0;

        while (x) // x's right most digit still has a 1
        {
                x &= x-1;
                i++;
        }

        return i;
}

int main(void){
        printf("%d", bitcount(0b1011));
}
