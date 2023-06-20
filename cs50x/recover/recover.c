#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define WRITING_JPG 1
#define LOOKING_FOR_JPG 0

#define BLOCK_SIZE 512
#define FNAME_SIZE 8
#define SIGNATURE_SIZE 4

#define FIRST_SIG_BYTE 0xff
#define SECOND_SIG_BYTE 0xd8
#define THIRD_SIG_BYTE 0xff
#define FIRST_4_BITS_MASK 0b1111
#define FOURTH_SIG_BYTE_MASK 0b1110

typedef uint8_t BYTE;

int is_jpeg_header(BYTE *buffer);

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: ./recover IMAGE\n");
        exit(1);
    }

    FILE *raw = fopen(argv[1], "r");
    if (raw == NULL) {
        exit(1);
    }

    FILE *f;
    int fc = 0;
    char *fname = malloc(sizeof(char) * FNAME_SIZE);

    BYTE *buffer = malloc(sizeof(BYTE) * BLOCK_SIZE);

    int state = LOOKING_FOR_JPG;
    while (fread(buffer, 1, BLOCK_SIZE, raw) == BLOCK_SIZE) {
        if (is_jpeg_header(buffer)) {
            if (state == WRITING_JPG) {
                fclose(f);
                f = NULL;
            } else {
                state = WRITING_JPG;
            }

            sprintf(fname, "%03d.jpg", ++fc);

            f = fopen(fname, "w");
            if (f == NULL) {
                exit(1);
            }
        }
        if (state == WRITING_JPG) {
           fwrite(buffer, 1, BLOCK_SIZE, f);
        }
    }

    free(buffer);
    fclose(f);


}

int is_jpeg_header(BYTE *buffer)
{
    return  *(buffer + 0) == FIRST_SIG_BYTE &&
            *(buffer + 1) == SECOND_SIG_BYTE &&
            *(buffer + 2) == THIRD_SIG_BYTE &&
            (*(buffer + 3) & FIRST_4_BITS_MASK) == FOURTH_SIG_BYTE_MASK;
}

