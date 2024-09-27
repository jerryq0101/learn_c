# include <stdio.h>


/*
Exercise 1-21 redo to get a better understanding of alternate solutions.

Logic:

keep track of:
- current_line_index
- spaces_elapsed

while (there is a character) {
        current_line_index++;

        if character is a space {
                spaces_elapsed++;

                if current_line_index is at a tab stop and spaces elapsed is obviously bigger than 0 {
                        print a tab
                        spaces_elapsed = 0
                }
        }
        else {
                while (spaces_elapsed > 0) {
                        spaces_elapsed--;
                        print a space;
                }
                print(the current character)
        }
}

return 0;
*/

#define EXIT_CHAR '~'
#define n 8

int main(void) {
        int c;
        int current_line_index;
        int spaces_elapsed;

        current_line_index = spaces_elapsed = 0;

        while ((c = getchar()) != EXIT_CHAR) {
                ++current_line_index;

                if (c == ' ') 
                {
                        ++spaces_elapsed;
                        
                        if (current_line_index % n == 0 && spaces_elapsed > 1) {
                                putchar('\t');
                                spaces_elapsed = 0;
                        }
                } 
                else 
                {
                        while (spaces_elapsed) {
                                putchar(' ');
                                --spaces_elapsed;
                        }
                        if (c == '\n') {
                                current_line_index = 0;
                        }
                        putchar(c);
                }
        }
        return 0;
}