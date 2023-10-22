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
    //����һ���յ����Ա�L
    L->elem = (ElemType *) calloc(LIST_INIT_SIZE, sizeof(ElemType));
    if (!L->elem) exit(-2);  //�洢����ʧ��
    L->length = 0;  //�ձ���Ϊ0
    L->listsize = LIST_INIT_SIZE;   //��ʼ�洢����
    return 1;
}

int ListInsert_Sq(SqList *L, int i, ElemType e) {
    //��˳�����Ա�L�е�i��λ��ǰ�����µ�Ԫ��e
    //i�ĺϷ�ֵΪ1<=i<=ListLength_Sq(L)+1
    if (i < 1 || i > L->length + 1) return 0;   //iֵ���Ϸ�
    if (L->length >= L->listsize) {
        ElemType *newbase = (ElemType *) realloc(L->elem,
                                                 (L->listsize + LISTINCREMENT) * sizeof(ElemType));
        if (!newbase) exit(-2);
        L->elem = newbase;
        L->listsize += LISTINCREMENT;
    }
    ElemType *q = &(L->elem[i - 1]); //qΪ����λ��
    for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p) {
        *(p + 1) = *p;
    }
    *q = e; //����e
    ++L->length;
    return 1;
}

int ListDelete_Sq(SqList *L, int i, ElemType *e) {
    //��˳�����Ա�L��ɾ����i��Ԫ�أ�����e������ֵ
    if ((i < 1) || (i > L->length)) return 0; //iֵ���Ϸ�
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
    printf("������%d����\n", LIST_INIT_SIZE);
    for (int i = 0; i < LIST_INIT_SIZE; ++i) {
        scanf("%d", &L->elem[i]);
        L->length++;
    }
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    printf("������Ҫ�����λ�ú���ֵ\n");
    int i, e;
    scanf("%d %d", &i, &e);
    ListInsert_Sq(L, i, e);
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    printf("������Ҫɾ����λ��\n");
    scanf("%d", &i);
    ListDelete_Sq(L, i, &e);
    for (int i = 0; i < L->length; ++i) {
        printf("%d ", L->elem[i]);
    }
    printf("\n");
    system("pause");
}