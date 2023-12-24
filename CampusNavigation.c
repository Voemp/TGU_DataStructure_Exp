#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// 定义图的最大大小
#define MAX_SIZE 10
#define INF 999999

// 定义景点结构体
typedef struct {
    char name[50];
    char description[200];
} Location;

// 定义图结构体
typedef struct {
    int vertices; // 顶点数
    int edges;    // 边数
    int distance[MAX_SIZE][MAX_SIZE];   // 存储最短距离
    int sequence[MAX_SIZE][MAX_SIZE];   // 存储中转顶点
    Location locations[MAX_SIZE];   // 存储景点信息
} CampusMap;

// 初始化图
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

// 添加景点
void addLocation(CampusMap *map, const char *name, const char *description) {
    if (map->vertices < MAX_SIZE) {
        strcpy(map->locations[map->vertices].name, name);
        strcpy(map->locations[map->vertices].description, description);
        map->vertices++;
    } else {
        printf("Error: Too many locations.\n");
    }
}

// 添加路径
void addPath(CampusMap *map, int start, int end, int weight) {
    if (start >= 0 && start < map->vertices && end >= 0 && end < map->vertices) {
        map->distance[start][end] = weight;
        map->sequence[start][end] = end;
        map->distance[end][start] = weight;  // 添加反向路径
        map->sequence[end][start] = start;  // 更新反向路径的中转顶点
        map->edges++;
    } else {
        printf("Error: Invalid vertices.\n");
    }
}

// Floyd算法计算最短路径
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

// 通过景点名字查找索引
int findLocationIndex(const CampusMap *map, const char *name) {
    for (int i = 0; i < map->vertices; i++) {
        if (strcmp(map->locations[i].name, name) == 0) {
            return i;
        }
    }
    return -1;  // 未找到
}

// 打印景点信息
void printLocationInfo(const CampusMap *map, const char *name) {
    int locationIndex = findLocationIndex(map, name);
    if (locationIndex != -1) {
        printf("\n景点名称: %s\n", map->locations[locationIndex].name);
        printf("景点描述: %s\n", map->locations[locationIndex].description);
    } else {
        printf("\n未找到该景点。\n");
    }
}

// 打印最短路径
void printShortestPath(const CampusMap *map, const char *startName, const char *endName) {
    int startIndex = findLocationIndex(map, startName);
    int endIndex = findLocationIndex(map, endName);

    if (startIndex != -1 && endIndex != -1) {
        if (map->distance[startIndex][endIndex] == INF) {
            printf("\n两点之间不可达。\n");
        } else {
            printf("\n从 %s 到 %s 的最短路径:\n", map->locations[startIndex].name, map->locations[endIndex].name);
            printf("%s", map->locations[startIndex].name);

            int intermediate = startIndex;
            while (intermediate != endIndex) {
                intermediate = map->sequence[intermediate][endIndex];
                printf(" -> %s", map->locations[intermediate].name);
            }

            printf("\n");
        }
    } else {
        printf("\n未找到起始或目标景点。\n");
    }
}


