#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buchalka/chararrchal.h"

int main(int argc, char *argv[])
{
        int arr[] = {3, 2, 1};
        for (int i = 0; i < sizeof(arr)/sizeof(arr[0]); i++) 
                printf("%i\n", arr[i]);
        return 0;
}
