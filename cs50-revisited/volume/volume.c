// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
	// Check command-line arguments
	if (argc != 4) {
		printf("Usage: ./volume input.wav output.wav factor\n");
		return 1;
	}

	// Open files and determine scaling factor
	FILE *input = fopen(argv[1], "r");
	if (!input) {
		printf("Could not open file.\n");
		return 1;
	}

	FILE *output = fopen(argv[2], "w");
	if (!output) {
		printf("Could not open file.\n");
		return 1;
	}

	float factor = atof(argv[3]);

	uint8_t *header = malloc(HEADER_SIZE * sizeof(uint8_t));
	if (!header) {
		printf("Memory allocation error - exiting...\n");
		return 1;
	}
	fread(header, HEADER_SIZE, 1, input);
	fwrite(header, HEADER_SIZE, 1, output);
	free(header);

	// determine file size
	fseek(input, 0, SEEK_END);
	long input_size = ftell(input);
	// set the file position to after the header
	fseek(input, HEADER_SIZE, SEEK_SET);

	int16_t *buffer = malloc(input_size - HEADER_SIZE * sizeof(uint8_t));
	if (buffer == NULL) {
		printf("Memory allocation error - exiting...\n");
		return 1;
	}

	fread(buffer, input_size, 1, input);
	int nbytes = (input_size - HEADER_SIZE) / sizeof(int16_t);
	for (int i = 0; i < nbytes; i++) {
		uint16_t sample = buffer[i];
		sample *= factor;
		fwrite(&sample, sizeof(int16_t), 1, output);
	}
	free(buffer);

	fclose(input);
	fclose(output);
}
