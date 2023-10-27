#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

void ListPrint(LinkList L) {
    //�������
    LinkList p = L;
    while (p->next != NULL) {
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
}

int ListInsert_L(LinkList L, int i, ElemType e) {
    //�ڴ�ͷ���ĵ������Ա�L�е�i��λ��֮ǰ����Ԫ��e
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1) {    //Ѱ�ҵ�i-1�����
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) return 0;  //iС��1���ߴ��ڱ�+1
    LNode *s = (LNode *) calloc(1, sizeof(LNode));  //�����½��
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

int ListDelete_L(LinkList L, int i, ElemType *e) {
    //�ڴ�ͷ���ĵ������Ա�L��,ɾ����i��Ԫ��,����e������ֵ
    LinkList p = L;
    int j = 0;
    while (p->next && j < i - 1) {  //Ѱ�ҵ�i�����,����pָ����ǰ��
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1) return 0;  //ɾ��λ�ò�����
    LinkList q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    return 1;
}

int main() {
    int i;
    ElemType e;
    LinkList L = (LNode *) calloc(1, sizeof(LNode));
    L->next = NULL;
    printf("������5����\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        ListInsert_L(L, i, e);
    }
    ListPrint(L);
    //����
    printf("������Ҫ�����λ�ú���ֵ\n");
    scanf("%d %d", &i, &e);
    ListInsert_L(L, i, e);
    ListPrint(L);
    //ɾ��
    printf("������Ҫɾ����λ��\n");
    scanf("%d", &i);
    ListDelete_L(L, i, &e);
    ListPrint(L);
    system("pause");
    return 0;
}