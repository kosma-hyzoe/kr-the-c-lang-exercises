/* 76. (Challenge) Understanding char arrays */
#include <string.h>

/* concatenate strs without strcat() */
char* nocatcat(char out[], char *s1, char *s2)
{
        strncpy(out, s1, sizeof s1);
        strncpy(out+strlen(s1), s2, sizeof s2);
        return out;
}

int nostrlenstrlenB(char *s)
{
        int i = 0;
        while (s[i])
                i++;
        return i;
}

int nostrlenstrlen(char *s)
{
        int len = 0;
        while (*s) {
                len++;
                *s++;
        }

        return len;
}
