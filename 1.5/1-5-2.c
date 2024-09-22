# include <stdio.h>

int main(void) {

    // Using while to count number of characters in input
    long nc;

    while (getchar() != EOF)
        ++nc;

    printf("%ld\n", nc);

    // Using for loop to count number of characters in input
    double fc;
    for (fc = 0; getchar() != EOF; ++fc)
        ;
    printf("%.0f\n", fc);
}