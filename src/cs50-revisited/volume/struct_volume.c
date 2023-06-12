// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define HEADER_SIZE 44

struct ioptrs {
	FILE *in;
	FILE *out;
};

struct ioptrs *const openio(char *ifname, char *ofname)
{
	FILE *input = fopen(ifname, "r");
	FILE *output = fopen(ofname, "w");
	if (!output || !input) {
		printf("Couldn't open %s file.\n", !input ? "input" : "output");
		exit(1);
	}

	struct ioptrs *io = malloc(sizeof(struct ioptrs));
	io->in = input;
	io->out = output;
	return io;
}

void cpheader(struct ioptrs *const pio)
{
	uint8_t header[HEADER_SIZE];
	fread(header, HEADER_SIZE, 1, pio->in);
	fwrite(header, HEADER_SIZE, 1, pio->out);
}

void chngvol(struct ioptrs *const pio, int factor)
{
	int16_t buffer;
	while (fread(&buffer, sizeof(int16_t), 1, pio->in)) {
		buffer *= factor;
		fwrite(&buffer, sizeof(int16_t), 1, pio->out);
	}
}

int main(int argc, char *argv[])
{
	struct ioptrs *const pio = openio(argv[1], argv[2]);
	float factor = atof(argv[3]);

	cpheader(pio);
        chngvol(pio, factor);
	
	fclose(pio->in);
	fclose(pio->out);
        free(pio);
}
