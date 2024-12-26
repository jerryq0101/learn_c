/*
Exercise 7-4. Write a private version of scanf analogous to minprintf from the previous
section.
*/
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

int getline(char s[], int lim);
void minscanf(char *fmt, ...);
#define MAXLINE 100
#define MAXCONV 10


int main(void)
{
    int* a1 = (int *) malloc(sizeof(int));
    float* b1 = (float *) malloc(sizeof(float));
    char* c1 = (char *) malloc(MAXLINE);
    int* a2 = (int *) malloc(sizeof(int));
    float* b2 = (float *) malloc(sizeof(float));
    char* c2 = (char *) malloc(MAXLINE);

    freopen("input.txt", "r", stdin);

    scanf("%d %f %s\n", a1, b1, c1);
    printf("From scanf: %d %f %s\n", *a1, *b1, c1);

    minscanf("%d %f %s\n", a2, b2, c2);
    printf("From minscanf: %d %f %s", *a2, *b2, c2);
}


void minscanf(char *fmt, ...)
{
    va_list ap;
    char* p;
    int load = 0;
    char curr[MAXCONV];
    char* curr_ptr = curr;
    
    int *ival;
    float *dval;
    char *sval;

    va_start(ap, fmt);

    for (p = fmt; *p; p++)
    {
        // look for each character
        
        if (*p == '%' && load == 0)
        {
            load = 1;
            *curr_ptr = *p;
            curr_ptr++;
        }
        else if (*p != '%' && load == 1)
        {
            *curr_ptr = *p;
            if (*p == 'd' || *p == 'f' || *p == 's')
            {
                load = 0;
                curr_ptr++;
                *curr_ptr = '\0';
                
                switch (*p)
                {
                    case 'd':
                        ival = va_arg(ap, int*);
                        scanf(curr, ival);          // scanf puts the stuff into an argument address, ival is an address
                        break;
                    case 'f':
                        dval = va_arg(ap, float*);
                        scanf(curr, dval);
                        break;
                    case 's':
                        sval = va_arg(ap, char*);
                        scanf(curr, sval);
                        break;
                    default:
                        break;
                }
                
                curr_ptr = curr;
            }
            else
            {
                curr_ptr++; 
            }
        }

    }
    va_end(ap);
}


/* getline: read a line into s, return length */
int getline(char s[], int lim)
{
    int c, i;
    for (i = 0; i < lim - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
        s[i] = c;
    if (c == '\n')
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';
    return i;
}