#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct date
	{
		int month;
		int day;
		int year;
	};

	struct date today = {4, 27, 2023};
	struct date y2023 = {NULL, NULL, 2023};
	printf("%i\n", y2023.day);
}
