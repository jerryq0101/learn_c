#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

/*
Exercise 2-3. Write a function htoi(s), which converts a string of hexadecimal digits
(including an optional 0x or 0X) into its equivalent integer value. The allowable digits are 0
through 9, a through f, and A through F.
*/

int htoi(char arr[]);

int main(void) {
        char arr[6];

        strcpy(arr, "123AF");

        printf("%d", htoi(arr));
        return 0;
}

int htoi(char digits[]) {
        int i = 0;
        int sum = 0;
        int length = 0; // Length of the string

        // Get to the last digit of the string
        while (digits[length] != '\0') {
                length++;
        }
        printf("%d \n", length);

        // To not start at the null character
        length--;
        
        // Conduct multiplication operation
        for (i = length; i >= 0; i--) {
                // Check if it is a digit
                if (digits[i] >= '0' && digits[i] <= '9') {
                        // printf("%d \n", digits[i]);
                        // printf("%s %d \n", "sixteen to the power of", length - i);
                        sum += (pow(16, (length - i)) * (digits[i] - '0'));
                }

                // check if its a lower case character
                else if (digits[i] >= 'a' && digits[i] <= 'f') 
                {
                        sum += (pow(16, (length - i)) * (digits[i] - 'W'));
                }

                // check if its a upper case character 
                else if (digits[i] >= 'A' && digits[i] <= 'F') 
                {
                        sum += (pow(16, (length - i)) * (digits[i] - '7'));
                }
        }
        return sum;
}