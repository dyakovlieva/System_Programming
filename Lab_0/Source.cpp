#include <stdio.h>
#include <limits.h>
#include <float.h>

#define UNSIGNED_MIN 0

int main(void)
{
    printf("Type           Bytes         Min             Max       \n");
    printf("unsigned char     %-5d %-21d %-21d\n", sizeof(unsigned char), UNSIGNED_MIN, UCHAR_MAX);
    printf("signed char       %-5d %-21d %-21d\n", sizeof(char), CHAR_MIN, CHAR_MAX);
    printf("unsigned short    %-5d %-21d %-21u\n", sizeof(unsigned short), UNSIGNED_MIN, USHRT_MAX);
    printf("short             %-5d %-21d %-21d\n", sizeof(short), SHRT_MIN, SHRT_MAX);
    printf("unsigned int      %-5d %-21d %-21u \n", sizeof(unsigned int), UNSIGNED_MIN, UINT_MAX);
    printf("int               %-5d %-21d %-21d\n", sizeof(int), INT_MIN, INT_MAX);
    printf("unsigned long     %-5d %-21d %-21u\n", sizeof(unsigned long), UNSIGNED_MIN, ULONG_MAX);
    printf("long              %-5d %-21ld %-21ld\n", sizeof(long), LONG_MIN, LONG_MAX);
    printf("uns. long long    %-5d %-21d %-21llu\n", sizeof(unsigned long long), UNSIGNED_MIN, ULLONG_MAX);
    printf("long long         %-5d %-21lld %-21lld\n", sizeof(long long), LLONG_MIN, LLONG_MAX);

    printf("    Type      Bytes          Min              Max        \n");
    printf("    float      %-5d   %-21G %-21G\n", sizeof(float), FLT_MIN, FLT_MAX);
    printf("    double     %-5d   %-21G %-21G\n", sizeof(double), DBL_MIN, DBL_MAX);
    printf(" long double   %-5d   %-21G %-21G\n", sizeof(long double), LDBL_MIN, LDBL_MAX);

    return 0;
}