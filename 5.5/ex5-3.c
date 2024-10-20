#include <stdio.h>

/*
Exercise 5-3. Write a pointer version of the function strcat that we showed in Chapter 2:
strcat(s,t) copies the string t to the end of s.
*/

void strcat_ptr_ver(char *s, char *t);
void strcat_og(char s[], char t[]);

int main(void)
{
        char msg_one[6] = {'a', 'b', 'c', '\0'};
        char *msg_two = "def";

        strcat_ptr_ver(msg_one, msg_two);
        printf("%s%s", "New function result\n", msg_one);
        
}

// strcat_prt_ver: concat t to the end of s; s must be big enough
void strcat_ptr_ver(char *s, char *t)
{
        while (*s++)
                ;
        s--;
        while ((*s++ = *t++))
                ;
}

/* strcat: concatenate t to end of s; s must be big enough */
void strcat_og(char s[], char t[])
{
        int i, j;
        i = j = 0;
        while (s[i] != '\0') /* find end of s */
                i++;
        while ((s[i++] = t[j++]) != '\0') /* copy t */
                ;
}