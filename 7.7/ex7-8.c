/*
Exercise 7-8. Write a program to print a set of files, starting each new one on a new page,
with a title and a running page count for each file.
*/
#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 100
#define MAXPAGELINES 10

int main(int argc, char* argv[])
{
    int count = 1;
    int page = 0;
    while (argc-- > 1)
    {
        FILE* file = fopen(argv[count++], "r");
        if (file == NULL)
        {
            fprintf(stderr, "Can't open %s\n", argv[count]);
            exit(1);
        }
        
        char* line = malloc(MAXLINE);

        printf("Page %d\n", ++page);

        int lines_printed = 0;
        while (fgets(line, MAXLINE, file) != NULL)
        {
            if (lines_printed > 0 && lines_printed % MAXPAGELINES == 0)
            {
                printf("\n");
                printf("Page %d\n", ++page);
            }
            printf(line);
            lines_printed++;
        }
        printf("\n\n");
        fclose(file);
        free(line);
    }
    exit(0);
}