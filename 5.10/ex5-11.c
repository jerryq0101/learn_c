# include <stdio.h>

/*
Exercise 1-21: Write a program entab that replaces strings of blanks by the minimum number of tabs
and blanks to achieve the same spacing. Use the same tab stops as for detab.

When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
Use a space.
*/

/*
Logic:

for all characters:
- while it is a blank, count how many there is
- after counting it print a new calculated number of tabs and blanks instead
- or else just print normal characters
*/

int n = 8;
#define EXIT_CHAR '~'

void convert_spacing(int);
int calculate();

int sinceNewLine = 0;

int main(int argc, char *argv[]) {
        int c, i, blanks;

        if (argc > 1) // Set the spacing
        {
                n = (*++argv)[0] - '0';
        }

        while ((c = getchar()) != EOF) {
                
                if (c == ' ') 
                {
                        blanks = 1;
                        while ((c = getchar()) == ' ') {
                                blanks++;
                        }

                        // convert the total blanks to a space or more blanks
                        convert_spacing(blanks);
                        
                        // Catch the case where c eats up the last char and forgets to increment.
                        printf("%c", c);
                        sinceNewLine++;
                }

                // Handling new line logic and incrementing sinceNewLine. Should be ok.
                else if (c == '\n') 
                {
                        sinceNewLine = 0;
                        printf("\n");
                }
                else {
                        printf("%c", c);
                        sinceNewLine++;
                        // printf("%s %d\n", "SINCE NEW LINE IN else CLAUSE", sinceNewLine);
                }
        }
}


void convert_spacing(int blanks) {
        int spaces_till_tab_stop;

        spaces_till_tab_stop = calculate();

        // Check if tabs are (still) needed
        while (blanks - spaces_till_tab_stop > 0) {
                // print one tab
                printf("%c", '\t');

                // decrement number of blanks available by the spaces of the tab, increment the added length to current line index
                blanks -= spaces_till_tab_stop;
                sinceNewLine+=spaces_till_tab_stop;


                // Update spaces_until_tab_stop to propagate what the next tab will do
                spaces_till_tab_stop = calculate();
        }

        // Fill in with blanks
        while (blanks > 0) {
                printf("%c", ' ');
                blanks--;
                sinceNewLine++;
        }
}


// Amount of blanks to get to the next tab stop
int calculate() {
    int next, spaces;
    next = n*((sinceNewLine / n) + 1);
    spaces = next - sinceNewLine;
    return spaces;
}
