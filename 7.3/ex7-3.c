/*
Exercise 7-3. Revise minprintf to handle more of the other facilities of printf. 
*/

#include <stdarg.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;
    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        
        // p is a % symbol
        // get the next character after %, and handle it

        int spec_size = 1;

        void* saved_p = p;
            while (!isalpha(*p))
            {
                spec_size++;
                p++;
            }
        p = (char *) saved_p;

        char* concat_result;

        if (spec_size > 1)
        {
            char* specifier = (char *) malloc(spec_size+1);
            void* saved_specifier = specifier;
            
            while (spec_size > 0)
            {
                *specifier = *p;
                specifier++;
                p++;
                spec_size--;
            }
            *specifier = '\0';
            specifier = (char *) saved_specifier;
            p--;        // go back to the actual d or f or s character

            concat_result = specifier;
        }
        else
        {
            concat_result = (char *) malloc(3);
            *concat_result = '%';
            *(concat_result+1) = *p;
            *(concat_result+2) = '\0';
        }

        switch (*p)
        {
            case 'd':
                ival = va_arg(ap, int);
                printf(concat_result, ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf(concat_result, dval);
                break;
            case 's':
                sval = va_arg(ap, char*);
                printf(concat_result, sval);
                break;
            default:
                putchar(*p);
                break;
        }
        free(concat_result); // Add this
    }
    va_end(ap); /* clean up when done */
}


// field width specifiers

int main(void)
{
    printf("%.5s", "whatthe");
    printf("\n");

    // Precondition: Type maps to the same type argument
    // TODO: Handle this precondition, so that I don't need it
    // e.g. doing d with a float, goes to negative number
    minprintf("%.5f", 12345.1);

    printf("\n");
    printf("%6.1s %6.5f %5.3d", "ab", 12345.1, 123);
    printf("\n");
    minprintf("%6.1s %6.5f %5.3d", "ab", 12345.1, 123);

    printf("\n");
    printf("%6.8s %3.5f %2.3d", "abcde", 12345.15453453, 123);
    printf("\n");
    minprintf("%6.8s %3.5f %2.3d", "abcde", 12345.15453453, 123);


    // TODO, not sure why minprintf always ends with some BS
}
