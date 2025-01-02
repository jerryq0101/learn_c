/*
Exercise 8-6. The standard library function calloc(n,size) returns a pointer to n objects of
size size, with the storage initialized to zero. Write calloc, by calling malloc or by
modifying it. 
*/

#include <stddef.h>

typedef long Align; /* for alignment to long boundary */

union header
{ /* block header */
    struct
    {
        union header *ptr; /* next block if on free list */
        unsigned size;     /* size of this block */
    } s;
    Align x; /* force alignment of blocks */
};

typedef union header Header;

static Header base;          /* empty list to get started */
static Header *freep = NULL; /* start of free list */

/* free: put block ap in free list */
void free(void *ap)
{
    Header *bp, *p;
    bp = (Header *)ap - 1; /* point to block header */
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break; /* freed block at start or end of arena */
    if (bp + bp->s.size == p->s.ptr)
    { /* join to upper nbr */
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
    }
    else
        bp->s.ptr = p->s.ptr;
    if (p + p->s.size == bp)
    { /* join to lower nbr */
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    }
    else
        p->s.ptr = bp;
    freep = p;
}

#define NALLOC 1024 /* minimum #units to request */
/* morecore: ask system for more memory */
static Header *morecore(unsigned nu)
{
    char *cp, *sbrk(int);
    Header *up;
    if (nu < NALLOC)
        nu = NALLOC;
    cp = sbrk(nu * sizeof(Header));

    if (cp == (char *)-1) /* no space at all */
        return NULL;
    up = (Header *)cp;
    up->s.size = nu;
    free((void *)(up + 1));
    return freep;
}

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    unsigned nunits;
    nunits = (nbytes + sizeof(Header) - 1) / sizeof(union header) + 1;
    if ((prevp = freep) == NULL)
    { /* no free list yet */
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits)
        {                            /* big enough */
            if (p->s.size == nunits) /* exactly */
                prevp->s.ptr = p->s.ptr;
            else
            { /* allocate tail end */
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) /* wrapped around free list */
            if ((p = morecore(nunits)) == NULL)
                return NULL; /* none left */
    }
}


#include <stdint.h>
#define SIZE_MAX ((size_t)-1)

void* calloc(size_t nitems, size_t size)
{
    void* ptr;
    void set_to_zero(char*, size_t);

    if (size && nitems && nitems < SIZE_MAX / size)       // check for valid mult value;
    {
        return NULL;
    }

    if ((ptr = malloc(nitems * size)) == NULL)
    {
        return NULL;
    }
    
    for (int i = 0; i < nitems*size; i+=size)
    {
        char* concat_pointer = (char *) ptr;        // same address as ptr - so when dereferencing and set value, it sets ptr's value
        concat_pointer+=i;
        set_to_zero(concat_pointer, size);
    }
    return ptr;
}

void set_to_zero(char* ptr, size_t size)
{
    for (size_t i = 0; i < size; i++)
    {
        *(ptr+i) = 0;
    }
}

int main(void)
{
    void** arr = calloc(5, 5);
}


