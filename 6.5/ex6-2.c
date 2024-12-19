/*
Exercise 6-2. Write a program that reads a C program and prints in alphabetical order each
group of variable names that are identical in the first 6 characters, but different somewhere
thereafter. Don't count words within strings and comments. Make 6 a parameter that can be
set from the command line.

Finding list of variables.

insert list into some tree (nodes with word lists), which should allow us to group stuff with same 6 letters.

find and print word lists.
*/

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAXWORD 100
#define MAXGROUP 10
#define ALPHABET 26

int getch(void);
void ungetch(int);
int isKeyword(char* str);
int getword(char *, int);
void add_string_to_arr(char** arr, int length, char* element);


//////////////// BUILDING A PREFIX TREE TO FIND SIMILARLY NAMED WORDS //////////////////


// held_character: the character represented at this node
// children: the possible next characters
// strings: the strings that match this prefix
struct wnode {
        char held_character;
        struct wnode* children[ALPHABET];
        char* strings[MAXGROUP];
};

struct wnode *alloc(void);
struct wnode* add_node(struct wnode* node, char new_character,const char* word);
void bfs_to_level(struct wnode* root, int target_level);

static struct wnode* tries[ALPHABET];

/* walloc: make a wnode */
struct wnode *alloc(void)
{
        struct wnode *node = malloc(sizeof(struct wnode));
        for (int i = 0; i < ALPHABET; i++) {
                node->children[i] = NULL;
        }
        for (int i = 0; i < MAXGROUP; i++) {
                node->strings[i] = NULL;
        }
        return node;
}

int main(void) 
{
        int n;
        char word[MAXWORD];

        FILE *fp = fopen("input.txt", "r");
        if (fp == NULL)
        {
                printf("Error opening file\n");
                return 1;
        }
        stdin = fp;
        
        while (getword(word, MAXWORD) != EOF)
        {
                // do stuff with the word.
                if (isalpha(word[0]))
                {
                        // Check if the word is a program keyword, then don't print it
                        if (!isKeyword(word) && strlen(word) >= 6)
                        {
                                printf("Variable name: %s", word);

                                // Situation: If they don't begin with the same initial char,
                                // They don't equal anyway.
                                
                                // see what is the initial character
                                        // make an initial node in the tries array with that character
                                struct wnode* curr_node = NULL;
                                switch (word[0])
                                {
                                        case 'a': {
                                                if (tries['a'-'a'] == NULL) {
                                                        struct wnode* a_wnode = alloc();
                                                        a_wnode->held_character = 'a';
                                                        curr_node = a_wnode;
                                                        tries['a' - 'a'] = a_wnode; 
                                                } else {
                                                        curr_node = tries['a'-'a'];
                                                }
                                                break;
                                        }
                                        default:
                                                break;
                                        
                                }
                                
                                // while there are more characters in the word
                                        // use the same initial node to add a character.
                                        // put that node into an addnode function
                                        // save the latest node
                                char* w = &word; // index of the word
                                w++;

                                while ((*w) != '\0' && curr_node != NULL)
                                {
                                        struct wnode* newly_added = add_node(curr_node, *w, word);
                                        curr_node = newly_added;
                                        w++;
                                }
                        }
                }
        }
        fclose(fp);


        // Tree construction is finished and its all in the trie.

        // loop through the trie array, and find level 6 of all the structs by doing bfs,
                // and printing out existing groups
        
        for (int i = 0; i < ALPHABET; i++)
        {
                bfs_to_level(tries[i], 6);
        }
}

// BFS 
void bfs_to_level(struct wnode* root, int target_level)
{
        if (!root)
        {
                return;
        }

        struct wnode* queue[1000];
        int front = 0;  // Front of queue
        int rear = 0;   // End of queue
        int level = 1;  // Start at level 1 since root is one character
        int level_nodes = 1;    // Nodes at current level
        int next_level = 0;     // Nodes at next level 

        queue[rear] = root;
        rear++;

        while (front < rear && level < target_level) 
        // We won't break if there are more nodes to process and level is smaller than target level
        {
                struct wnode* node = queue[front];
                front++;        // Since the front node is popped
                level_nodes--;

                // Add children to queue
                for (int i = 0; i < ALPHABET; i++)
                {
                        if (node->children[i])
                        {
                                queue[rear] = node->children[i];
                                rear++; // Increment pipe length
                                next_level++;   // Increment nodes at next level
                        }
                }

                if (level_nodes == 0)
                {
                        level++;        // We finished processing nodes we have for this level (since we can't distinguish it from the queue)
                        level_nodes = next_level;       // Go to the next level
                        next_level = 0;                 // Set the next level 
                }
        }

        // Reached the target level.
        // All of the desired children should be at this level
        if (level == target_level)
        {
                // Print the group
                // queue[front].strings
                for (int i = 0; i < MAXGROUP; i++) {
                        if (queue[front]->strings[i] != NULL) {
                                        printf("%s\n", queue[front]->strings[i]);
                        }
                }
        }
}



