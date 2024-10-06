#include <stdio.h>
#include <ctype.h>
#include <string.h>

/*
Exercise 3-3. Write a function expand(s1,s2) that expands shorthand notations like a-z in
the string s1 into the equivalent complete list abc...xyz in s2. Allow for letters of either
case and digits, and be prepared to handle cases like a-b-c and a-z0-9 and -a-z. Arrange
that a leading or trailing - is taken literally.
*/

#define MAX_LINE 1000

void expand(char s1[], char s2[]) {
        int i, j;

        i = j = 0;

        for (; s1[i] != '\0'; i++) {
                switch (s1[i]) {
                        case '-': 
                                // if left char exists and right char exists
                                if (i >= 1 && s1[i+1] != '\0') {
                                        int difference = s1[i+1] - s1[i-1];
                                        for (int k = 1; k < difference; k++, j++) {
                                                s2[j] = s1[i-1] + k;
                                        }
                                }
                                
                                
                                else if (i == 0 && s1[i+1] != '\0') // if no left, right exists
                                {
                                        // if the right digit is a digit
                                        if (isdigit(s1[i+1])) {
                                                for (int k = 0; k < s1[i+1] - '0'; k++, j++) {
                                                        s2[j] = k + '0';
                                                }
                                        }
                                        else if (islower(s1[i+1])) {
                                                for (int k = 0; k < s1[i+1] - 'a'; k++, j++) {
                                                        s2[j] = k + 'a';
                                                }
                                        }
                                        else if (isupper(s1[i+1])) {
                                                for (int k = 0; k < s1[i+1] - 'A'; k++, j++) {
                                                        s2[j] = k + 'A';
                                                }
                                        }
                                } 
                                // if left, no right
                                else if (i > 0 && s1[i+1] == '\0' && s1[i-1] != '\0') 
                                {
                                        // if the left character is a digit
                                        if (isdigit(s1[i-1])) {
                                                for (int k = 1; k <= ('9' - s1[i-1]); k++, j++) {
                                                        s2[j] = k + s1[i-1];
                                                }
                                        }
                                        else if (islower(s1[i-1])) {
                                                for (int k = 1; k <= ('z' - s1[i-1]); k++, j++) {
                                                        s2[j] = k + s1[i-1];
                                                }
                                        }
                                        else if (isupper(s1[i-1])) {
                                                for (int k = 1; k <= ('Z' - s1[i-1]); k++, j++) {
                                                        s2[j] = k + s1[i-1];
                                                }
                                        }
                                }


                                else {
                                        j++;
                                }
                                break;

                                

                                // Increment to the next available character space.
                                
                        default:
                                s2[j++] = s1[i];
                }
        }

        s2[j] = '\0';

}

int main(void) {
        char s1[6] = {'-', 'b', '-', 'd', '-', '\0'};
        char s1_1[7];
        char s2[MAX_LINE];


        strcpy(s1_1, "a-z0-9");

        expand(s1_1, s2);

        printf("%s \n", s2);
}