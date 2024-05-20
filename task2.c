#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define VIOLATIONS_LENGTH 15
#define REG_NUM_LENGTH 20
#define MODEL_LENGTH 25

typedef struct
{
    int fine;
    int type;
} violation;

typedef struct
{
    char reg_num[REG_NUM_LENGTH];
    char* model;
    violation* violations;
} CAr;

int is_file_empty(const char* file_name)
{
    FILE *file = fopen(file_name, "r");
    int c = fgetc(file);
    fclose(file);

    if (c == EOF) return 1;
    else return 0;
}

int is_number(const char *str)
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

void instruction()
{
    FILE* file = fopen("instructions.txt", "r");

    char buffer[100];
    while (fgets(buffer, 100, file) != NULL)
    {
        printf("%s ", buffer);
    }

    fclose(file);
}

int check_reg_num(char *car, CAr *another_cars, const int* num)
{
    for(int i = 0; i < *num; i++)
    {
        if(strcmp(car, another_cars[i].reg_num) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int Vytautas_choice (int mode, int num_car, char* reg_num, int* fine)
{
    int choise;
    switch (mode)
    {
        case 1:
            printf("Регистрационный номер автомобиля под номером %d не уникален! "
                   "Закрыть программу или переписать? 1/0\n", num_car);
            scanf("%d", &choise);
            if (choise) return 1;
            else
            {
                printf("Введите новый регистрационный номер: ");
                scanf("%s", reg_num);
                return 0;
            }
        case 2:
            printf("Отрицательное значение штрафа у автомобиля под номером %d!\n"
                   "Закрыть программу или переписать? 1/0\n", num_car);
            scanf("%d", &choise);
            if (choise) return 1;
            else
            {
                printf("Введите новый размер штрафа: ");
                scanf("%d", fine);
                return 0;
            }
        default: break;
    }
    return 5;
}

void from_file (char* file_name, int *num_cars, CAr **cars, char **violations_1, int* num_violations)
{
    FILE *file = fopen(file_name, "r");
    if (file == NULL)
    {
        printf("Ошибка открытия файла!\n");
        return;
    }

    if(is_file_empty(file_name))
    {
        printf("Файл пуст. Пожалуйста, прочтите инструкцию перед его заполнением и перезапустите программу. Инструкция:\n\n");
        instruction();
        exit(0);
    }

    *num_cars = 0;

    fscanf(file, "%d", num_violations);
    (*cars) = (CAr*)malloc((*num_cars + 1) * sizeof(CAr));

    for(int i = 0; i < *num_violations; i++)
    {
        violations_1[i] = (char*)malloc(VIOLATIONS_LENGTH * sizeof(char));
        fscanf(file, "%s", violations_1[i]);
    }

    while (fscanf(file, "%s", (*cars)[*num_cars].reg_num) != EOF)
    {
        while(check_reg_num((*cars)[*num_cars].reg_num, (*cars), num_cars))
        {
            if(Vytautas_choice (1, *num_cars, (*cars)[*num_cars].reg_num, 0)) exit(0);
        }
        (*cars)[*num_cars].model = (char*)malloc(MODEL_LENGTH * sizeof(char));
        fseek(file, 1, SEEK_CUR);
        fgets((*cars)[*num_cars].model, MODEL_LENGTH, file);

        (*cars)[*num_cars].violations = (violation*)malloc(*num_violations * sizeof(violation));
        for (int j = 0; j < *num_violations; j++)
        {
            fscanf(file, "%d %d", &(*cars)[*num_cars].violations[j].type, &(*cars)[*num_cars].violations[j].fine);
            while ((*cars)[*num_cars].violations[j].fine < 0)
            {
                if(Vytautas_choice (2, *num_cars, (*cars)[*num_cars].reg_num, &(*cars)[*num_cars].violations[j].fine)) exit(0);
            }
        }

        *num_cars += 1;
        (*cars) = (CAr*)realloc((*cars), (*num_cars + 1) * sizeof(CAr));
    }
    fclose(file);
}

void to_file(const char* file_name, const int *num_cars, CAr *cars, char** violations, const int* max_violations) {
    FILE *file = fopen(file_name, "w");

    rewind(file);
    fprintf(file, "%d\n", *max_violations);
    for(int i = 0; i < *max_violations; i++)
    {
        fprintf(file, "%s\n", violations[i]);
    }

    for (int i = 0; i < *num_cars; i++)
    {
        fprintf(file, "%s\n%s", cars[i].reg_num, cars[i].model);
        for (int j = 0; j < *max_violations; j++)
        {
            fprintf(file, "%d %d\n", cars[i].violations[j].type, cars[i].violations[j].fine);
        }
    }

    fclose(file);
}

void print_cars(const int *num_cars, CAr* cars, char** violations, const int* max_violations)
{
    for (int i = 0; i < *num_cars; i++)
    {
        printf("CAr %d:\n", i+1);
        printf("Регистрационный номер: %s\n", cars[i].reg_num);
        printf("Модель: %s\n", cars[i].model);
        for (int j = 0; j < *max_violations; j++)
        {
            printf("Нарушение %d: Кодовое имя - %s, Штраф: %d\n", j+1, violations[cars[i].violations[j].type], cars[i].violations[j].fine);
        }
        printf("\n");
    }
}

void add_car(int *num_cars, CAr** cars, char** violations, const int* max_violations)
{
    CAr car;
    car.model = (char*)malloc(MODEL_LENGTH * sizeof(char));
    printf("Введите регистрационный номер: ");
    scanf("%s", car.reg_num);
    while(check_reg_num(car.reg_num, (*cars), num_cars))
    {
        printf("Регистрационный номер не уникален. Введите другое значение: \n");
        scanf("%s", car.reg_num);
    }
    fflush(stdin);
    printf("Введите модель: ");
    getchar();
    fgets(car.model, MODEL_LENGTH, stdin);

    car.violations = (violation*) malloc(*max_violations * sizeof(violation));
    for (int i = 0; i < *max_violations; i++)
    {
        car.violations[i].type = i;
        printf("Введите штраф за %s: ", violations[i]);
        scanf("%d", &car.violations[i].fine);
        while (car.violations[i].fine < 0)
        {
            printf("Отрицательное значение штрафа! Введите новое значение: ");
            scanf("%d", &car.violations[i].fine);
        }
    }
    (*cars)[*num_cars] = car;
    *num_cars += 1;
    (*cars) = (CAr*)realloc((*cars), (*num_cars + 1) * sizeof(CAr));
}

void delete_car(int index, int *num_cars, CAr **cars, const int* num_violations)
{
    if (index >= 0 && index < *num_cars)
    {
        free((*cars)[index].model);
        for (int i = index; i < *num_cars - 1; i++)
        {
            (*cars)[i] = (*cars)[i + 1];
        }
        *num_cars -= 1;
        printf("Удалён автомобиль с индексом: %d\n", index + 1);
        (*cars) = (CAr*)realloc((*cars), (*num_cars * sizeof(CAr)) + *num_violations);
    }
    else
    {
        printf("Неверный индекс.\n");
    }
}

void sort_violation (const int *num_cars, CAr* cars, const int* max_violations, int *violationCount, int index_v[*max_violations])
{

    for (int i = 0; i < *num_cars; i++)
    {
        for (int j = 0; j < *max_violations; j++)
        {
            if (cars[i].violations[j].fine > 0)
            {
                violationCount[cars[i].violations[j].type]++;
            }
        }
    }

    for (int i = 0; i < *max_violations; i++)
    {
        index_v[i] = i;
    }

    for (int i = 0; i < *max_violations - 1; i++)
    {
        for (int j = i + 1; j < *max_violations; j++)
        {
            if (violationCount[i] < violationCount[j])
            {
                int temp = violationCount[i];
                violationCount[i] = violationCount[j];
                violationCount[j] = temp;

                int tempIndex = index_v[i];
                index_v[i] = index_v[j];
                index_v[j] = tempIndex;
            }
        }
    }
}

void print_sort(int* violation_count, const int* max_violations, char** violations, const int* index)
{

    printf("Нарушения отсортированы от большего количества вовлечённых к меньшим:\n");
    for (int i = 0; i < *max_violations; i++)
    {
        if (violation_count[i] == 0) continue;
        printf("Кодовое имя нарушения %s: вовлечено %d машин\n", violations[index[i]], violation_count[i]);
    }
}

void exceeding_fine (int *num_cars, CAr* cars, int* max_violations)
{
    char max_fine_c[10];
    printf("Введите максимальный суммарный штраф: ");
    do scanf("%s", max_fine_c); while(is_number(max_fine_c));
    int max_fine = atoi(max_fine_c);

    int is_fine = 0;
    int amount_fine;
    int *fines = (int*)malloc(is_fine * sizeof(int));
    for(int i = 0; i < *num_cars; i++)
    {
        amount_fine = 0;
        for (int y = 0; y < 5; y++)
            amount_fine += cars[i].violations[y].fine;
        if (amount_fine > max_fine)
        {
            is_fine++;
            fines = (int*)realloc(fines, is_fine * sizeof(int));
            fines[is_fine - 1] = i;
        }
    }
    if(is_fine == 0) printf("У существующих в списке автомобилей нет превышения штрафа.\n");
    else
        while (is_fine != 0)
        {
            delete_car(fines[is_fine - 1], num_cars, &cars, max_violations);
            is_fine--;
        }
    free(fines);
}


void menu()
{
    printf("1. Прочитать инструкцию заполнения файла к заданию;\n"
           "2. Вывести меню программы;\n"
           "3. Вывести все автомобили;\n"
           "4. Добавить автомобиль;\n"
           "5. Удалить автомобиль;\n"
           "6. Сортировка нарушений;\n"
           "7. Удаление превышений;\n"
           "0. Выйти.\n");
}

void task2(char *file_name)
{
    CAr *cars = NULL;
    int num_violations = 0;
    FILE *file = fopen(file_name, "r");
    fscanf(file, "%d", &num_violations);
    fclose(file);
    int num_cars = 0;
    char **violations = (char**) malloc(num_violations * sizeof(char*));
    from_file(file_name, &num_cars, &cars, violations, &num_violations);
    int *violationCount = calloc(num_violations, sizeof(int));
    int index_v[num_violations];

    menu();

    char choise[10];
    char index[10];

    do {
        printf("\nВведите предпочитаемый пункт из меню или '2', чтобы вывести его: ");
        do scanf("%s", choise); while(is_number(choise));

        switch (atoi(choise))
        {
            case 2:
                menu();
                break;
            case 1:
                instruction();
                break;
            case 3:
                print_cars(&num_cars, cars, violations, &num_violations);
                break;
            case 0:
                to_file(file_name, &num_cars, cars, violations, &num_violations);
                break;
            case 4:
                add_car(&num_cars, &cars, violations, &num_violations);
                break;
            case 6:
                sort_violation(&num_cars, cars, &num_violations, violationCount, index_v);
                print_sort(violationCount, &num_violations, violations, index_v);
                break;
            case 5:
                printf("Введите индекс нужного автомобиля: ");
                do scanf("%s", &index); while(is_number(index));
                delete_car(atoi(index) - 1, &num_cars, &cars, &num_violations);
                break;
            case 7:
                exceeding_fine(&num_cars, cars, &num_violations);
                break;
            default:
                printf("Попробуйте ещё раз.");
        }
    }

    while(atoi(choise) != 0);

    free(violationCount);
    free(violations);
    free(cars);
}