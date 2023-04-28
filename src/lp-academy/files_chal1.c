#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define LINE_MAX 4095

int fgetsgetln(FILE *file)
{
    int ln = 1;
    char buffer[LINE_MAX];
    while (fgets(buffer, LINE_MAX, file) != NULL)
        ln++;
    return ln;
}

int fgetcgetln(FILE *file)
{
    int c, ln = 1;
    while ((c = fgetc(file)) != EOF)
        if (c == '\n')
            ln++;
    return ln;
}

void ftoupper(FILE *in, FILE *out)
{
    int c;
    while ((c = fgetc(in)) != EOF)
        islower(c) ? fputc(toupper(c), out) : fputc(c, out);
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

    ftoupper(i, o);

    remove(infname);
    rename("tmp", infname);

    fclose(i);
    fclose(o);
    return 0;
}