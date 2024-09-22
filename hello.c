# include <stdio.h>

int main() {
    float fahr, celsius, lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;

    // Heading 
    printf("%1s %3s %1s %6s %1s\n", "|", "F","|", "C", "|");
    printf("%1s %3s %1s %6s %1s\n", "|", "---", "|", "------", "|");
    while (fahr <= upper) {
        celsius = 5.0 * (fahr - 32.0) / 9.0;
        printf("%1s %3.0f %1s %6.1f %1s \n", "|", fahr, "|", celsius, "|");
        fahr = fahr + step;
    }
    
    printf("hello world");
}