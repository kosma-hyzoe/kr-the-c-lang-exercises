/* 78. (Challenge) Utilizing common string functions */
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

char *revstr(char in[])
{
        char rev[strlen(in) + 1];
        rev[strlen(in)] = '\0';
        int outindex = 0;
        for (int i = strlen(in) - 1; i >= 0; i--) {
                rev[outindex] = in[i];
                outindex++;
        }

        char *out = rev;
        return out;
}

void bblsrt(int arr[])
{
        bool sorted = false;
        while (!sorted) {
                sorted = true;
                for (int i = 0; i < sizeof(arr) / sizeof(int) - 1; i++) {
                        if (arr[i] < arr[i + 1]) {
                                int tmp = arr[i];
                                arr[i] = arr[i + 1];
                                arr[i + 1] = tmp;
                                sorted = false;
                        }
                }
        }
}


int main()
{

}