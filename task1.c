#include <stdio.h>

struct point
{
    unsigned int x:32;
} number;

union code
{
    struct point p;
    struct
    {
        unsigned a0:8;
        unsigned a1:8;
        unsigned a2:8;
        unsigned a3:8;
    } byte;
};

void task1(void)
{
    printf("Write a number: \n");
    scanf("%i", &number);
    union code c;
    c.p = number;
    printf("The highest byte of the number (in 10th): %d", c.byte.a3);
}