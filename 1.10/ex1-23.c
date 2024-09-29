# include <stdio.h>

/*
Exercise 1-23: Write a program to remove all comments from a C program. 
Don't forget to handle quoted strings and character constants properly. 
C comments do not nest.

What is a c comment?

1. Single line comment: remove everything from // to the end of the line
2. Multi-line comment: remove everything from / * to the next * /
3. But, // within single quotes, or double quotes are not comments.

*/

int main(void) {
        int c;
        char arr[2];
        int in_string;
        int in_double_comment; // Double slash comment
        int in_single_comment; // Single slash comment
        int in_double_string;
        int in_single_string;

        in_string = in_double_string = in_single_string = in_double_comment = in_single_comment = 0;
        arr[0] = arr[1] = ' ';
        
        int start_of_file = 0;
        int ignore_count = 0;

        while ((c = getchar()) != EOF) {
                if (start_of_file == 0) {
                        start_of_file = 1;
                        arr[0] = c;
                        continue;
                }
                arr[1] = c;

                // Check if gonna go into string
                if (!in_string && arr[1] == '"') {
                        in_string = 1;
                        in_double_string = 1;
                } else if (!in_string && arr[1] == '\'') {
                        in_string = 1;
                        in_single_string = 1;
                }


                if (!in_string)
                {      
                        // check if comment will start, when not already in a comment
                        if (arr[0] == '/' && arr[1] == '/' && !in_double_comment) {
                                ignore_count = 2;
                                in_double_comment = 1;
                        } else if (arr[0] == '/' && arr[1] == '*' && !in_single_comment) {
                                ignore_count = 2;
                                in_single_comment = 1;
                        }

                        // Check if comment will end, when in a comment
                        if (in_double_comment && arr[1] == '\n') {
                                ignore_count = 1;
                                in_double_comment = 0;
                        } else if (in_single_comment && arr[0] == '*' && arr[1] == '/') {
                                ignore_count = 2;
                                in_single_comment = 0;
                        }

                        // if not in comment
                        // and zeroth element is not used to
                        // start / end a comment, print the 0th char
                        if (ignore_count == 0 && !in_double_comment && !in_single_comment) {
                                putchar(arr[0]);
                        } else {
                                ignore_count--;
                        }
                }
                else // inside of a string
                // look for string endings
                {
                        putchar(arr[0]);
                        if (in_double_string && arr[1] == '"') {
                                in_string = 0;
                                in_double_string = 0;
                        } else if (in_single_string && arr[1] == '\'') {
                                in_string = 0;
                                in_single_string = 0;
                        }
                }
                // rotate array elements
                arr[0] = arr[1];
        }
        // Print the last character if not in a comment
        if (!in_double_comment && !in_single_comment && arr[0] != '\0') {
                putchar(arr[0]);
        }

}