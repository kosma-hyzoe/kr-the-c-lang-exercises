/* 97. (Challenge) Counting characters in a String */
#include <stdio.h>

#define FOOBAR 2000;

void sqrbyptr(int *num)
{
        *num = *num * *num;
        return;
}

int ptrstrlen(const char *strptr)
{
        int strlen = 0;
        for (; *strptr != '\0'; strptr++, strlen++)
                ;
        return strlen;
}

int ptrstrlenv2(const char *strptr)
{
        const char *endstrptr = strptr;
        for (; *endstrptr != '\0'; endstrptr++)
                ;
        return endstrptr - strptr;
}

int main()
{
        int i = 3;
        sqrbyptr(&i);
        printf("%i\n", i);
        return 0;
}