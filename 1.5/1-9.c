# include <stdio.h>

int main(void) {
    // Exercise 1-9: Write a program to copy its input to its output, replacing each string of one or more blanks by a single blank

    int c;
    while ((c = getchar()) != EOF) {
        // If blank => print blank
        if (c == ' ') {
            putchar(c);
            
            // If consecutive blanks => don't do anything
            while ((c = getchar()) == ' ')
                ;
        }
        putchar(c);
    }
}