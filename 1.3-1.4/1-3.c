# include <stdio.h>


# define LOWER 0
# define UPPER 300
# define STEP 20
# define FRAC 5.0/9.0

int main(void) {
    int fahr;

    for (fahr = UPPER; fahr >= LOWER; fahr-=20) {
        printf("%3d %6.1f\n", fahr, FRAC * (fahr - 32));
    }
}