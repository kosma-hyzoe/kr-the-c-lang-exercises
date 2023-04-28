# C Programming For Beginners

## Misc

* abort(), atexit() - define what happens on 1 and 0 exits
* qsort() - sort array
* system() - use system commands

## Datatypes

### Bool

```c
/* bool */

/* c89 */
_Bool boolVar = 1;
/* c99 */
#include <stdbool.h>
bool voolVar = true;
```

### short, long unsigned

* char < short int < int < lonv int
* float < double < long double

```c
/* long constants? */
long double US_deficit_2017 = 1.325e+7L;
long double bazBar;
/* non-negative only. "extended accuracy"? */
unsigned int barbaz;
/* just for extra clarity */
signed int baz;
```

### enums

```c
/* these store ints under the hood */
enum primaryColor {red, yellow, blue};

/* u can explicitly assign the int values */
/* here up=0, down=1, left=10, right=11 */
enum direction {up, down, left = 10, right};


/* declare two primaryColor vars */
enum primaryColor blueColor, redColor;
redColor = red;
blueColor = blue;
```

## Bitwise

* & - bitwise AND, copies the bit if both operands have it
* | - bitwise OR
* ^ - XOR
* ~ - flip bits
* `>>/<<`  - move bits

## Strings

* strlen()
* strcpy(dest, src), strncpy(dest, src, len)
* strcat(dest, src)

* strchr()/strrchr() - search string for a specified character
* strstr()/strrstr() - returns pointer tho where substring is found in string
* isxdigit()
* iscntrl() - control chars
* isprint() - printing chars including spaces
* isblank() - tab and space
* isgraph() - printing char except space
* isapunct() - (isspace() && isalumn() -> false)
* `for(i=0; text[i] = (char)toupper(text[i]) != '\0'; ++i);`

```c
/* get the first token */
char * token = strtok(str, delimeter);
while (token != NULL) {
    printf("%s\n", token);
    token = strtok(NULL, s);
}

```

### String conversion

`ato`'s don't detect errors.

* atof() - double
* atoi() - int
* atol() - long
* atoll() - long long

* strtod(char *nptr, char **endptr, int base) - string to double
* `strtod(text, NULL, 10)`
* strtol() - string to long
* strtof() - string to float
* strtold() - long double

## Pointers

* can be assigned to arrays names, variable addresses and other pointers
* you can determine distance between array elements by pointer substr.

* do not `int *pt; *pt = 5;` - it will place "5" ANYWHERE in memory.
* creating a long pointer does not allocate memory for the long, just the
  pointer
* `const int *p;` - "pointer to a constant int"
* `int *const p;` - "constant pointer to an int"
* NOTE: `(*p)++` != `*p++`

* `void* vp = &foo;` - a pointer that can point to anything
* needs to be cast to get value `printf("%d\n", *(int *)vptr)`
* `*(int *)vptr` - dereference a void pointer cast to an int pointer
* `vp = &values[0]` == `vp = values`
  `ar[i]` == `*(ar+i)`

## Structures

* better to use struct pointers as fuction arguments, probably const

```c
struct date
{
 int month;
 int day;
 int year;
}

struct date today = {4, 27, 2023};
struct date y2023 = {NULL, NULL, 2023};
struct date april = {4};
struct date yadot = {.year=2023, .day=27, .month=4};

/* immediately create a struct instance */
struct date
{
 int month;
 int day;
 int year;
} today;

/* anonymous structs */
struct
{
 int foo;
 int bar;
} tempstruct;

/* c11+: compound literals - assign multiple values on one line */
today = (struct date) {9, 26, 2015};
int arr;
arr = (int[]) {3, 2, 1};


struct date *todayp = &today;
(*todayp).month = 3;
todayp->month = 4;
```
## Files

* w, a, r - write, append, read
* + - rw, create if doesnt exist


* `rename()`, `remove()` - returns 0/1
* getc() - fgetc() with macros
* rewind() - place position at the beginning
* fgets():
	* read until `'\n'` or nchars-1
	* retains the `'\n'`
	* returns NULL if EOF, else char \*
