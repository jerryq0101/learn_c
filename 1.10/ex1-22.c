# include <stdio.h>

/*
Exercise 1-22: Folding long input lines into two or more 
shorter lines after the last non-blank character that occurs before the n-th column of input. Make sure your program
does something intelligent with very long lines, and if there are no blanks or tabs before the specified column.

*/
#define n 7
#define TAB_STOP 8

int get_spaces_till_next_tab_stop(int);

int main(void) {
        int c, i;
        int space_elapsed;
        int line_char_elapsed;
        int total_line_char_elapsed;

        space_elapsed = line_char_elapsed = total_line_char_elapsed = 0;

        while ((c = getchar()) != EOF) {
                line_char_elapsed++;
                total_line_char_elapsed++;

                if (c == ' ') 
                {
                        space_elapsed++;
                }
                else if (c == '\t')
                {       
                        // Technically, since \t is also a blank, I need to consider printing that for the space.
                        space_elapsed += get_spaces_till_next_tab_stop(total_line_char_elapsed) + 1;
                        
                        line_char_elapsed += get_spaces_till_next_tab_stop(total_line_char_elapsed);

                        total_line_char_elapsed += get_spaces_till_next_tab_stop(total_line_char_elapsed);

                        // printf("%s %d %d %d \n", "Tab, space_elapsed, line_char_elapsed, total_line_char_elapsed: ", space_elapsed, line_char_elapsed, total_line_char_elapsed);
                }
                else if (c == '\n') 
                {
                        space_elapsed = 0;
                        line_char_elapsed = 0;
                        total_line_char_elapsed = 0;
                }
                else    // Not a blank character, 
                        // line_char_elapsed <= n
                { 
                        while (space_elapsed > 0) {
                                space_elapsed--;
                                putchar(' ');
                        }
                        if (line_char_elapsed <= n){
                                putchar(c);
                        }
                }

                if (line_char_elapsed > n) {
                        // Either a single character input
                        // or due to the previous tab
                        
                        printf("\n");

                        if (c == ' ') // If its a single blank that caused the line increase
                        {
                                line_char_elapsed = 1;
                                space_elapsed = 0;
                                space_elapsed++;
                        } 
                        else if (c == '\t') // if its tab that caused the line increase
                        {
                                space_elapsed = line_char_elapsed-n;
                                line_char_elapsed = line_char_elapsed - n;
                                // printf("%s %d %d %d \n", "Tab that caused the line increase, space_elapsed, line char elapsed, total_line_char_elapsed", space_elapsed, line_char_elapsed, total_line_char_elapsed);
                        } 
                        else // If its a single non-blank character
                        {
                                line_char_elapsed = 1;
                                space_elapsed = 0;
                                putchar(c);
                        }
                }
        }
        return 0;
}

// Get the spaces until the next line char
int get_spaces_till_next_tab_stop(int line_char_elapsed) {
        return TAB_STOP * ((line_char_elapsed / TAB_STOP) + 1) - line_char_elapsed;
}