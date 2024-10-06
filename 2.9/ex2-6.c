#include <stdio.h>

/*
Exercise 2-6. Write a function setbits(x,p,n,y) that returns x with the n bits that begin at
position p set to the rightmost n bits of y, leaving the other bits unchanged.
*/
void printBinary(int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

unsigned setbits(unsigned x, int p, int n, unsigned y) {
    unsigned y_shifted = y << (p - n);
    printf("Y Shifted\n");
    printBinary(y_shifted);
    unsigned y_mask = ~(~0 << n) << (p - n);
    printf("Y Mask\n");
    printBinary(y_mask);
    unsigned x_mask = ~y_mask;
    return (y_shifted & y_mask) | (x & x_mask);
}


int main(void) {
        // Since binary is 32 bits on my machine
        unsigned x = 0b1010000000;
        unsigned y = 0b1111011;

        printBinary(setbits(x, 9, 4, y));
}


