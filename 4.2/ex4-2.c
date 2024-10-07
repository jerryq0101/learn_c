#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAX_LINE 100

int main(void) {
        double sum, atof(char []);
        char line[10];

        strcpy(line, "1.2345");
        printf("%f \n", atof(line));
        return 0;
}

/* atof: convert string s to double */
double atof(char s[])
{
        double val, power;
        int i, sign;
        for (i = 0; isspace(s[i]); i++) /* skip white space */
                ;
        sign = (s[i] == '-') ? -1 : 1;
        if (s[i] == '+' || s[i] == '-')
                i++;
        for (val = 0.0; isdigit(s[i]); i++)
                val = 10.0 * val + (s[i] - '0');

        // i stops when symbol not a digit
        // either a period or e

        // if i is a period, increment and get decimal values
        if (s[i] == '.')
                i++;
        for (power = 1.0; isdigit(s[i]); i++)
        {
                val = 10.0 * val + (s[i] - '0');
                power *= 10;
        }

        printf("%lf \n", val);
        printf("%f \n", power);

        // if i is an e, increment and get how many times the scientific notation is.
        int sci = 0;
        int increasing = 1;
        // for the scientific notation
        if (s[i] == 'e') {
                i++;
                if (s[i] == '-') {
                        i++;
                        increasing = 0;
                }
        }
        for (sci = 0; isdigit(s[i]); i++){
                sci = 10*sci + (s[i] - '0');
        }

        // add decimals onto the end
        val /= power;

        printf("%lf \n", val);
        
        if (increasing) {
                while (sci > 0) {
                        val *= 10;
                        sci--;
                }
        } else {
                while (sci > 0) {
                        val /= 10;
                        sci--;
                }
        }
        
        return sign * val;
}