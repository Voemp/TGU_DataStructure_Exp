#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 定义最大字符串长度
#define MAX_STRING_LENGTH 50

// 定义存储航班信息的结构体
typedef struct {
    char flightNumber[MAX_STRING_LENGTH];
    char departure[MAX_STRING_LENGTH];
    char destination[MAX_STRING_LENGTH];
    char flightDate[MAX_STRING_LENGTH];
    char departureTime[MAX_STRING_LENGTH];
    char arrivalTime[MAX_STRING_LENGTH];
} Flight;

// 定义动态数组来存储航班信息
typedef struct {
    Flight *flights;
    size_t size;
    size_t capacity;
} FlightArray;

// 函数声明
void readCSV(const char *filename, FlightArray *flightArray);

void displayFlights(const FlightArray *flightArray);

void searchFlights(const FlightArray *flightArray);

void sortFlights(FlightArray *flightArray);

void resizeFlightArray(FlightArray *flightArray);

void quickSort(FlightArray *flightArray, int left, int right, int keyIndex);

int partition(FlightArray *flightArray, int left, int right, int keyIndex);

int main() {
    // 替换为实际的CSV文件名
    const char *filename = "flight_info.csv";

    // 创建动态数组来存储航班信息
    FlightArray flightArray;
    flightArray.size = 0;
    flightArray.capacity = 10;  // 初始容量
    flightArray.flights = malloc(flightArray.capacity * sizeof(Flight));

    if (!flightArray.flights) {
        fprintf(stderr, "内存分配错误\n");
        exit(EXIT_FAILURE);
    }

    // 从CSV文件中读取航班信息
    readCSV(filename, &flightArray);

    int choice;
    do {
        system("cls");
        printf("\n===== 航班信息管理系统 =====\n");
        printf("1. 显示航班信息\n");
        printf("2. 查询航班信息\n");
        printf("3. 排序航班信息\n");
        printf("0. 退出\n");
        printf("请选择操作：");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayFlights(&flightArray);
                break;
            case 2:
                searchFlights(&flightArray);
                break;
            case 3:
                sortFlights(&flightArray);
                break;
            case 0:
                printf("感谢使用，再见！\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    } while (choice != 0);

    // 释放分配的内存
    free(flightArray.flights);

    return 0;
}

void readCSV(const char *filename, FlightArray *flightArray) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "打开文件错误: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // 调整数组大小如果需要
        if (flightArray->size == flightArray->capacity) {
            resizeFlightArray(flightArray);
        }

        // 解析CSV行并存储航班信息
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
               flightArray->flights[flightArray->size].flightNumber,
               flightArray->flights[flightArray->size].departure,
               flightArray->flights[flightArray->size].destination,
               flightArray->flights[flightArray->size].flightDate,
               flightArray->flights[flightArray->size].departureTime,
               flightArray->flights[flightArray->size].arrivalTime);

        flightArray->size++;
    }

    fclose(file);
}


void displayFlights(const FlightArray *flightArray) {
    if (flightArray->size > 0) {
        system("cls");
        printf("\n===== 显示航班信息 =====\n");
        printf("航班号\t起点站\t到达站\t航班日期\t起飞时间\t到达时间\n");
        for (size_t i = 1; i < flightArray->size; i++) {
            printf("%s\t%s\t%s\t%s\t%s\t\t%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].flightDate,
                   flightArray->flights[i].departureTime, flightArray->flights[i].arrivalTime);
        }
    } else {
        printf("当前没有航班信息。\n");
    }
    system("pause");
}

void searchFlights(const FlightArray *flightArray) {
    int choice;
    system("cls");
    printf("\n===== 查询航班信息 =====\n");
    printf("选择查询方式：\n");
    printf("1. 航班号\n");
    printf("2. 起点站\n");
    printf("3. 到达站\n");
    printf("4. 航班日期\n");
    printf("请输入选择（1-4）：");
    scanf("%d", &choice);

    char keyword[MAX_STRING_LENGTH];
    printf("\n请输入查询关键词：");
    scanf("%s", keyword);

    int found = 0;

    for (size_t i = 1; i < flightArray->size; i++) {
        int match = 0;

        switch (choice) {
            case 1:
                match = (strstr(flightArray->flights[i].flightNumber, keyword) != NULL);
                break;
            case 2:
                match = (strstr(flightArray->flights[i].departure, keyword) != NULL);
                break;
            case 3:
                match = (strstr(flightArray->flights[i].destination, keyword) != NULL);
                break;
            case 4:
                match = (strstr(flightArray->flights[i].flightDate, keyword) != NULL);
                break;
            default:
                printf("无效的选择。\n");
                return;
        }

        if (match) {
            if (!found) {
                printf("\n查询结果：\n");
                printf("航班号\t起点站\t到达站\t航班日期\t起飞时间\t到达时间\n");
                found = 1;
            }

            printf("%s\t%s\t%s\t%s\t%s\t\t%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].flightDate,
                   flightArray->flights[i].departureTime, flightArray->flights[i].arrivalTime);
        }
    }

    if (!found) {
        printf("未找到符合条件的航班信息。\n");
    }
    system("pause");
}


