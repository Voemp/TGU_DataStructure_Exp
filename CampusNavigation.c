#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// ����ͼ������С
#define MAX_SIZE 10
#define INF 999999

// ���徰��ṹ��
typedef struct {
    char name[50];
    char description[200];
} Location;

// ����ͼ�ṹ��
typedef struct {
    int vertices; // ������
    int edges;    // ����
    int distance[MAX_SIZE][MAX_SIZE];   // �洢��̾���
    int sequence[MAX_SIZE][MAX_SIZE];   // �洢��ת����
    Location locations[MAX_SIZE];   // �洢������Ϣ
} CampusMap;

// ��ʼ��ͼ
void initCampusMap(CampusMap *map) {
    map->vertices = 0;
    map->edges = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        for (int j = 0; j < MAX_SIZE; j++) {
            if (i == j) {
                map->distance[i][j] = 0;
            } else {
                map->distance[i][j] = INF;
            }
            map->sequence[i][j] = -1;
        }
    }
}

// ��Ӿ���
void addLocation(CampusMap *map, const char *name, const char *description) {
    if (map->vertices < MAX_SIZE) {
        strcpy(map->locations[map->vertices].name, name);
        strcpy(map->locations[map->vertices].description, description);
        map->vertices++;
    } else {
        printf("Error: Too many locations.\n");
    }
}

// ���·��
void addPath(CampusMap *map, int start, int end, int weight) {
    if (start >= 0 && start < map->vertices && end >= 0 && end < map->vertices) {
        map->distance[start][end] = weight;
        map->sequence[start][end] = end;
        map->distance[end][start] = weight;  // ��ӷ���·��
        map->sequence[end][start] = start;  // ���·���·������ת����
        map->edges++;
    } else {
        printf("Error: Invalid vertices.\n");
    }
}

// Floyd�㷨�������·��
void floyd(CampusMap *map) {
    for (int k = 0; k < map->vertices; k++) {
        for (int i = 0; i < map->vertices; i++) {
            for (int j = 0; j < map->vertices; j++) {
                if (map->distance[i][j] > map->distance[i][k] + map->distance[k][j]) {
                    map->distance[i][j] = map->distance[i][k] + map->distance[k][j];
                    map->sequence[i][j] = map->sequence[i][k];
                }
            }
        }
    }
}

// ͨ���������ֲ�������
int findLocationIndex(const CampusMap *map, const char *name) {
    for (int i = 0; i < map->vertices; i++) {
        if (strcmp(map->locations[i].name, name) == 0) {
            return i;
        }
    }
    return -1;  // δ�ҵ�
}

// ��ӡ������Ϣ
void printLocationInfo(const CampusMap *map, const char *name) {
    int locationIndex = findLocationIndex(map, name);
    if (locationIndex != -1) {
        printf("\n��������: %s\n", map->locations[locationIndex].name);
        printf("��������: %s\n", map->locations[locationIndex].description);
    } else {
        printf("\nδ�ҵ��þ��㡣\n");
    }
}

// ��ӡ���·��
void printShortestPath(const CampusMap *map, const char *startName, const char *endName) {
    int startIndex = findLocationIndex(map, startName);
    int endIndex = findLocationIndex(map, endName);

    if (startIndex != -1 && endIndex != -1) {
        if (map->distance[startIndex][endIndex] == INF) {
            printf("\n����֮�䲻�ɴ\n");
        } else {
            printf("\n�� %s �� %s �����·��:\n", map->locations[startIndex].name, map->locations[endIndex].name);
            printf("%s", map->locations[startIndex].name);

            int intermediate = startIndex;
            while (intermediate != endIndex) {
                intermediate = map->sequence[intermediate][endIndex];
                printf(" -> %s", map->locations[intermediate].name);
            }

            printf("\n");
        }
    } else {
        printf("\nδ�ҵ���ʼ��Ŀ�꾰�㡣\n");
    }
}


