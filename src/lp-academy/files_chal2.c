#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void revf(FILE *in, FILE *out)
{
    fseek(in, 0, SEEK_END);
    long pos = ftell(in);

    while (pos > 0) {
        fseek(in, --pos, SEEK_SET);
        fputc(fgetc(in), out);
    }
}

int main(int argc, char *argv[])
{
    char *infname;
    if (argc == 2) {
        infname = argv[1];
    } else {
        infname = malloc(FILENAME_MAX);
        printf("File name:\n");
        fgets(infname, FILENAME_MAX, stdin);
        infname[strcspn(infname, "\n")] = '\0';
    }

    FILE *i = fopen(infname, "r");
    FILE *o = fopen("tmp", "w+");

    if (!i || !o) {
        printf("Cant open '%s'\n", !i ? infname : "out.txt");
        return 1;
    }

    revf(i, o);
    remove(infname);
    rename("tmp", infname);

    fclose(i);
    fclose(o);
    return 0;
}