// add_node:
// if desired character node doesn't exist under this trie: just directly appends a value to the given node
// else: don't add a node, and just return the corresponding next character node
// BOTH CASES: should append the string to the node lists

struct wnode* add_node(
                struct wnode* node, 
                char new_character,
                const char* word
        )
{
        struct wnode* arr_value = node->children[new_character - 'a'];

        if (arr_value == NULL) // This path doesn't exist yet, so create a new node
        {
                struct wnode* new_node = alloc();
                new_node->held_character = new_character;
                
                // set the string of the path
                add_string_to_arr(new_node->strings, MAXGROUP, word);

                // set one of the node's children to this
                node->children[new_character -'a'] = new_node;
                return new_node;
        }
        else // The path exists
        {
                // set the string here
                add_string_to_arr(arr_value->strings, MAXGROUP, word);

                // then return
                return arr_value;
        }
}


void add_string_to_arr(char** arr, int length, char* element)
{
        char** end = arr + length;

        while (arr < end){
                // check if a string spot is free
                if ((*arr) == NULL)
                {
                        // need to make a string copy in case the element changes
                        *arr = strdup(element);
                        return;
                }
                arr++;
        }
        return;
}


/////////////// FINDING THE VARIABLE NAMES LONGER THAN 6 characters ////////////

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
        int c, getch(void);
        void ungetch(int);
        char *w = word; // passed in pointer to fill.
        while (isspace(c = getch()))
                ;
        if (c != EOF)
                *w++ = c;
        if (!isalpha(c)) // can't do all punct otherwise might absorb everything
        {
                *w = '\0';
                return c;
        }
        for (; --lim > 0; w++){
                *w = getch();
                if ((*w) == ';' || (*w) == ' ' || (*w) == '=') 
                {
                        ungetch(*w);
                        break;
                }
                else if (!isalnum(*w) && *w != '_') 
                // Other cases of not variable termination, so not variable
                // scan for next characters
                {
                        break;
                }
        }
        *w = '\0';
        return word[0];
}



#define BUFSIZE 100
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getch(void)    /* get a (possibly pushed-back) character */
{
        return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push character back on input */
{
        if (bufp >= BUFSIZE)
                printf("ungetch: too many characters\n");
        else
                buf[bufp++] = c;
}


// Function to check whether the given
// string is a keyword or not
// Returns 'true' if the string is a KEYWORD.
int isKeyword(char* str)
{
        if (!strcmp(str, "auto") || !strcmp(str, "default")
                || !strcmp(str, "signed") || !strcmp(str, "enum")
                || !strcmp(str, "extern") || !strcmp(str, "for")
                || !strcmp(str, "register") || !strcmp(str, "if")
                || !strcmp(str, "else") || !strcmp(str, "int")
                || !strcmp(str, "while") || !strcmp(str, "do")
                || !strcmp(str, "break") || !strcmp(str, "continue")
                || !strcmp(str, "double") || !strcmp(str, "float")
                || !strcmp(str, "return") || !strcmp(str, "char")
                || !strcmp(str, "case") || !strcmp(str, "const")
                || !strcmp(str, "sizeof") || !strcmp(str, "long")
                || !strcmp(str, "short") || !strcmp(str, "typedef")
                || !strcmp(str, "switch")
                || !strcmp(str, "unsigned") || !strcmp(str, "void")
                || !strcmp(str, "static") || !strcmp(str, "struct")
                || !strcmp(str, "goto") || !strcmp(str, "union")
                || !strcmp(str, "volatile")|| !strcmp(str, "stdio") 
                || !strcmp(str, "include") || !strcmp(str, "main"))
        {
                        return 1;
        }       
    return 0;
}
