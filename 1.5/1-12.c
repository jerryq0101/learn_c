/*
Exercise 1-12: Write a program that prints its input one word per line
*/

# include <stdio.h>

int main(void) {
    int c;
    int printed;

    while ((c = getchar()) != EOF) {
        // Enters a word
        while (c != ' ' && c != '\t' && c != '\n') {
            // Print a character
            putchar(c);
            printed = 1;
            // Get next character, until its not in the word
            c = getchar();
        }
        if (printed == 1) {
            printf("\n");
            printed = 0;
        }
    }
}