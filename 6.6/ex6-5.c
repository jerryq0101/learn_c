#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Exercise 6-5. Write a function undef that will remove a name and definition from the table
maintained by lookup and install.
*/


struct nlist { /* table entry: */
        struct nlist *next; /* next entry in chain */
        char *name; /* defined name */
        char *defn; /* replacement text */
};

#define HASHSIZE 101
static struct nlist *hashtab[HASHSIZE] = {NULL}; /* pointer table, initialized with null so no garbage values */

/* hash: form hash value for string s */
unsigned hash(char *s)
{
        unsigned hashval;
        for (hashval = 0; *s != '\0'; s++)
                hashval = *s + 31 * hashval;
        return hashval % HASHSIZE;
}

/* lookup: look for s in hashtab */
struct nlist *lookup(char *s)
{
        struct nlist *np;
        for (np = hashtab[hash(s)]; np != NULL; np = np->next)
                if (strcmp(s, np->name) == 0) 
                        return np;      /* found */
        return NULL;                    /* not found */
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char* name, char* defn)
{
        struct nlist *np;
        
        if ((np = lookup(name)) == NULL)        // name doesn't exist in hashtab yet
        {
                struct nlist *new_entry = (struct nlist *) malloc(sizeof (struct nlist));       // allocate memory for a new entry
                if (new_entry == NULL || (new_entry->name = strdup(name)) == NULL)              // set new name, and check if its null.
                {
                        return NULL;
                }
                np = new_entry;
                unsigned hashvalue = hash(name);         // get hash
                np->next = NULL;                        // set next to be null initially.
                hashtab[hashvalue] = np;        // put new value at array spot
        }
        else
        {
                free((void *) np->defn);        // cast the char ptr to void (I don't have to include this, any pointer just converts to void) and free it
        }

        // Set new replacement text for the definition for both cases
        if ((np->defn = strdup(defn)) == NULL)
        {
                return NULL;
        }

        return np;
}

/* undef: removes (name, defn) from the hashtable */
void undef(char* name, char* defn)
{
        struct nlist* np;
        struct nlist* prev = NULL;
        
        for (np = hashtab[hash(name)]; np != NULL; np = np->next)
        {
                if (strcmp(np->name, name) == 0)        // do something
                {
                        if (prev == NULL) // if this is the head
                        {
                                hashtab[hash(name)] = np->next;
                        }
                        else
                        {
                                prev->next = np->next;
                        }
                        free(np);
                }
        }
}

// /* undef: removes (name, defn) from the hashtable */
// int undef(char* name, char* defn)
// {
//         struct nlist* np;

//         if ((np = lookup(name)) == NULL)
//         {
//                 return 1;
//         }
//         else                             // np != null
//         {
//                 if (np->next != NULL) // case where next element of np is not null.
//                 {
//                         struct nlist* temp = np->next;
//                         *np = *(np->next);
//                         free(temp);
//                 }
//                 else // case where next elemnt of np is null
//                 {
//                         free(np);
//                         np = NULL;
//                         // This part is bad since the np is still being referenced by the last element. 
//                         // and/or if this is the head, the original np address is still there. (so its not null)
//                         // conclusion: just use prev and next elements, draw it out!
//                 }
//         }
// }

int main(void)
{
        char* string1 = "hello";
        char* string2 = "wassup";
        char* string3 = "lil";
        char* string4 = "big";
        char* string5 = "shalom";
        char* string6 = "bible";

        install(string1, string2);
        install(string3, string4);
        install(string5, string6);

        undef(string5, string6);
}