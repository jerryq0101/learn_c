# include <stdio.h>

/*
Exercise 1-20: Detab Program

Replaces tabs in the input with the proper number of blanks to space to the next tab stop.
Assume fixed set of tab stops, every n columns.

Should n be a variable or a symbolic parameter? Symbolic Param it is.

*/

/*

Logic: 

# define n 8


For each tab in the input:
- current position
- detemine how many spaces needed for the next tab stop
- insert that many spaces and replace the tab character

calculuate function:
- finds the number of spaces needed to the next tab stop

*/

#define n 8
#define EXIT_CHAR '~'

int calculate(int since_new_line);

int main(void) {
    int c, i, j, temp, since_new_line;

    since_new_line = temp = 0;

    for (i = 0; (c = getchar()) !=  EXIT_CHAR; ++i) {

        if (c == '\t')
        {
            // print spaces instead of the tab
            temp = calculate(since_new_line);
            for (j = temp; j > 0; --j) {
                printf("%c", ' ');
            }

            // increment since new line with new length
            since_new_line+=temp;
        }
        else if (c == '\n') 
        {
            printf("\n");
            since_new_line = 0;
        } 
        else 
        {
            printf("%c", c);
            since_new_line++;
        }
    }

    return 0;
}

int calculate(int since_new_line) {
    int next, spaces;

    next = n*((since_new_line / n) + 1);
    spaces = next - since_new_line;

    // printf("%s %d %s %d", "Tabs", spaces, "Since new line", since_new_line);
    return spaces;
}