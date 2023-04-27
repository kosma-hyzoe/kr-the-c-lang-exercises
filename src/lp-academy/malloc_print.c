#include <stdio.h>
#include <stdlib.h>

int main()
{
	int slim;
	char *s = NULL;

	printf("String lenght limit:\n");
	scanf("%i", &slim);

	s = calloc(slim+1, sizeof(char));

	if (!s) {
		printf("Error while allocating memory. Exiting...\n");
		return 1;
	}
	
	int c;
	while ((c = getchar()) != '\n' && c != EOF)
		;

	printf("Your string:\n");
	int nchar = 0;
	while ((c = getchar()) != EOF && nchar < slim) {
		*(s + nchar) = c;
		nchar++;
	} 

	printf("%s\n", s);
	free(s);
	return 0;
}