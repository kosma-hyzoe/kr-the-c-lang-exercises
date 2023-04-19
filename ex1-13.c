#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXWORDLEN 15

int main()
{
	
	int wordlens[MAXWORDLEN];
	for (int i = 0; i < MAXWORDLEN; i++)
		wordlens[0] = 0;

	printf("Your input: \n");
	int state = OUT;

	int wordlen = 0;
	int nmaxwords, c;
	while ((c = getchar()) != EOF) {
		if (c == ' ' || c == '\t' || c == '\t') {
			if (state == IN && wordlen > 15) {
				state = OUT;
				nmaxwords++;
				wordlen = 0;

			}
			else if (state == IN) {
				state = OUT;
				wordlens[wordlen-1] += 1;
				wordlen = 0;
			}
		} else {
			if (state == OUT)
				state = IN;
			wordlen++;
		}
	}
	for (int i = 0; i < MAXWORDLEN; i++)
		printf("%d: %d\n", i+1, wordlens[i]);
	
	return 0;
}
