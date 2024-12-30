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
#define MAXLINE 20


int putc(int x, FILE* p) {
    return --(p)->cnt >= 0 ? *(p)->ptr++ = (x) : _flushbuf((x), p);
}

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


int _flushbuf(int c, FILE* fp) 
{
    // flush into file
    if (fp->base == NULL)   // check if stuff is broken
    {
        return EOF;
    }

    // Write HANDLES: buffer has characters or buffer doesn't have anything.
    int bytes_written = write(fp->fd, fp->base, fp->ptr - fp->base);

    // Now we've written to the buffer, we load the buffer with next set of things
    int bytes_read = read(fp->fd, fp->base, MAXLINE);

    if (bytes_read > 0)         // file position not at end
    {
        fp->ptr = fp->base;
        fp->cnt = bytes_read;
    }
    else if (bytes_read == 0)   // file position at the end
    {
        // Reset values in the buffer 
        free(fp->base);
        fp->base = (char *) malloc(MAXLINE);

        // set the initial values
        fp->ptr = fp->base;
        fp->cnt = MAXLINE;
    }

    // put the character at the initial position of the new buffer
    return (*(fp->base) = c);
}

int main(void)
{
    FILE* in = fopen("in2.txt", "a");           // open the file
    /*
    Append makes the file position at the end of the file
    Read just opens file from beginning
    Write does a creat (clearing entire file)
    */
    in->base = (char *) malloc(MAXLINE);        // initialize the buffer
    *(in->base) = "0123456789012345678";
    in->ptr = in->base + 20;

    /*
    putc logic:
    just put the character in the current buffer and then put it at the current file position when flushing.

    - within the buffer range: sets *fp to value, then goes to the next value
    - at the end of buffer range: calls _flushbuf
    
    _flushbuf called scenarios: Append / Write
    - file position is at the end of file (nothing to read in the file next)
        - stuff in buffer (need to write to file)
        - nothing in buffer (nothing to write)
    - file position not at the end of file (need to read next stuff in the file)
        - stuff in buffer (need to write to file)
        - nothing in buffer (nothing to write)
    */
    putc('a', in);


    close(in->fd);
    return 0;
}
