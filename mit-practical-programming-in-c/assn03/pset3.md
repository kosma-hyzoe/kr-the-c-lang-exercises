# Practical Programming in C: Problem Set 3

## 3.2

* a) static
* b) No.
* c) `gcc dict.c main.c -o dictionary.o`

## 3.3

```c
int factorial(int n)
{
    int i = 1, ret = 1;
    while (++i <= n)
        ret *= i;
    return ret;
}
```

### b

```c
double sample_geometric_rv(double p)
{
    double q = rand_double();
    int n = 1;

    while ((q = rand_double()) >= p)
        n++;

    return n;
}
```

```c

double sample_geometric_rv(double p)
{
    double q = -DBL_MAX;
    int n = 0;

    while ((q = rand_double()) >= p)
        n++;

    return n;
}
```
