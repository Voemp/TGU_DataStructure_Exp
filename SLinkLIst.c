#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkList;

void ListPrint(LinkList L) {
    //输出链表
    LinkList p = L;
    while (p->next != NULL) {
        printf("%d ", p->next->data);
        p = p->next;
    }
    printf("\n");
}

int ListInsert_L(LinkList L, int i, ElemType e) {
    //在带头结点的单链线性表L中第i个位置之前插入元素e
    LinkList p = L;
    int j = 0;
    while (p && j < i - 1) {    //寻找第i-1个结点
        p = p->next;
        ++j;
    }
    if (!p || j > i - 1) return 0;  //i小于1或者大于表长+1
    LNode *s = (LNode *) calloc(1, sizeof(LNode));  //生成新结点
    s->data = e;
    s->next = p->next;
    p->next = s;
    return 1;
}

int ListDelete_L(LinkList L, int i, ElemType *e) {
    //在带头结点的单链线性表L中,删除第i个元素,并由e返回其值
    LinkList p = L;
    int j = 0;
    while (p->next && j < i - 1) {  //寻找第i个结点,并令p指向其前驱
        p = p->next;
        ++j;
    }
    if (!(p->next) || j > i - 1) return 0;  //删除位置不合理
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
    printf("请输入5个数\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        ListInsert_L(L, i, e);
    }
    ListPrint(L);
    //插入
    printf("请输入要插入的位置和数值\n");
    scanf("%d %d", &i, &e);
    ListInsert_L(L, i, e);
    ListPrint(L);
    //删除
    printf("请输入要删除的位置\n");
    scanf("%d", &i);
    ListDelete_L(L, i, &e);
    ListPrint(L);
    system("pause");
    return 0;
}