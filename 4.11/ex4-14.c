#include <stdio.h>

/*
Exercise 4-14. Define a macro swap(t,x,y) that interchanges two arguments of type t.
(Block structure will help.)
*/

#define swap(t, x, y) { \
        t temp = y; \
        y = x; \
        x = temp; \
}

int main(void) {
        int x = 3;
        int y = 5;
        
        swap(int, x, y);

        printf("%d %d", x, y);
}