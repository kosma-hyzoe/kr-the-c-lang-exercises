#include <stdio.h>

/* Celsius to Fahrenhheit table (300 to 0) */

int main()
{
        printf("Fahr\tCelsius\n");
        for (int fahr = 300; fahr >= 0; fahr -= 20)
                printf("%3d\t%6.2f\n", fahr, (5.0 / 9.0) * (fahr - 32.0));
}
