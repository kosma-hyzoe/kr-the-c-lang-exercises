#include <stdio.h>
#include <string.h>

#define IN 1
#define OUT 0
#define MAXWORDLEN 15

int main(int argc, char *argv[])
{

	int wordlens[MAXWORDLEN];
	for (int i = 0; i < MAXWORDLEN; i++)
		wordlens[i] = 0;

	int state = OUT;

	int wordlen, ovflow = 0;
	int c;

	for (int i = 0; i < strlen(argv[1]); i++) {
        c = argv[1][i];
		if (c == ' ' || c == '\n' || c == '\t') {
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
			if (state == OUT){
				state = IN;
            } else if (state == IN && i < strlen(argv[1])) 

			wordlen++;
		}

	}

	for (int i = 0; i < MAXWORDLEN; i++)
		printf("%d: %d\n", i+1, wordlens[i]);
	if (ovflow) 
		printf("Words over max word lenght: %d\n", ovflow);
	return 0;
}
