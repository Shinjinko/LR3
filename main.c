#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"

int main(int argc, char** argv)
{
    if (argc > 2)
    {
        printf("Wrong arguments!");
        exit(0);
    }

    int num = atoi(argv[1]);

    while(1)
    {
        switch (num)
        {
            case 1:
                task1();
                break;
            case 2:
                task2();
                break;
            case 0:
                printf("Bye!");
                exit(0);
            default:
                printf("Error 404");
                scanf("%i", &num);
                break;
        }
        printf("\nSelect a number of the task or write '0' to exit: ");
        scanf("%d", &num);
    }
}