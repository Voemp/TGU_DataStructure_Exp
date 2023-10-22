#include <stdio.h>
#include <stdlib.h>

#define LIST_INIT_SIZE 5
#define LISTINCREMENT 5
typedef int ElemType;


typedef struct {
    ElemType *elem;
    int length;
    int listsize;
} SqList;

int InitLIst_Sq(SqList *L) {
    //构建一个空的线性表L
    L->elem = (ElemType *) calloc(LIST_INIT_SIZE, sizeof(ElemType));
    if (!L->elem) exit(-2);  //存储分配失败
    L->length = 0;  //空表长度为0
    L->listsize = LIST_INIT_SIZE;   //初始存储容量
    return 1;
}

int ListInsert_Sq(SqList *L, int i, ElemType e) {
    //在顺序线性表L中第i个位置前插入新的元素e
    //i的合法值为1<=i<=ListLength_Sq(L)+1
    if (i < 1 || i > L->length + 1) return 0;   //i值不合法
    if (L->length >= L->listsize) {
        ElemType *newbase = (ElemType *) realloc(L->elem,
                                                 (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) exit(-2);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType *q = &(L->elem[i - 1]); //q为插入位置
    for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = e; //插入e
    ++L->length;
    return 1;
}

int ListDelete_Sq(SqList *L, int i, ElemType *e) {
    //在顺序线性表L中删除第i个元素，并用e返回其值
    if ((i < 1) || (i > L->length)) return 0; //i值不合法
    ElemType *p = &(L->elem[i - 1]);
    *e = *p;
    ElemType *q = L->elem + L->length - 1;
    for (++p; p <= q; ++p) {
        *(p - 1) = *p;
    }
    --L->length;
    return 1;
}


int main() {
    SqList *L = calloc(1, sizeof(SqList));
    InitLIst_Sq(L);
    printf("请输入%d个数\n", LIST_INIT_SIZE);
    for (int i = 0; i < LIST_INIT_SIZE; ++i) {
        scanf("%d", &L->elem[i]);
        L->length++;
    }
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    printf("请输入要插入的位置和数值\n");
    int i, e;
    scanf("%d %d", &i, &e);
    ListInsert_Sq(L, i, e);
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    printf("请输入要删除的位置\n");
    scanf("%d", &i);
    ListDelete_Sq(L, i, &e);
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    system("pause");
}