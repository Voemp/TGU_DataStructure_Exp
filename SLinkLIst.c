#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

void ListPrint(LinkList L) {
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
    while (p && j < i - 1) {
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) return 0;
    LNode *s = (LNode *) calloc(1, sizeof(LNode));
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

int main() {
    int i, e;
    LinkList L = (LNode *) calloc(1, sizeof(LNode));
    L->next = NULL;
    printf("������5����\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        ListInsert_L(L, i, e);
    }
    ListPrint(L);
    printf("������Ҫ�����λ�ú���ֵ\n");
    scanf("%d %d", &i, &e);
    ListInsert_L(L, i, e);
    ListPrint(L);
    system("pause");
}