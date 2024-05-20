#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

struct point
{
    unsigned int x:32;
} number;

union code
{
    int p;
    struct
    {
        unsigned a0:8;
        unsigned a1:8;
        unsigned a2:8;
        unsigned a3:8;
    } byte;
};

int is_number_1(const char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (!isdigit(str[i]))
        {
            printf("Введённый элемент не является числом. Повторный ввод: ");
            return 1;
        }
    }
    return 0;
}

void task1(void)
{
    printf("Введите число: \n");
    char test[10];
    do scanf("%s", &test); while(is_number_1(test));
    union code c;
    c.p = atoi(test);
    printf("Старший байт числа равен (в десятичной системе): %d", c.byte.a3);
}