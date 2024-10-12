#include <stdio.h>
#include <string.h>

/*
Exercise 4-13. Write a recursive version of the function reverse(s), which reverses the
string s in place.
*/

#define MAX_LEN 100

void swap_sections_recur(char s[], int left, int middle, int right);
void reverse_str_recur(char s[], int left, int right);

int main(void) {
        char s[MAX_LEN] = {'\0'};
        strcpy(s, "abcde");


        reverse_str_recur(s, 0, 4);
        printf("%s", s);
}

void swap_sections_recur(char s[], int left, int middle, int right) {
        char temp[right - left];

        int i = 0;
        int pos = middle + 1;
        while (pos <= right) {
                temp[i] = s[pos];
                pos++;
                i++;
        }
        
        pos = left;
        while (pos <= middle) {
                temp[i] = s[pos];
                pos++;
                i++;
        }
        
        i = 0;
        pos = left;
        while (pos <= right) {
                s[pos] = temp[i];
                i++;
                pos++;
        }
}

/* reverse_str: reverses a string in its place */
void reverse_str_recur(char s[], int left, int right) {


        if (right - left >= 2) {
                int middle = (right + left) / 2;

                reverse_str_recur(s, left, middle);
                reverse_str_recur(s, middle+1, right);

                // Swap the sections
                swap_sections_recur(s, left, middle, right);
        }
        else if (right - left < 2) // Swap the two indexes
        {
                int temp = s[right];
                s[right] = s[left];
                s[left] = temp;
        }
}

