#include <stdio.h>

enum boolean { FALSE, TRUE };

int a;

int str_len(const char a[]);

int main(void) {
        enum boolean this_is_true = TRUE;
        while (this_is_true) {
                printf("This is true\n");
                this_is_true = FALSE;
        }
        int b;
        int c;

        // printf("%s %d\n", "this is int a:", a);
        // printf("%s %d\n", "this is int b:", b);
        // printf("%s %d\n", "this is int c:", c);

        char a[10] = "hello";
        printf("%d \n", str_len(a));
}

int str_len(const char a[]) {
        int i = 0;
        while (a[i] != '\0') {
                i++;
        }
        return i;
}