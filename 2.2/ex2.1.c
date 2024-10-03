#include <stdio.h>
#include <limits.h>

/*
Exercise 2-1. Write a program to determine the ranges of char, short, int, and long
variables, both signed and unsigned, by printing appropriate values from standard headers
and by direct computation. Harder if you compute them: determine the ranges of the various
floating-point types.
*/

int main(void) {
  printf("#################### CHAR #####################\n");
  printf("bits: %d\n", CHAR_BIT);
  printf("unsigned char max: %d\n", UCHAR_MAX);
  printf("signed char min: %d\n", SCHAR_MIN);
  printf("signed char max: %d\n", SCHAR_MAX);
  printf("\n");

  printf("##################### INT #####################\n");
  printf("unsigned int max: %u\n", UINT_MAX);
  printf("signed int min: %d\n", INT_MIN);
  printf("signed int max: %d\n", INT_MAX);
  printf("\n");

  printf("################## SHORT INT ##################\n");
  printf("unsigned short int max: %u\n", USHRT_MAX);
  printf("signed short int min: %d\n", SHRT_MIN);
  printf("signed short int max: %d\n", SHRT_MAX);
  printf("\n");

  printf("################## LONG INT ###################\n");
  printf("unsigned long int max: %lu\n", ULONG_MAX);
  printf("signed long int min: %ld\n", LONG_MIN);
  printf("signed long int max: %ld\n", LONG_MAX);
  printf("\n");

  printf("################ LONG LONG INT #################\n");
  printf("unsigned long long int max: %llu\n", ULLONG_MAX);
  printf("signed long long int min: %lld\n", LLONG_MIN);
  printf("signed long long int max: %lld\n", LLONG_MAX);
  printf("\n");

  return 0;
}