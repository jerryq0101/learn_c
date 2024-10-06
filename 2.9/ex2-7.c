#include <stdio.h>

/*
Exercise 2-7. Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged.
*/


void printBinary(int num) {
    for (int i = 31; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
    }
    printf("\n");
}

unsigned invert(int x, int p, int n) {
        int x_mask = (~0 << (p - n)) & ~(~0 << p);
        int hollow_x = ~x_mask & x;
        printBinary(x);
        printBinary(x_mask);
        printBinary(hollow_x);

        int x_portion = (x & x_mask);
        printBinary(x_portion);

        return hollow_x | (~x_portion & x_mask);
}



int main(void) {
        int x = 0b10010100;
        printBinary(invert(x, 5, 3));
}

