#include <stdio.h>

int main(void){
        int n, c;
        int i, j;

        n = 5;
        c = 6;

        for (i = 0, j = 0; i < n || j < c; i++, j++)
                ;
        printf("%d %d \n", i, j);
        
}