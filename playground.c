#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct foo {
	struct foo *next;
	int foo;
	int bar;
};

int main()
{
	struct foo *f = NULL;
	free(f->next);
}
