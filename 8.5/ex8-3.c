/*
Exercise 8-3. Design and write _flushbuf, fflush, and fclose.
*/

#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

#define EOF (-1)
#define BUFSIZ 1024
#define OPEN_MAX 20 /* max #files open at once */

typedef struct _iobuf
{
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    int flag;   /* mode of file access */
    int fd;     /* file descriptor */
} FILE;

enum _flags
{
    _READ = 01,  /* file open for reading */
    _WRITE = 02, /* file open for writing */
    _UNBUF = 04, /* file is unbuffered */
    _EOF = 010,  /* EOF has occurred on this file */
    _ERR = 020   /* error occurred on this file */
};


extern FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr, and the rest are empty slots*/
 { 0, (char *) 0, (char *) 0, _READ, 0 },
 { 0, (char *) 0, (char *) 0, _WRITE, 1 },
 { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])


int _fillbuf(FILE *);
int _flushbuf(int, FILE *);

#define feof(p) ((p)->flag & _EOF) != 0)
#define ferror(p) ((p)->flag & _ERR) != 0)
#define fileno(p) ((p)->fd)
#define getc(p) (--(p)->cnt >= 0                  \
                     ? (unsigned char)*(p)->ptr++ \
                     : _fillbuf(p))

#define getchar() getc(stdin)
#define putcher(x) putc((x), stdout)

#define PERMS 0666 /* RW for owner, group, others */
#define MAXLINE 100

// int _flushbuf(int c, FILE* fp) 
// {
//     if (fp == NULL || fp->base == NULL) {
//         return EOF;
//     }

//     // commits the buffer to the file
//     int num_written = write(fp->fd, fp->base, fp->ptr - fp->base);    // (file descriptor, buffer beginning, number of characters from buffer beginning)
//     if (num_written == -1) {
//         fp->flag |= _ERR;
//         return EOF;
//     }

//     // reread the buffer
//     int bytes_read = read(fp->fd, fp->base, MAXLINE);   // read from the file into fp's base
    
//     if (bytes_read == 0) {

//     }
//     if (bytes_read == 0) {
//         if (bytes_read == -1) {
//             fp->flag |= _ERR;
//         }
//         return EOF;
//     }
//     fp->cnt = bytes_read;                               // set fp's cnt to characters read
//     fp->ptr = fp->base;                                 // set the next character pointer to beginning character

//     return *(fp->ptr++);
// }

// int putc(int x, FILE* p) {
//     return --(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p);
// }

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
        if ((fp->flag & (_READ | _WRITE)) == 0)
            break;             /* found free slot */
    if (fp >= _iob + OPEN_MAX) /* no free slots */
        return NULL;
    if (*mode == 'w')
        fd = creat(name, PERMS);
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
            fd = creat(name, PERMS);
        lseek(fd, 0L, 2);
    }
    else
        fd = open(name, O_RDONLY, 0);
    if (fd == -1) /* couldn't access name */
        return NULL;
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}



int main(void)
{
    FILE* in = fopen("in2.txt", "a");           // open the file
    in->base = (char *) malloc(MAXLINE);        // initialize the buffer
    in->ptr = in->base;
    
    char* test = (char*) malloc(MAXLINE);
    read(in->fd, test, 1);
    

    close(in->fd);
    return 0;
}
