# include <stdio.h>

# define EXIT_CHAR '~'

int main(void) {
    int c, i;
    int frequencies[26];
    int nwhite, nother;

    nwhite = nother = 0;
    for (i = 0; i < 26; ++i) {
        frequencies[i] = 0;
    }

    while ((c = getchar()) != EXIT_CHAR) {
        if (c >= 'a' && c <= 'z') {
            ++frequencies[c-'a'];
        } 
        else if (c == ' ' || c == '\n' || c == '\t') {
            ++nwhite;
        }
        else {
            ++nother;
        }
    }

    for (i = 0; i < 26; ++i) {
        printf("%c %d\n", 'a' + i, frequencies[i]);
    }
    printf("%s %d\n", "Whitespace", nwhite);
    printf("%s, %d\n", "Other", nother);
}
