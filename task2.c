#include <stdio.h>
#include <stdlib.h>

#define REG_NUM_LENGTH 10
#define MODEL_LENGTH 20
#define VIOLATION_TYPES 5
#define MAX_CARS 100

typedef enum
{
    SPEEDING,
    PARKING,
    RED_LIGHT,
    DRUNK,
    NO_SEAT_BELT
} ViolationType;

typedef struct
{
    ViolationType type;
    int fine_amount;
} Violation;

typedef struct
{
    char reg_num[REG_NUM_LENGTH];
    char* model;
    Violation violations[VIOLATION_TYPES];
} CAr;

CAr cars[MAX_CARS];
int num_cars = 0;

void add_car() {
    if (num_cars < MAX_CARS) {
        CAr car;
        printf("Enter registration number: ");
        scanf("%s", car.reg_num);
        car.model = (char*)malloc(MODEL_LENGTH * sizeof(char));
        printf("Enter model: ");
        scanf("%s", car.model);

        for (int i = 0; i < VIOLATION_TYPES; i++) {
            car.violations[i].type = (ViolationType)i;
            printf("Enter fine amount for violation %d: ", i+1);
            scanf("%d", &car.violations[i].fine_amount);
        }

        cars[num_cars++] = car;
    } else {
        printf("Maximum number of cars reached.\n");
    }
}

void delete_car(int index) {
    if (index >= 0 && index < num_cars) {
        free(cars[index].model);
        for (int i = index; i < num_cars - 1; i++) {
            cars[i] = cars[i + 1];
        }
        num_cars--;
    } else {
        printf("Invalid index.\n");
    }
}

void print_cars() {
    for (int i = 0; i < num_cars; i++)
    {
        printf("CAr %d:\n", i+1);
        printf("Registration number: %s\n", cars[i].reg_num);
        printf("Model: %s\n", cars[i].model);
        for (int j = 0; j < VIOLATION_TYPES; j++) {
            printf("Violation %d: Type %d, Fine amount %d\n", j+1, cars[i].violations[j].type + 1, cars[i].violations[j].fine_amount);
        }
        printf("\n");
    }
}

void from_file(const char* fileName) {
    FILE *file = fopen(fileName, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    num_cars = 0;

    while (fscanf(file, "%s", cars[num_cars].reg_num) == 1)
    {
        cars[num_cars].model = (char*)malloc(MODEL_LENGTH * sizeof(char));
        fscanf(file, "%s", cars[num_cars].model);

        for (int j = 0; j < VIOLATION_TYPES; j++)
        {
            fscanf(file, "%d %d", &cars[num_cars].violations[j].type, &cars[num_cars].violations[j].fine_amount);
        }

        num_cars++;
    }

    fclose(file);
}

void to_file(const char* file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < num_cars; i++) {
        fprintf(file, "%s %s\n", cars[i].reg_num, cars[i].model);
        for (int j = 0; j < VIOLATION_TYPES; j++) {
            fprintf(file, "%d %d\n", cars[i].violations[j].type, cars[i].violations[j].fine_amount);
        }
    }

    fclose(file);
}

void main_action()
{
    int violationCount[VIOLATION_TYPES] = {0};

    for (int i = 0; i < num_cars; i++)
    {
        for (int j = 0; j < VIOLATION_TYPES; j++)
        {
            if (cars[i].violations[j].fine_amount > 0)
            {
                violationCount[cars[i].violations[j].type]++;
            }
        }
    }
    int index[VIOLATION_TYPES];

    for (int i = 0; i < VIOLATION_TYPES; i++)
    {
        index[i] = i;
    }

    // Сортируем типы нарушений по убыванию количества
    for (int i = 0; i < VIOLATION_TYPES - 1; i++)
    {
        for (int j = i + 1; j < VIOLATION_TYPES; j++)
        {
            if (violationCount[i] < violationCount[j])
            {
                int temp = violationCount[i];
                violationCount[i] = violationCount[j];
                violationCount[j] = temp;

                int tempIndex = index[i];
                index[i] = index[j];
                index[j] = tempIndex;
            }
        }
    }

    printf("Violation types sorted by number of cars involved:\n");
    for (int i = 0; i < VIOLATION_TYPES; i++)
    {
        printf("Violation Type %d: %d cars\n", index[i] + 1, violationCount[i]);
    }
}

void task2()
{
    from_file("D:\\Task.txt");

    int choice;
    do {
        printf("1. Add a car\n");
        printf("2. Delete a car\n");
        printf("3. Print all cars\n");
        printf("4. Write statistic\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        int index;

        switch(choice) {
            case 1:
                add_car();
                break;
            case 2:
                printf("Enter index of car to delete: ");
                scanf("%d", &index);
                delete_car(index - 1);
                break;
            case 3:
                print_cars();
                break;
            case 5:
                to_file("D:\\Task.txt");
                break;
            case 4:
                main_action();
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);
}
