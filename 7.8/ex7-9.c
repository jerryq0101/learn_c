/*
Exercise 7-9. Functions like isupper can be implemented to save space or to save time.
Explore both possibilities.

int isupper(int argument);
*/

int main(void)
{

}

int isspaceminspace(int a)
{
    return a == ' ' || a == '\t' || a == '\n' || a == '\v' || a == '\f' || a == '\f' || a == '\r';
}

static const unsigned char space_table[256] = {
   [' '] = 1,   // space
   ['\t'] = 1,  // horizontal tab
   ['\n'] = 1,  // newline
   ['\v'] = 1,  // vertical tab
   ['\f'] = 1,  // form feed
   ['\r'] = 1   // carriage return
};

int isspacemintime(int c) {
   return (unsigned)c < 256 && space_table[c];
}

int isuppermin(int a)
{
    return a >= 65 && a <= 90;
}