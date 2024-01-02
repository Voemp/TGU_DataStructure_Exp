#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ��������ַ�������
#define MAX_STRING_LENGTH 50

// ����洢������Ϣ�Ľṹ��
typedef struct {
    char flightNumber[MAX_STRING_LENGTH];
    char departure[MAX_STRING_LENGTH];
    char destination[MAX_STRING_LENGTH];
    char departureTime[MAX_STRING_LENGTH];
    char arrivalTime[MAX_STRING_LENGTH];
    char airline[MAX_STRING_LENGTH];
} Flight;

// ���嶯̬�������洢������Ϣ
typedef struct {
    Flight *flights;
    size_t size;
    size_t capacity;
} FlightArray;

// ��������
void readCSV(const char *filename, FlightArray *flightArray);
void displayFlights(const FlightArray *flightArray);
void searchFlights(const FlightArray *flightArray);
void sortFlights(FlightArray *flightArray);
void resizeFlightArray(FlightArray *flightArray);

int main() {
    // �滻Ϊʵ�ʵ�CSV�ļ���
    const char *filename = "flight_info.csv";

    // ������̬�������洢������Ϣ
    FlightArray flightArray;
    flightArray.size = 0;
    flightArray.capacity = 10;  // ��ʼ����
    flightArray.flights = malloc(flightArray.capacity * sizeof(Flight));

    if (!flightArray.flights) {
        fprintf(stderr, "�ڴ�������\n");
        exit(EXIT_FAILURE);
    }

    // ��CSV�ļ��ж�ȡ������Ϣ
    readCSV(filename, &flightArray);

    int choice;
    do {
        printf("\n===== ������Ϣ����ϵͳ =====\n");
        printf("1. ��ʾ������Ϣ\n");
        printf("2. ��ѯ������Ϣ\n");
        printf("3. ���򺽰���Ϣ\n");
        printf("4. �˳�\n");
        printf("��ѡ�������");
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
                printf("��лʹ�ã��ټ���\n");
                break;
            default:
                printf("��Ч��ѡ�����������롣\n");
        }
    } while (choice != 4);

    // �ͷŷ�����ڴ�
    free(flightArray.flights);

    return 0;
}

void readCSV(const char *filename, FlightArray *flightArray) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        fprintf(stderr, "���ļ�����: %s\n", filename);
        exit(EXIT_FAILURE);
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        // ���������Ϣ
        printf("Debug: %s", line);

        // ���������С�����Ҫ
        if (flightArray->size == flightArray->capacity) {
            resizeFlightArray(flightArray);
        }

        // ����CSV�в��洢������Ϣ
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
        printf("\n===== ��ʾ������Ϣ =====\n");
        for (size_t i = 0; i < flightArray->size; i++) {
            printf("����ţ�%s  ���վ��%s  ����վ��%s  ���ʱ�䣺%s  ����ʱ�䣺%s  ���չ�˾��%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].departureTime,
                   flightArray->flights[i].arrivalTime, flightArray->flights[i].airline);
        }
    } else {
        printf("��ǰû�к�����Ϣ��\n");
    }
}

void searchFlights(const FlightArray *flightArray) {
    char keyword[MAX_STRING_LENGTH];
    int found = 0;

    printf("\n===== ��ѯ������Ϣ =====\n");
    printf("�������ѯ�ؼ��ʣ�����š����վ������վ�ȣ���");
    scanf("%s", keyword);

    for (size_t i = 0; i < flightArray->size; i++) {
        if (strstr(flightArray->flights[i].flightNumber, keyword) != NULL ||
            strstr(flightArray->flights[i].departure, keyword) != NULL ||
            strstr(flightArray->flights[i].destination, keyword) != NULL) {
            printf("����ţ�%s  ���վ��%s  ����վ��%s  ���ʱ�䣺%s  ����ʱ�䣺%s  ���չ�˾��%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].departureTime,
                   flightArray->flights[i].arrivalTime, flightArray->flights[i].airline);
            found = 1;
        }
    }

    if (!found) {
        printf("δ�ҵ����������ĺ�����Ϣ��\n");
    }
}

void sortFlights(FlightArray *flightArray) {
    int choice;

    printf("\n===== ���򺽰���Ϣ =====\n");
    printf("1. �����������\n");
    printf("2. �����վ����\n");
    printf("3. ������վ����\n");
    printf("4. �����ʱ������\n");
    printf("��ѡ������ʽ��");
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
            printf("�������������ɡ�\n");
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
            printf("�����վ������ɡ�\n");
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
            printf("������վ������ɡ�\n");
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
            printf("�����ʱ��������ɡ�\n");
            break;
        default:
            printf("��Ч������ʽ��\n");
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