//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//
//#define REG_NUM_LENGTH 10
//#define MODEL_LENGTH 20
//#define VIOLATION_NAME 10
//#define VIOLATION_TYPES 3
//#define MAX_CARS 100
//
//typedef enum
//{
//    Violation1,
//    Violation2,
//    Violation3
//} ViolationType;
//
//typedef struct
//{
//    ViolationType type;
//    char* name;
//    int fine_amount;
//} Violation;
//
//typedef struct
//{
//    char reg_num[REG_NUM_LENGTH];
//    char* model;
//    Violation violations[VIOLATION_TYPES];
//} CAr;
//
//int check_name (char *car, char* another_car, const int* num)
//{
//    int check = 0;
//    for(int i = 0; i < *num; i++)
//    {
//        check += memcmp(car, another_car, sizeof(another_car));
//    }
//    return !check;
//}
//
//
//void add_car(int *num_cars, CAr* cars)
//{
//    if (*num_cars < MAX_CARS)
//    {
//        CAr car;
//        car.model = (char*)malloc(MODEL_LENGTH * sizeof(char));
//        printf("Enter model: ");
//        scanf("%s", car.model);
//        printf("Enter registration number: ");
//        scanf("%s", car.reg_num);
//        int i = 0;
//        while (check_name(car.reg_num, cars[i].reg_num, num_cars))
//        {
//            printf("Not a unique registration number! Try again: ");
//            scanf("%s", car.reg_num);
//            i++;
//        }
//
//        printf("You can choose only 3 types of violation!\n");
//        for (int i = 0; i < VIOLATION_TYPES; i++)
//        {
//            car.violations[i].type = (ViolationType)i;
//            car.violations[i].name = (char*)malloc(VIOLATION_NAME * sizeof(char));
//            printf("Enter violation name on one word: ");
//            scanf("%s", car.violations[i].name);
//            printf("Enter fine amount for violation %d: ", i+1);
//            scanf("%d", &car.violations[i].fine_amount);
//        }
//        cars[*num_cars] = car;
//        *num_cars += 1;
//    }
//    else
//    {
//        printf("Maximum number of cars reached.\n");
//    }
//}
//
//void delete_car(int index, int *num_cars, CAr *cars) {
//    if (index >= 0 && index < *num_cars) {
//        free(cars[index].model);
//        free(cars[index].violations[index].name);
//        for (int i = index; i < *num_cars - 1; i++) {
//            cars[i] = cars[i + 1];
//        }
//        *num_cars -= 1;
//    }
//    else
//    {
//        printf("Invalid index.\n");
//    }
//}
//
//void print_cars(int *num_cars, CAr* cars) {
//    for (int i = 0; i < *num_cars; i++)
//    {
//        printf("CAr %d:\n", i+1);
//        printf("Registration number: %s\n", cars[i].reg_num);
//        printf("Model: %s\n", cars[i].model);
//        for (int j = 0; j < VIOLATION_TYPES; j++) {
//            printf("Violation %d: Type %s, Fine amount %d\n", j+1, cars[i].violations[j].name, cars[i].violations[j].fine_amount);
//        }
//        printf("\n");
//    }
//}
//
//void from_file(const char* fileName, int *num_cars, CAr *cars)
//{
//    FILE *file = fopen(fileName, "r");
//    if (file == NULL) {
//        printf("Error opening file.\n");
//        return;
//    }
//
//    *num_cars = 0;
//
//    while (fscanf(file, "%s", cars[*num_cars].reg_num) == 1)
//    {
//        cars[*num_cars].model = (char*)malloc(MODEL_LENGTH * sizeof(char));
//        fscanf(file, "%s", cars[*num_cars].model);
//
//        for (int j = 0; j < VIOLATION_TYPES; j++)
//        {
//            cars[*num_cars].violations[j].name = (char*)malloc(VIOLATION_NAME * sizeof(char));
//            fscanf(file, "%d%s%d", &cars[*num_cars].violations[j].type, cars[*num_cars].violations[j].name, &cars[*num_cars].violations[j].fine_amount);
//        }
//
//        *num_cars += 1;
//    }
//
//    fclose(file);
//}
//
//void to_file(const char* file_name, int *num_cars, CAr *cars) {
//    FILE *file = fopen(file_name, "w");
//    if (file == NULL) {
//        printf("Error opening file.\n");
//        return;
//    }
//
//    for (int i = 0; i < *num_cars; i++) {
//        fprintf(file, "%s %s\n", cars[i].reg_num, cars[i].model);
//        for (int j = 0; j < VIOLATION_TYPES; j++) {
//            fprintf(file, "%d %s %d\n", cars[*num_cars].violations[j].type, cars[i].violations[j].name, cars[i].violations[j].fine_amount);
//        }
//    }
//
//    fclose(file);
//}
//
//void main_action(int *num_cars, CAr *cars)
//{
//    int violationCount[VIOLATION_TYPES] = {0};
//
//    for (int i = 0; i < *num_cars; i++)
//    {
//        for (int j = 0; j < VIOLATION_TYPES; j++)
//        {
//            if (cars[i].violations[j].fine_amount > 0)
//            {
//                violationCount[cars[i].violations[j].type]++;
//            }
//        }
//    }
//    int index[VIOLATION_TYPES];
//
//    for (int i = 0; i < VIOLATION_TYPES; i++)
//    {
//        index[i] = i;
//    }
//
//    for (int i = 0; i < VIOLATION_TYPES - 1; i++)
//    {
//        for (int j = i + 1; j < VIOLATION_TYPES; j++)
//        {
//            if (violationCount[i] < violationCount[j])
//            {
//                int temp = violationCount[i];
//                violationCount[i] = violationCount[j];
//                violationCount[j] = temp;
//
//                int tempIndex = index[i];
//                index[i] = index[j];
//                index[j] = tempIndex;
//            }
//        }
//    }
//
//    printf("Violation types sorted by number of cars involved:\n");
//    for (int i = 0; i < VIOLATION_TYPES; i++)
//    {
//        if (violationCount[i] == 0) continue;
//        printf("Violation Type %s: %d cars\n", cars[0].violations[index[i]].name, violationCount[i]);
//    }
//}
//
//void task2()
//{
//    CAr *cars = malloc(MAX_CARS * sizeof(CAr));
//    int num_cars = 0;
//    from_file("D:\\Task.txt", &num_cars, cars);
//
//    int choice;
//    do {
//        printf("1. Add a car\n2. Delete a car\n3. Print all cars\n4. Write statistic\n5. Exit\nEnter your choice: ");
//        scanf("%d", &choice);
//        int index;
//        switch(choice)
//        {
//            case 1:
//                add_car(&num_cars, cars);
//                break;
//            case 2:
//                printf("Enter index of car to delete: ");
//                scanf("%d", &index);
//                delete_car(index - 1, &num_cars, cars);
//                break;
//            case 3:
//                print_cars(&num_cars, cars);
//                break;
//            case 5:
//                to_file("D:\\Task.txt", &num_cars, cars);
//                break;
//            case 4:
//                main_action(&num_cars, cars);
//                break;
//            default:
//                printf("Invalid choice. Please try again.\n");
//        }
//    } while (choice != 5);
//    free(cars);
//}