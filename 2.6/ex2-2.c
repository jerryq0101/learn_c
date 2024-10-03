#include <stdio.h>

/*
Exercise 2-2. Write a loop equivalent to the for loop above without using && or ||.
*/

int main(void) {
        int i;
        int c;
        int s[1000];
        int lim = 1000;

        // The first for loop
        for (i=0; i < lim-1 && (c=getchar()) != '\n' && c != EOF; ++i)
                s[i] = c;
        
        for (i=0; i < lim-1; ++i) {
                if ((c=getchar()) != '\n'){
                        if (c != EOF) {
                                s[i] = c;
                        }
                }
        }

}