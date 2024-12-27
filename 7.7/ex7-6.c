/*
Exercise 7-6. Write a program to compare two files, printing the first line where they differ. 
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINE 100

int main(void)
{
    FILE* in1 = fopen("in1.txt", "r");
    FILE* in2 = fopen("in2.txt", "r");
    

    char* line1 = malloc(MAXLINE);
    char* line2 = malloc(MAXLINE);
    char* status1;
    char* status2;
    while ((status1 = fgets(line1, MAXLINE, in1)) != NULL && (status2 = fgets(line2, MAXLINE, in2)) != NULL)
    {
        if (strcmp(line1, line2) != 0)      // case of differing lines
        {
            printf("Differing lines: \n");
            printf("in1: %s\n", line1);
            printf("in2: %s\n", line2);
            fclose(in1);
            fclose(in2);
            return 0;
        }
    }

    if (status1 == NULL && status2 != NULL)
    {
        printf("in1 reached EOF");
    } else if (status1 != NULL && status2 == NULL)
    {
        printf("in2 reached EOF");
    }
    return 0;
}
