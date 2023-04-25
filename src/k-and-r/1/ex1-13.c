#include <stdio.h>

#define IN 1
#define OUT 0
#define MAXWORDLEN 15

int main()
{

	int wordlens[MAXWORDLEN];
	for (int i = 0; i < MAXWORDLEN; i++)
		wordlens[i] = 0;

	printf("Your input: \n");
	int state = OUT;

	int wordlen, ovflow = 0;
	int c;

	while (c = getchar()) {
		if (c == ' ' || c == '\n' || c == '\t' || c == EOF) {
			if (state == IN && wordlen > 15) {
				state = OUT;
				ovflow++;
				wordlen = 0;

			}
			else if (state == IN) {
				state = OUT;
				wordlens[wordlen-1] += 1;
				wordlen = 0;
			}

			if (c == EOF) 
				break;
		}

		else {
			if (state == OUT)
				state = IN;
			wordlen++;
		}

	}

	for (int i = 0; i < MAXWORDLEN; i++)
		printf("%d: %d\n", i+1, wordlens[i]);
	if (ovflow) 
		printf("Words over max word lenght: %d\n", ovflow);
	return 0;
}
