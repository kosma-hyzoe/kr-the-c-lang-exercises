#include <stdio.h>

struct employee {
	char *name;
	int hireDate;
	float salary;
};

int main()
{
	struct employee foobianBarsky = {"Foobian Barsky", 2023, 3000.45};
	struct employee jackBarsky;

	printf("Name:\n");
	scanf("%s", jackBarsky.name);
	printf("Hire date (year):\n");
	scanf("%i", &jackBarsky.hireDate);
	printf("Salary:\n");
	scanf("%f", &jackBarsky.salary);

	printf("Name: %s\tHire date: %i\tSalary: %f\n", jackBarsky.name,
	       jackBarsky.hireDate, jackBarsky.salary);
}