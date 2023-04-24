#include <stdio.h>

int main(int argc, char* argv[])
{
        char foo = 'i';
        printf("%li\n", sizeof foo);
        printf("%li\n", sizeof 3);
        printf("%li\n", sizeof 30000L);
        printf("%li\n", sizeof 3.5);
}
