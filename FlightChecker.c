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
    char departureTime[MAX_STRING_LENGTH];
    char arrivalTime[MAX_STRING_LENGTH];
    char airline[MAX_STRING_LENGTH];
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
        printf("\n===== 航班信息管理系统 =====\n");
        printf("1. 显示航班信息\n");
        printf("2. 查询航班信息\n");
        printf("3. 排序航班信息\n");
        printf("4. 退出\n");
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
            case 4:
                printf("感谢使用，再见！\n");
                break;
            default:
                printf("无效的选择，请重新输入。\n");
        }
    } while (choice != 4);

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
        // 输出调试信息
        printf("Debug: %s", line);

        // 调整数组大小如果需要
        if (flightArray->size == flightArray->capacity) {
            resizeFlightArray(flightArray);
        }

        // 解析CSV行并存储航班信息
        sscanf(line, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^\n]",
               flightArray->flights[flightArray->size].flightNumber,
               flightArray->flights[flightArray->size].departure,
               flightArray->flights[flightArray->size].destination,
               flightArray->flights[flightArray->size].departureTime,
               flightArray->flights[flightArray->size].arrivalTime,
               flightArray->flights[flightArray->size].airline);

        flightArray->size++;
    }

    fclose(file);
}


void displayFlights(const FlightArray *flightArray) {
    if (flightArray->size > 0) {
        printf("\n===== 显示航班信息 =====\n");
        for (size_t i = 0; i < flightArray->size; i++) {
            printf("航班号：%s  起点站：%s  到达站：%s  起飞时间：%s  到达时间：%s  航空公司：%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].departureTime,
                   flightArray->flights[i].arrivalTime, flightArray->flights[i].airline);
        }
    } else {
        printf("当前没有航班信息。\n");
    }
}

void searchFlights(const FlightArray *flightArray) {
    char keyword[MAX_STRING_LENGTH];
    int found = 0;

    printf("\n===== 查询航班信息 =====\n");
    printf("请输入查询关键词（航班号、起点站、到达站等）：");
    scanf("%s", keyword);

    for (size_t i = 0; i < flightArray->size; i++) {
        if (strstr(flightArray->flights[i].flightNumber, keyword) != NULL ||
            strstr(flightArray->flights[i].departure, keyword) != NULL ||
            strstr(flightArray->flights[i].destination, keyword) != NULL) {
            printf("航班号：%s  起点站：%s  到达站：%s  起飞时间：%s  到达时间：%s  航空公司：%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].departureTime,
                   flightArray->flights[i].arrivalTime, flightArray->flights[i].airline);
            found = 1;
        }
    }

    if (!found) {
        printf("未找到符合条件的航班信息。\n");
    }
}

void sortFlights(FlightArray *flightArray) {
    int choice;

    printf("\n===== 排序航班信息 =====\n");
    printf("1. 按航班号排序\n");
    printf("2. 按起点站排序\n");
    printf("3. 按到达站排序\n");
    printf("4. 按起飞时间排序\n");
    printf("请选择排序方式：");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            // Sort by flight number, using bubble sort
            for (size_t i = 0; i < flightArray->size - 1; i++) {
                for (size_t j = 0; j < flightArray->size - i - 1; j++) {
                    if (strcmp(flightArray->flights[j].flightNumber, flightArray->flights[j + 1].flightNumber) > 0) {
                        // Swap two flight information
                        Flight temp = flightArray->flights[j];
                        flightArray->flights[j] = flightArray->flights[j + 1];
                        flightArray->flights[j + 1] = temp;
                    }
                }
            }
            printf("按航班号排序完成。\n");
            break;
        case 2:
            // Sort by departure, using bubble sort
            for (size_t i = 0; i < flightArray->size - 1; i++) {
                for (size_t j = 0; j < flightArray->size - i - 1; j++) {
                    if (strcmp(flightArray->flights[j].departure, flightArray->flights[j + 1].departure) > 0) {
                        // Swap two flight information
                        Flight temp = flightArray->flights[j];
                        flightArray->flights[j] = flightArray->flights[j + 1];
                        flightArray->flights[j + 1] = temp;
                    }
                }
            }
            printf("按起点站排序完成。\n");
            break;
        case 3:
            // Sort by destination, using bubble sort
            for (size_t i = 0; i < flightArray->size - 1; i++) {
                for (size_t j = 0; j < flightArray->size - i - 1; j++) {
                    if (strcmp(flightArray->flights[j].destination, flightArray->flights[j + 1].destination) > 0) {
                        // Swap two flight information
                        Flight temp = flightArray->flights[j];
                        flightArray->flights[j] = flightArray->flights[j + 1];
                        flightArray->flights[j + 1] = temp;
                    }
                }
            }
            printf("按到达站排序完成。\n");
            break;
        case 4:
            // Sort by departure time, using bubble sort
            for (size_t i = 0; i < flightArray->size - 1; i++) {
                for (size_t j = 0; j < flightArray->size - i - 1; j++) {
                    if (strcmp(flightArray->flights[j].departureTime, flightArray->flights[j + 1].departureTime) > 0) {
                        // Swap two flight information
                        Flight temp = flightArray->flights[j];
                        flightArray->flights[j] = flightArray->flights[j + 1];
                        flightArray->flights[j + 1] = temp;
                    }
                }
            }
            printf("按起飞时间排序完成。\n");
            break;
        default:
            printf("无效的排序方式。\n");
    }
}

void resizeFlightArray(FlightArray *flightArray) {
    // Double the capacity of the array
    flightArray->capacity *= 2;

    // Reallocate memory for the array
    flightArray->flights = realloc(flightArray->flights, flightArray->capacity * sizeof(Flight));

    if (!flightArray->flights) {
        fprintf(stderr, "Memory reallocation error\n");
        exit(EXIT_FAILURE);
    }
}