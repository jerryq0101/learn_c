#include <stdio.h>

struct point {
        int x;
        int y;
};

int main(void) 
{
        struct point thing = {1, 2};
        printf("%d %d", thing.x, thing.y);
        
        return 0;
}