int main() {
    CampusMap campus;
    initCampusMap(&campus);

    // ��Ӿ���
    addLocation(&campus, "��ѧ¥", "��Ҫ���и���γ̵Ľ�ѧ�����ж�����Һ�ʵ���ҡ�");
    addLocation(&campus, "ʳ��", "�ṩѧ���ͽ�ְ���òͷ����и�����ʳѡ��");
    addLocation(&campus, "������", "���ھٰ��������������������κͱ�����");
    addLocation(&campus, "ͼ���", "�ṩ����ͼ���ѧ����Դ����ѧ��ѧϰ���о�����Ҫ������");
    addLocation(&campus, "����", "ΪУ��ʦ���ṩ������Ʒ��ʳƷ�Ĺ��ﳡ����");
    addLocation(&campus, "��ӡ��", "�ṩ��ӡ���񣬰�����ӡ����ӡ��ҵ��");
    addLocation(&campus, "����", "Ϊʦ���ṩ������������");
    addLocation(&campus, "�ٳ�", "����ѧ���������������͸�����ͻ�ĳ��ء�");
    addLocation(&campus, "У��", "ѧУ����Ҫ����ڣ�ͨ��У�⡣");
    addLocation(&campus, "ʵ����", "���п�ѧ�о���ʵ���ѧ��ר��ʵ�鳡����");

    // ���·��
    addPath(&campus, 0, 1, 3);  // �ӽ�ѧ¥��ʳ�õ�·������Ϊ3
    addPath(&campus, 0, 2, 7);  // �ӽ�ѧ¥�������ݵ�·������Ϊ7
    addPath(&campus, 0, 3, 9);  // �ӽ�ѧ¥��ͼ��ݵ�·������Ϊ9
    addPath(&campus, 0, 4, 8);  // �ӽ�ѧ¥�����е�·������Ϊ8
    addPath(&campus, 1, 2, 4);  // ��ʳ�õ������ݵ�·������Ϊ4
    addPath(&campus, 1, 3, 6);  // ��ʳ�õ�ͼ��ݵ�·������Ϊ6
    addPath(&campus, 1, 4, 7);  // ��ʳ�õ����е�·������Ϊ7
    addPath(&campus, 1, 5, 5);  // ��ʳ�õ���ӡ���·������Ϊ5
    addPath(&campus, 2, 3, 2);  // �������ݵ�ͼ��ݵ�·������Ϊ2
    addPath(&campus, 2, 4, 4);  // �������ݵ����е�·������Ϊ4
    addPath(&campus, 2, 5, 6);  // �������ݵ���ӡ���·������Ϊ6
    addPath(&campus, 2, 6, 7);  // �������ݵ������·������Ϊ7
    addPath(&campus, 3, 4, 5);  // ��ͼ��ݵ����е�·������Ϊ5
    addPath(&campus, 3, 5, 8);  // ��ͼ��ݵ���ӡ���·������Ϊ8
    addPath(&campus, 3, 6, 4);  // ��ͼ��ݵ������·������Ϊ4
    addPath(&campus, 3, 7, 8);  // ��ͼ��ݵ��ٳ���·������Ϊ8
    addPath(&campus, 4, 5, 3);  // �ӳ��е���ӡ���·������Ϊ3
    addPath(&campus, 4, 6, 3);  // �ӳ��е������·������Ϊ3
    addPath(&campus, 4, 7, 5);  // �ӳ��е��ٳ���·������Ϊ5
    addPath(&campus, 4, 8, 4);  // �ӳ��е�У�ŵ�·������Ϊ4
    addPath(&campus, 5, 6, 2);  // �Ӵ�ӡ�굽�����·������Ϊ2
    addPath(&campus, 5, 7, 5);  // �Ӵ�ӡ�굽�ٳ���·������Ϊ5
    addPath(&campus, 5, 8, 7);  // �Ӵ�ӡ�굽У�ŵ�·������Ϊ7
    addPath(&campus, 5, 9, 5);  // �Ӵ�ӡ�굽ʵ���ҵ�·������Ϊ5
    addPath(&campus, 6, 7, 4);  // �����굽�ٳ���·������Ϊ4
    addPath(&campus, 6, 8, 2);  // �����굽У�ŵ�·������Ϊ2
    addPath(&campus, 6, 9, 6);  // �����굽ʵ���ҵ�·������Ϊ6
    addPath(&campus, 7, 8, 3);  // �Ӳٳ���У�ŵ�·������Ϊ3
    addPath(&campus, 7, 9, 4);  // �Ӳٳ���ʵ���ҵ�·������Ϊ4
    addPath(&campus, 8, 9, 5);  // ��У�ŵ�ʵ���ҵ�·������Ϊ5

    // ִ��Floyd�㷨�������·��
    floyd(&campus);

    int choice;
    do {
        // �û������ѯ
        system("cls");
        printf("������Ҫ��ѯ�����ͣ�\n1. ��ѯ�ص���Ϣ\n2. ��ѯ���·��\n0. �˳�\n");
        scanf("%d", &choice);

        system("cls");
        if (choice == 1) {
            // ��ʾ���о��������
            printf("���о�������֣�\n");
            for (int i = 0; i < campus.vertices; i++) {
                printf("%s\n", campus.locations[i].name);
            }

            // ��ѯ�ص���Ϣ
            char locationName[50];
            printf("\n������Ҫ��ѯ�ĵص����ƣ�");
            scanf("%s", locationName);
            printLocationInfo(&campus, locationName);
        } else if (choice == 2) {
            // ��ʾ���о��������
            printf("���о�������֣�\n");
            for (int i = 0; i < campus.vertices; i++) {
                printf("%s\n", campus.locations[i].name);
            }

            // ��ѯ���·��
            char startName[50], endName[50];
            printf("\n��������ʼ�ص����ƣ�");
            scanf("%s", startName);
            printf("������Ŀ��ص����ƣ�");
            scanf("%s", endName);
            printShortestPath(&campus, startName, endName);
        } else if (choice == 0) {
            // �˳�
            printf("��лʹ�á�\n");
            Sleep(500);
            break;
        } else {
            printf("��Ч��ѡ��\n");
        }
        system("pause");
    } while (choice != 0);
    return 0;
}