int main() {
    CampusMap campus;
    initCampusMap(&campus);

    // 添加景点
    addLocation(&campus, "教学楼", "主要进行各类课程的教学，设有多个教室和实验室。");
    addLocation(&campus, "食堂", "提供学生和教职工用餐服务，有各种美食选择。");
    addLocation(&campus, "体育馆", "用于举办各类体育活动，包括体育课和比赛。");
    addLocation(&campus, "图书馆", "提供大量图书和学术资源，是学生学习和研究的重要场所。");
    addLocation(&campus, "超市", "为校内师生提供生活用品和食品的购物场所。");
    addLocation(&campus, "打印店", "提供文印服务，包括打印、复印等业务。");
    addLocation(&campus, "理发店", "为师生提供理发和美发服务。");
    addLocation(&campus, "操场", "用于学生进行体育锻炼和各类大型活动的场地。");
    addLocation(&campus, "校门", "学校的主要出入口，通向校外。");
    addLocation(&campus, "实验室", "进行科学研究和实验教学的专用实验场所。");

    // 添加路径
    addPath(&campus, 0, 1, 3);  // 从教学楼到食堂的路径长度为3
    addPath(&campus, 0, 2, 7);  // 从教学楼到体育馆的路径长度为7
    addPath(&campus, 0, 3, 9);  // 从教学楼到图书馆的路径长度为9
    addPath(&campus, 0, 4, 8);  // 从教学楼到超市的路径长度为8
    addPath(&campus, 1, 2, 4);  // 从食堂到体育馆的路径长度为4
    addPath(&campus, 1, 3, 6);  // 从食堂到图书馆的路径长度为6
    addPath(&campus, 1, 4, 7);  // 从食堂到超市的路径长度为7
    addPath(&campus, 1, 5, 5);  // 从食堂到打印店的路径长度为5
    addPath(&campus, 2, 3, 2);  // 从体育馆到图书馆的路径长度为2
    addPath(&campus, 2, 4, 4);  // 从体育馆到超市的路径长度为4
    addPath(&campus, 2, 5, 6);  // 从体育馆到打印店的路径长度为6
    addPath(&campus, 2, 6, 7);  // 从体育馆到理发店的路径长度为7
    addPath(&campus, 3, 4, 5);  // 从图书馆到超市的路径长度为5
    addPath(&campus, 3, 5, 8);  // 从图书馆到打印店的路径长度为8
    addPath(&campus, 3, 6, 4);  // 从图书馆到理发店的路径长度为4
    addPath(&campus, 3, 7, 8);  // 从图书馆到操场的路径长度为8
    addPath(&campus, 4, 5, 3);  // 从超市到打印店的路径长度为3
    addPath(&campus, 4, 6, 3);  // 从超市到理发店的路径长度为3
    addPath(&campus, 4, 7, 5);  // 从超市到操场的路径长度为5
    addPath(&campus, 4, 8, 4);  // 从超市到校门的路径长度为4
    addPath(&campus, 5, 6, 2);  // 从打印店到理发店的路径长度为2
    addPath(&campus, 5, 7, 5);  // 从打印店到操场的路径长度为5
    addPath(&campus, 5, 8, 7);  // 从打印店到校门的路径长度为7
    addPath(&campus, 5, 9, 5);  // 从打印店到实验室的路径长度为5
    addPath(&campus, 6, 7, 4);  // 从理发店到操场的路径长度为4
    addPath(&campus, 6, 8, 2);  // 从理发店到校门的路径长度为2
    addPath(&campus, 6, 9, 6);  // 从理发店到实验室的路径长度为6
    addPath(&campus, 7, 8, 3);  // 从操场到校门的路径长度为3
    addPath(&campus, 7, 9, 4);  // 从操场到实验室的路径长度为4
    addPath(&campus, 8, 9, 5);  // 从校门到实验室的路径长度为5

    // 执行Floyd算法计算最短路径
    floyd(&campus);

    int choice;
    do {
        // 用户输入查询
        system("cls");
        printf("请输入要查询的类型：\n1. 查询地点信息\n2. 查询最短路径\n0. 退出\n");
        scanf("%d", &choice);

        system("cls");
        if (choice == 1) {
            // 显示所有景点的名字
            printf("所有景点的名字：\n");
            for (int i = 0; i < campus.vertices; i++) {
                printf("%s\n", campus.locations[i].name);
            }

            // 查询地点信息
            char locationName[50];
            printf("\n请输入要查询的地点名称：");
            scanf("%s", locationName);
            printLocationInfo(&campus, locationName);
        } else if (choice == 2) {
            // 显示所有景点的名字
            printf("所有景点的名字：\n");
            for (int i = 0; i < campus.vertices; i++) {
                printf("%s\n", campus.locations[i].name);
            }

            // 查询最短路径
            char startName[50], endName[50];
            printf("\n请输入起始地点名称：");
            scanf("%s", startName);
            printf("请输入目标地点名称：");
            scanf("%s", endName);
            printShortestPath(&campus, startName, endName);
        } else if (choice == 0) {
            // 退出
            printf("感谢使用。\n");
            Sleep(500);
            break;
        } else {
            printf("无效的选择。\n");
        }
        system("pause");
    } while (choice != 0);
    return 0;
}