void sortFlights(FlightArray *flightArray) {
    int choice;
    system("cls");
    printf("\n===== 排序航班信息 =====\n");
    printf("1. 按航班号排序\n");
    printf("2. 按起点站排序\n");
    printf("3. 按到达站排序\n");
    printf("4. 按起飞日期以及起飞时间排序\n");
    printf("\n请选择排序方式：");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            quickSort(flightArray, 0, flightArray->size - 1, 1);  // 按航班号排序
            printf("按航班号排序完成。\n");
            break;
        case 2:
            quickSort(flightArray, 0, flightArray->size - 1, 2);  // 按起点站排序
            printf("按起点站排序完成。\n");
            break;
        case 3:
            quickSort(flightArray, 0, flightArray->size - 1, 3);  // 按到达站排序
            printf("按到达站排序完成。\n");
            break;
        case 4:
            quickSort(flightArray, 0, flightArray->size - 1, 4);  // 按起飞日期和时间排序
            printf("按起飞日期以及起飞时间排序完成。\n");
            break;
        default:
            printf("无效的排序方式。\n");
    }
}

void quickSort(FlightArray *flightArray, int left, int right, int keyIndex) {
    if (left < right) {
        int pivotIndex = partition(flightArray, left, right, keyIndex);

        // 递归地对两个子数组进行排序
        quickSort(flightArray, left, pivotIndex - 1, keyIndex);
        quickSort(flightArray, pivotIndex + 1, right, keyIndex);
    }
}

int partition(FlightArray *flightArray, int left, int right, int keyIndex) {
    // 使用最右侧的元素作为基准值
    char pivot[MAX_STRING_LENGTH];
    switch (keyIndex) {
        case 1:
            strcpy(pivot, flightArray->flights[right].flightNumber);
            break;
        case 2:
            strcpy(pivot, flightArray->flights[right].departure);
            break;
        case 3:
            strcpy(pivot, flightArray->flights[right].destination);
            break;
        case 4:
            sprintf(pivot, "%s %02d:%s", flightArray->flights[right].flightDate,
                    atoi(flightArray->flights[right].departureTime), flightArray->flights[right].departureTime + 3);
            break;
        default:
            return -1;  // 无效的 keyIndex
    }

    int i = left - 1;

    for (int j = left; j < right; j++) {
        // 根据选择的关键词比较航班
        char compareString[MAX_STRING_LENGTH];
        switch (keyIndex) {
            case 1:
                strcpy(compareString, flightArray->flights[j].flightNumber);
                break;
            case 2:
                strcpy(compareString, flightArray->flights[j].departure);
                break;
            case 3:
                strcpy(compareString, flightArray->flights[j].destination);
                break;
            case 4:
                sprintf(compareString, "%s %02d:%s", flightArray->flights[j].flightDate,
                        atoi(flightArray->flights[j].departureTime), flightArray->flights[j].departureTime + 3);
                break;
            default:
                return -1;  // 无效的 keyIndex
        }

        if (strcmp(compareString, pivot) <= 0) {
            i++;
            // 交换航班信息
            Flight temp = flightArray->flights[i];
            flightArray->flights[i] = flightArray->flights[j];
            flightArray->flights[j] = temp;
        }
    }

    // 将基准值（最右侧）与 i+1 处的元素交换
    Flight temp = flightArray->flights[i + 1];
    flightArray->flights[i + 1] = flightArray->flights[right];
    flightArray->flights[right] = temp;

    return i + 1;
}

void resizeFlightArray(FlightArray *flightArray) {
    // 数组容量增加一倍
    flightArray->capacity *= 2;

    // 为数组重新分配内存
    flightArray->flights = realloc(flightArray->flights, flightArray->capacity * sizeof(Flight));

    if (!flightArray->flights) {
        fprintf(stderr, "Memory reallocation error\n");
        exit(EXIT_FAILURE);
    }
}