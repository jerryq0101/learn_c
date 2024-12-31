/*
Exercise 8-5. Modify the fsize program to print the other information contained in the inode
entry. 
*/

#include <sys/dir.h> /* local directory structure */

// int fstat(int fd, struct stat *);

#include <stdio.h>
#include <string.h>
#include <fcntl.h>     /* flags for read and write */
#include <sys/types.h> /* typedefs */
#include <sys/stat.h>  /* structure returned by stat */
#include "dirent.h"


#define NAME_MAX 14 /* longest filename component; */
/* system-dependent */
typedef struct
{                            /* portable directory entry */
    long ino;                /* inode number */
    char name[NAME_MAX + 1]; /* name + '\0' terminator */
} Dirent;

// DIR *opendir(char *dirname);
// Dirent *readdir(DIR *dfd);
// void closedir(DIR *dfd);

char *name;
struct stat stbuf;
// int stat(char *, struct stat *);
// stat(name, &stbuf);

// struct stat /* inode information returned by stat */
// {
//     dev_t st_dev;    /* device of inode */
//     ino_t st_ino;    /* inode number */
//     short st_mode;   /* mode bits */
//     short st_nlink;  /* number of links to file */
//     short st_uid;    /* owners user id */
//     short st_gid;    /* owners group id */
//     dev_t st_rdev;   /* for special files */
//     off_t st_size;   /* file size in characters */
//     time_t st_atime; /* time last accessed */
//     time_t st_mtime; /* time last modified */
//     time_t st_ctime; /* time originally created */
// };

#define DIRSIZ 14

// struct dirent
// {                        /* directory entry */
//     ino_t d_ino;         /* inode number */
//     char d_name[DIRSIZ]; /* long name does not have '\0' */
// };

void fsize(char *); /* print file name */


int main(int argc, char* argv[])
{
    if (argc == 1) /* default: current directory */
        fsize(".");
    else
        while (--argc > 0)
            fsize(*++argv);
    return 0;
}

// int stat(char *, struct stat *);
void dirwalk(char *, void (*fcn)(char *));
/* fsize: print the name of file "name" */
void fsize(char *name)
{
    struct stat stbuf;
    if (stat(name, &stbuf) == -1)
    {
        fprintf(stderr, "fsize: can't access %s\n", name);
        return;
    }
    if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
    {
        dirwalk(name, fsize);
    }
    printf("%8ld %s\n", stbuf.st_size, name);
}

#define MAX_PATH 1024
/* dirwalk: apply fcn to all files in dir */
void dirwalk(char *dir, void (*fcn)(char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;
    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
            continue; /* skip self and parent */
        if (strlen(dir) + strlen(dp->name) + 2 > sizeof(name))
            fprintf(stderr, "dirwalk: name %s %s too long\n",
                    dir, dp->name);
        else
        {
            sprintf(name, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

/* opendir: open a directory for readdir calls */
// DIR *opendir(char *dirname)
// {
//     int fd;
//     struct stat stbuf;
//     DIR *dp;
//     if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIR *)malloc(sizeof(DIR))) == NULL)
//         return NULL;
//     dp->fd = fd;
//     return dp;
// }

/* closedir: close directory opened by opendir */
// void closedir(DIR *dp)
// {
//     if (dp)
//     {
//         close(dp->fd);
//         free(dp);
//     }
// }

/* readdir: read directory entries in sequence */
// Dirent *readdir(DIR *dp)
// {
//     struct direct dirbuf; /* local directory structure */
//     static Dirent d;      /* return: portable structure */
//     while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
//     {
//         if (dirbuf.d_ino == 0) /* slot not in use */
//             continue;
//         d.ino = dirbuf.d_ino;
//         strncpy(d.name, dirbuf.d_name, DIRSIZ);
//         d.name[DIRSIZ] = '\0'; /* ensure termination */
//         return &d;
//     }
//     return NULL;
// }
