#include <stdio.h>
#include <time.h>

/*
Exercise 3-1. Our binary search makes two tests inside the loop, when one would suffice (at
the price of more tests outside.) Write a version with only one test inside the loop and
measure the difference in run-time.
*/

/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch_modified(int x, int v[], int n)
{
        int low, high, mid;
        low = 0;
        high = n - 1;
        while (low <= high)
        {
                mid = (low + high) / 2;
                if (x >= v[mid])
                        low = mid + 1;
                else
                        high = mid - 1;
        }

        if (low > 0 && v[low - 1] == x) {
                return low - 1;
        }
        return -1; /* no match */
}



/* binsearch: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, int v[], int n)
{
        int low, high, mid;
        low = 0;
        high = n - 1;
        while (low <= high)
        {
                mid = (low + high) / 2;
                if (x < v[mid])
                        high = mid + 1;
                else if (x > v[mid])
                        low = mid + 1;
                else /* found match */
                        return mid;
        }
        return -1;
}

int main(void)
{
        clock_t start, end; 
        double cpuTimeUsed;
        int arr[5] = {1, 2, 3, 4, 5};
        int x = 3;

        start = clock();
        printf("%d \n", binsearch_modified(x, arr, 5));
        
        end = clock();
        cpuTimeUsed = (double) end - start;
        printf("%f", cpuTimeUsed);

        return 0;
}