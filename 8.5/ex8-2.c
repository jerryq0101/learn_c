/*
Exercise 8-2. Rewrite fopen and _fillbuf with fields instead of explicit bit operations.
Compare code size and execution speed.
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

typedef struct FIELDFLAG
{
    unsigned int _READ : 1;     // this field has a width of 1
    unsigned int _WRITE : 1;
    unsigned int _UNBUF : 1;
    unsigned int _EOF : 1;
    unsigned int _ERR : 1;
};

typedef struct _iobuf_bitfield
{
    int cnt;    /* characters left */
    char *ptr;  /* next character position */
    char *base; /* location of buffer */
    struct FIELDFLAG* flag;   /* mode of file access */
    int fd;     /* file descriptor */
} FILE_FIELD;


extern FILE _iob[OPEN_MAX] = { /* stdin, stdout, stderr, and the rest are empty slots*/
 { 0, (char *) 0, (char *) 0, _READ, 0 },
 { 0, (char *) 0, (char *) 0, _WRITE, 1 },
 { 0, (char *) 0, (char *) 0, _WRITE | _UNBUF, 2 }
};
#define stdin (&_iob[0])
#define stdout (&_iob[1])
#define stderr (&_iob[2])

extern FILE_FIELD _iob_field[OPEN_MAX] = { /* stdin, stdout, stderr */
 { 0, (char *) 0, (char *) 0, {1, 0, 0, 0, 0}, 0 },
 { 0, (char *) 0, (char *) 0, {0, 1, 0, 0, 0}, 1 },
 { 0, (char *) 0, (char *) 0, {0, 1, 1, 0, 0}, 2 }
};
// #define stdin (&_iob_field[0])
// #define stdout (&_iob_field[1])
// #define stderr (&_iob_field[2])

int _fillbuf(FILE *);
// int _flushbuf(int, FILE *);

// #define feof(p) ((p)->flag & _EOF) != 0)
// #define ferror(p) ((p)->flag & _ERR) != 0)
// #define fileno(p) ((p)->fd)
// #define getc(p) (--(p)->cnt >= 0                  \
//                      ? (unsigned char)*(p)->ptr++ \
//                      : _fillbuf(p))
// #define putc(x, p) (--(p)->cnt >= 0         \
//                         ? *(p)->ptr++ = (x) \
//                         : _flushbuf((x), p))
// #define getchar() getc(stdin)
// #define putcher(x) putc((x), stdout)

#define PERMS 0666 /* RW for owner, group, others */

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
    bufsize = (fp->flag & _UNBUF) ? 1 : BUFSIZ;
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


FILE_FIELD *fopen_field(char *name, char *mode)
{
    int fd;
    FILE_FIELD *fp;
    
    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
        return NULL;
    for (fp = _iob_field; fp < _iob_field + OPEN_MAX; fp++)
        if ((fp->flag == NULL))
            break;             /* found free slot */
    if (fp >= _iob_field + OPEN_MAX) /* no free slots */
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
    
    fp->flag = (struct FIELDFLAG*) malloc(sizeof(struct FIELDFLAG));
    if (*mode == 'r') 
    {
        fp->flag->_READ = 1;
    }
    else
    {
        fp->flag->_WRITE = 1;
    }
    return fp;
}

/* _fillbuf: allocate and fill input buffer */
int _fillbuf_field(FILE_FIELD *fp)
{
    int bufsize;
    if (fp->flag->_EOF || fp->flag->_ERR)
        return EOF;
    bufsize = (fp->flag->_UNBUF) ? 1 : BUFSIZ;
    if (fp->base == NULL) /* no buffer yet */
        if ((fp->base = (char *)malloc(bufsize)) == NULL)
            return EOF; /* can't get buffer */
    fp->ptr = fp->base;
    fp->cnt = read(fp->fd, fp->ptr, bufsize);
    if (--fp->cnt < 0)
    {
        if (fp->cnt == -1)
            fp->flag->_EOF = 1;
        else
            fp->flag->_ERR = 1;
        fp->cnt = 0;
        return EOF;
    }
    return (unsigned char)*fp->ptr++;
}

#include <time.h>

int printf(const char *format, ...);

#define MAXLINE 100
#define ITERATIONS 1000

int main(void)
{
    clock_t start = clock();
    for (int i = 0 ; i < ITERATIONS; i++)
    {
        FILE* p = fopen("in1.txt", "r");
        if (p != NULL)
        {
            _fillbuf(p);
            if (p-> base != NULL)              // check if fillbuf operated correctly
            {
                free(p->base);                 // Free the allocated memory in fillbuf for the buffer (if its not made using malloc, then, system will handle it)
            }
            close(p->fd);                      // for the fd that is opened, we should still close it since system doesn't care for this.
        }
    }
    clock_t end = clock();

    double cpu_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("fopen and _fillbuf using bitwise: %lf\n", cpu_time);

    clock_t start2 = clock();
    for (int i = 0 ; i < ITERATIONS; i++)
    {
        FILE_FIELD* p = fopen_field("in1.txt", "r");
        if (p != NULL)
        {
            _fillbuf_field(p);
            if (p-> base != NULL)              // check if fillbuf operated correctly
            {
                free(p->base);                 // Free the allocated memory in fillbuf for the buffer (if its not made using malloc, then, system will handle it)
            }
            // clean up for opened p
            free(p->flag);                     // Free the buffer allocated for BITFIELDS struct (the other vars in the filefield struct not dynamically allocated, so we don't need to take care of it)
            close(p->fd);                      // for the fd file that is opened, we should close it since system doesn't care for this.
        }
    }
    
    clock_t end2 = clock();

    double cpu_time2 = ((double) (end2 - start2)) / CLOCKS_PER_SEC;
    printf("fopen and _fillbuf using fields: %lf\n", cpu_time2);
}
