# C Programming For Beginners

## Misc

* \r -
* \a - alert

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

* char < short int < int < long int
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
