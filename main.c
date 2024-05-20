#include <stdio.h>
#include <stdlib.h>
#include "tasks.h"
#include <windows.h>

int main(int argc, char** argv)
{
    SetConsoleOutputCP(CP_UTF8);
    if (argc > 3)
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
                task2(argv[2]);
                break;
            case 0:
                printf("Bye!");
                exit(0);
            default:
                printf("Error 404");
                scanf("%i", &num);
                break;
        }
        printf("\nВыберите номер задачи или напишите \"0\" для выхода: ");
        scanf("%d", &num);
    }
}