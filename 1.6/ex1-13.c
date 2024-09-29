# include <stdio.h>

# define EXIT_CHAR '~'

int main(void) {
    int c, i;
    int lengths[20];

    // Initialize the counts
    for (i = 0; i < 20; ++i)
        lengths[i] = 0;
    
    while ((c = getchar()) != EXIT_CHAR) {
        int length, marked;
        length = 0;
        marked = 0;

        while (c != ' ' && c != '\n' && c != '\t' && c != '\b') {
            ++length;
            marked = 1;
            c = getchar();
        }

        if (marked == 1) {
            ++lengths[length];
        }
    }
    
    for (i = 0; i < 20; i++){
        printf("%d %d\n", i, lengths[i]);
    }
}