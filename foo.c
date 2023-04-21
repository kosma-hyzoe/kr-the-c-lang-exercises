#include <stdio.h>

int main()
{
    enum foobar {foo, bar};
    enum foobar myFoo = foo;

    printf("%d\n", myFoo);
    
    return 0;
}
