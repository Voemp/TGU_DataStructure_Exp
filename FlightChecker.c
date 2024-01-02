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
    char flightDate[MAX_STRING_LENGTH];
    char departureTime[MAX_STRING_LENGTH];
    char arrivalTime[MAX_STRING_LENGTH];
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

void quickSort(FlightArray *flightArray, int left, int right, int keyIndex);

int partition(FlightArray *flightArray, int left, int right, int keyIndex);

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
        system("cls");
        printf("\n===== ������Ϣ����ϵͳ =====\n");
        printf("1. ��ʾ������Ϣ\n");
        printf("2. ��ѯ������Ϣ\n");
        printf("3. ���򺽰���Ϣ\n");
        printf("0. �˳�\n");
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
            case 0:
                printf("��лʹ�ã��ټ���\n");
                break;
            default:
                printf("��Ч��ѡ�����������롣\n");
        }
    } while (choice != 0);

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
        // ���������С�����Ҫ
        if (flightArray->size == flightArray->capacity) {
            resizeFlightArray(flightArray);
        }

        // ����CSV�в��洢������Ϣ
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
        printf("\n===== ��ʾ������Ϣ =====\n");
        printf("�����\t���վ\t����վ\t��������\t���ʱ��\t����ʱ��\n");
        for (size_t i = 1; i < flightArray->size; i++) {
            printf("%s\t%s\t%s\t%s\t%s\t\t%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].flightDate,
                   flightArray->flights[i].departureTime, flightArray->flights[i].arrivalTime);
        }
    } else {
        printf("��ǰû�к�����Ϣ��\n");
    }
    system("pause");
}

void searchFlights(const FlightArray *flightArray) {
    int choice;
    system("cls");
    printf("\n===== ��ѯ������Ϣ =====\n");
    printf("ѡ���ѯ��ʽ��\n");
    printf("1. �����\n");
    printf("2. ���վ\n");
    printf("3. ����վ\n");
    printf("4. ��������\n");
    printf("������ѡ��1-4����");
    scanf("%d", &choice);

    char keyword[MAX_STRING_LENGTH];
    printf("\n�������ѯ�ؼ��ʣ�");
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
                printf("��Ч��ѡ��\n");
                return;
        }

        if (match) {
            if (!found) {
                printf("\n��ѯ�����\n");
                printf("�����\t���վ\t����վ\t��������\t���ʱ��\t����ʱ��\n");
                found = 1;
            }

            printf("%s\t%s\t%s\t%s\t%s\t\t%s\n",
                   flightArray->flights[i].flightNumber, flightArray->flights[i].departure,
                   flightArray->flights[i].destination, flightArray->flights[i].flightDate,
                   flightArray->flights[i].departureTime, flightArray->flights[i].arrivalTime);
        }
    }

    if (!found) {
        printf("δ�ҵ����������ĺ�����Ϣ��\n");
    }
    system("pause");
}


void sortFlights(FlightArray *flightArray) {
    int choice;
    system("cls");
    printf("\n===== ���򺽰���Ϣ =====\n");
    printf("1. �����������\n");
    printf("2. �����վ����\n");
    printf("3. ������վ����\n");
    printf("4. ����������Լ����ʱ������\n");
    printf("\n��ѡ������ʽ��");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            quickSort(flightArray, 0, flightArray->size - 1, 1);  // �����������
            printf("�������������ɡ�\n");
            break;
        case 2:
            quickSort(flightArray, 0, flightArray->size - 1, 2);  // �����վ����
            printf("�����վ������ɡ�\n");
            break;
        case 3:
            quickSort(flightArray, 0, flightArray->size - 1, 3);  // ������վ����
            printf("������վ������ɡ�\n");
            break;
        case 4:
            quickSort(flightArray, 0, flightArray->size - 1, 4);  // ��������ں�ʱ������
            printf("����������Լ����ʱ��������ɡ�\n");
            break;
        default:
            printf("��Ч������ʽ��\n");
    }
}

void quickSort(FlightArray *flightArray, int left, int right, int keyIndex) {
    if (left < right) {
        int pivotIndex = partition(flightArray, left, right, keyIndex);

        // �ݹ�ض������������������
        quickSort(flightArray, left, pivotIndex - 1, keyIndex);
        quickSort(flightArray, pivotIndex + 1, right, keyIndex);
    }
}

int partition(FlightArray *flightArray, int left, int right, int keyIndex) {
    // ʹ�����Ҳ��Ԫ����Ϊ��׼ֵ
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
            return -1;  // ��Ч�� keyIndex
    }

    int i = left - 1;

    for (int j = left; j < right; j++) {
        // ����ѡ��Ĺؼ��ʱȽϺ���
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
                return -1;  // ��Ч�� keyIndex
        }

        if (strcmp(compareString, pivot) <= 0) {
            i++;
            // ����������Ϣ
            Flight temp = flightArray->flights[i];
            flightArray->flights[i] = flightArray->flights[j];
            flightArray->flights[j] = temp;
        }
    }

    // ����׼ֵ�����Ҳࣩ�� i+1 ����Ԫ�ؽ���
    Flight temp = flightArray->flights[i + 1];
    flightArray->flights[i + 1] = flightArray->flights[right];
    flightArray->flights[right] = temp;

    return i + 1;
}

void resizeFlightArray(FlightArray *flightArray) {
    // ������������һ��
    flightArray->capacity *= 2;

    // Ϊ�������·����ڴ�
    flightArray->flights = realloc(flightArray->flights, flightArray->capacity * sizeof(Flight));

    if (!flightArray->flights) {
        fprintf(stderr, "Memory reallocation error\n");
        exit(EXIT_FAILURE);
    }
}