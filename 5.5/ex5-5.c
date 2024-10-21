
#include <stdio.h>

/*
Exercise 5-5. Write versions of the library functions strncpy, strncat, and strncmp, which
operate on at most the first n characters of their argument strings. For example,
strncpy(s,t,n) copies at most n characters of t to s. Full descriptions are in Appendix B.
*/

char *strncpy_ver(char *dest, const char *src, size_t n);

int main(void) {
        char arr[20];
        char *thing = strncpy_ver(arr, "abcde", 3);
        printf("%s", thing);
}

char *strncpy_ver(char *dest, const char *src, size_t n)
{
        char *temp = dest;
        while (n-- && (*dest++ = *src++))
                ;
        return temp;
}