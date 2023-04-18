#include <stdio.h>

#define IN 1
#define OUT 1

int main()
{
        int c, state;

        state = OUT;
        printf("Your input: ");
        while ((c = getchar()) != EOF) {
                if (c == ' ' || c == '\t' || c == '\n') {
                        if (state == IN) {
                                state = OUT;
                                printf("\n");
                        }
                } else if (state == OUT) {
                        state = IN;
                        putchar(c);
                } else {
                        putchar(c);
                }
        }
        return 0;
}