/*
Exercise 8-4. The standard library function
int fseek(FILE *   fp, long offset, int origin)
is identical to lseek except that fp is a file pointer instead of a file descriptor and return value
is an int status, not a position. Write fseek. Make sure that your fseek coordinates properly
with the buffering done for the other functions of the library. 
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
// #define getc(p) (--(p)->cnt >= 0                  \
//                      ? (unsigned char)*(p)->ptr++ \
//                      : _fillbuf(p))

#define getchar() getc(stdin)
#define putcher(x) putc((x), stdout)

#define PERMS 0666 /* RW for owner, group, others */
#define MAXLINE 20

int fseek(FILE* fp, long offset, int origin);

int getc(FILE* p) {
    return (--(p)->cnt >= 0                  \
                     ? (unsigned char)*(p)->ptr++ \
                     : _fillbuf(p));
}

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

/* _fillbuf: allocate and fill input buffer */
int _fillbuf(FILE *fp)
{
    int bufsize;
    if ((fp->flag & (_READ | _EOF | _ERR)) != _READ)
        return EOF;
    bufsize = (fp->flag & _UNBUF) ? 1 : MAXLINE;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag |= _EOF;
        else
            fp->flag |= _ERR;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

int _flushbuf(int c, FILE* fp) 
{
    int buf_size = (fp->flag & _UNBUF) ? 1 : MAXLINE;

    if (fp->base == NULL)               // base hasn't been allocated, allocate a buffer for it
    {
        fp->base = malloc(buf_size);     // Allocate buffer for base
        if (fp->base == NULL)
        {
            return EOF;
        }
        fp->ptr = fp->base;
    }

    if ((fp->flag & _ERR) || (fp->flag & _EOF))
    {
        return EOF;
    }

    if ((fp->flag & _WRITE) != _WRITE || (fp->flag & _ERR) == _ERR)
    {
        return EOF;
    }
    
    // Write HANDLES: buffer has characters or buffer doesn't have anything.
    int bytes_written = write(fp->fd, fp->base, fp->ptr - fp->base);
    if (bytes_written <= 0)
    {
        return EOF;
    }

    // actual answer logic.
    // if null, malloc to base
    // if not null, write the number of bytes to the file and 

    
    // then for both cases, set fp->ptr to fp->base
    // set the first buffer char to c
    // increment ptr
    // decrement cnt

    // We've written the buffer contents to the file
    /*
    Understanding:
    
    On the outside, we need the character passed in.
    On the inside, we need to put this new character in the buffer and make sure that the file will get impacted by this character
    
    Since the write expression above controls the number of characters we print to the file (if early flush),
    we won't overwrite any (original) file contents with a non full buffer. 
    - THEREFORE, we don't need read.
    
    WE WRITE ONLY the non null characters in the buffer.
    
    No READ needed.

    Reset ptr to base. Purpose of ptr: point to next position in buffer to change, also showing which characters in buffer are modified.
    Reset count. Purpose: to tell us buffer size
    Decrement count by 1. Since we modified one thing in buffer already.
    */

    free(fp->base);                     // clear previous contents
    fp->base = malloc(buf_size);         // reset values

    fp->ptr = fp->base;
    fp->cnt = buf_size;
    *(fp->ptr) = c;
    (fp->ptr)++;
    fp->cnt--;

    // put the character at the initial position of the new buffer
    return c;
}


int fflush(FILE* stream)
{
    if (stream == NULL) 
    {
        return -1;
    }

    if ((stream->flag & _WRITE) != _WRITE)
    {
        return EOF;
    }

    if (stream->base == NULL || stream->ptr == NULL)   // Check if buffer base hasn't been allocated
    {
        stream->base = malloc(MAXLINE); // CHECK IF MALLOC FAILS
        if (stream->base == NULL)
        {
            return EOF;
        }
        stream->ptr = stream->base;
    }

    int bytes_written = write(stream->fd, stream->base, stream->ptr - stream->base);        // writes buffer to fd
    
    if (bytes_written <= 0)
    {
        return EOF;
    }
    
    free(stream->base);                 // deallocate previous values
    stream->base = malloc(MAXLINE);     // reset buffer values
    if (stream->base == NULL)
    {
        return EOF;
    }
    
    stream->ptr = stream->base;     // set pointer to the first element
    stream->cnt = (stream->flag & _UNBUF) ? 1 : MAXLINE;          // reset count to initial, (if unbuf, every new character causes buffer flush, unless its in the beginning)
    return 0;
}


int fclose(FILE* stream)
{
    if ((stream->flag & _UNBUF) == 0)               // no buffer behaviour
    {
        if ((stream->flag & _WRITE) == _WRITE)      // if we are writing, flush output to file
        {
            fflush(stream);
        }
        
        if (stream->base)                           // Free buffer.
        {
            free(stream->base);
        }
    }
    
    return close(stream->fd) ? EOF : 0;
}


int fseek(FILE* fp, long offset, int origin)
{
    // Consider unbuf flag, just directly skip the buffer considerations
    if ((fp->flag & _UNBUF) == 0)
    {
        if (((fp->flag) & _WRITE) == _WRITE)	// write op file
        {
            // flush potential changes before moving file position
            fflush(fp);
        }
        else if ((fp->flag & _READ) == _READ)	// read op file
        {
            // invalidate the buffer and positions (as we are at a new position)
            fp->ptr = fp->base;
            fp->cnt = -1;
        }
    }

	
	int pos = lseek(fp->fd, offset, origin);
	if (pos == -1)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}


int main(void)
{
    // Test case for reading the input
	FILE* in = fopen("in3.txt", "r");
    int first = getc(in);
    
    if (in == NULL)
    {
        return -1;
    }

	fseek(in, 5, 0);
    int second = getc(in);

    fclose(in);

    // Test case for append.
    in = fopen("in3.txt", "a");
    first = putc('x', in);
    fflush(in);
    fseek(in, 5, 0);
    second = putc('x', in);
    fflush(in);
    fclose(in);

    // Test case for writing
    in = fopen("in3.txt", "w");
    first = putc('x', in);
    fflush(in);
    fseek(in, 0, 0);
    second = putc('x', in);
    fflush(in);
    fclose(in);


    return 0;
}
