# include <stdio.h>

int main(void) {
    // Exercise 1-8: Count blanks, tabs and newlines

    int blanks, tabs, newlines;
    int c;

    while ((c = getchar()) != EOF) {
        if (c == ' ') {
            ++blanks;
        } 
        else if (c == '\t') {
            ++tabs;
        } 
        else if (c == '\n') {
            ++newlines;
        }
    }
    printf("%s %d %s %d %s %d\n", "Blanks: ", blanks, "Tabs: ", tabs, "Newlines: ", newlines);
}