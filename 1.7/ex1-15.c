#include <stdio.h>

// Exercise 1.15: Rewrite the temperature conversion program of section 1.2 to use a function for conversion.

int fah_to_cel(int);

int main(void)
{
    int fahr, celsius;
    int lower, upper, step;
    lower = 0;   /* lower limit of temperature scale */
    upper = 300; /* upper limit */
    step = 20;   /* step size */
    fahr = lower;
    while (fahr <= upper)
    {
        printf("%d\t%d\n", fahr, fah_to_cel(fahr));
        fahr = fahr + step;
    }
}

int fah_to_cel(int fahr) {
    return 5 * (fahr - 32) / 9;
}