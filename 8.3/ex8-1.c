/*
Exercise 8-1. Rewrite the program cat from Chapter 7 using read, write, open, and close
instead of their standard library equivalents. Perform experiments to determine the relative
speeds of the two versions.

TODO: Compile with a macbook.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>    // for read, write
#include <fcntl.h>     // for open, O_RDONLY

#define MAXLINE 100

int function_with_syslvl(int argc, char *argv[]);
int function_with_abstractions(int argc, char *argv[]);

/* cat: concatenate files */
int main(int argc, char *argv[])
{
    clock_t start = clock();
    function_with_abstractions(argc, argv);
    clock_t end = clock();

    double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;

    printf("Time taken by with abstractions:  %f seconds \n", cpu_time);

    start = clock();
    function_with_syslvl(argc, argv);
    end = clock();
    cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time taken by system level: %f seconds \n", cpu_time);
}



int function_with_abstractions(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; /* program name for errors */
    if (argc == 1)        /* no args; copy standard input */
    {
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "%s: can't open %s\n",
                        prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
    }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);

}

/* cat syscall version: concatenate files */
int function_with_syslvl(int argc, char *argv[])
{
    int fd;
    void filecopy_sys(int, int);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1)        /* no args; copy standard input */
    {
        filecopy_sys(0, 1);
    }
    else
    {
        while (--argc > 0)
            if ((fd = open(*++argv, O_RDONLY)) == -1)
            {
                char error_msg[100];
                sprintf(error_msg, "%s: can't open %s\n", prog, *argv);

                write(2, error_msg, strlen(error_msg));
                exit(1);
            }
            else
            {
                filecopy_sys(fd, 1);
                close(fd);
            }
    }

    exit(0);
}


/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;
    while ((c = getc(ifp)) != EOF)
        putc(c, ofp);
}

/* filecopy_sys syscall version: copy file ifp to file ofp */
void filecopy_sys(int ifp, int ofp)
{
    int c;
    char line[MAXLINE];
    
    while ((c = read(ifp, line, MAXLINE)) != 0)
    {
        write(ofp, line, c);            // should have write permissions for stdout
    }

    if (c == -1)
    {
        char error_msg[MAXLINE];
        sprintf(error_msg, "Error, read error for ifp");
        write(2, error_msg, strlen(error_msg));
    }
}
