#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkStack;

void InitStack_L(LinkStack top) {
    //����һ����ջS
    top->next = NULL;
}

void Push_L(LinkStack top, ElemType e) {
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    LNode *s = (LNode *) calloc(1, sizeof(LinkStack));
    s->data = e;
    s->next = top->next;
    top->next = s;
}

ElemType Pop_L(LinkStack top) {
    //��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ�����򷵻�0
    if (top->next == NULL) return 0; //ջ��
    LinkStack p = top->next;
    ElemType e = p->data;
    top->next = p->next;
    free(p);
    return e;
}

void StackPrint(LinkStack top) {
    //���ջ
    LinkStack p = top->next;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

int main() {
    LinkStack top = (LNode *) calloc(1, sizeof(LNode));
    InitStack_L(top);
    int i;
    ElemType e;
    //��ȡ
    printf("������5����\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        Push_L(top, e);
    }
    StackPrint(top);
    //ѹ��
    printf("������Ҫѹ��ջ����\n");
    scanf("%d", &e);
    Push_L(top, e);
    StackPrint(top);
    //����
    printf("�����������ջ��Ԫ��\n");
    getchar();
    getchar();
    e = Pop_L(top);
    printf("������Ԫ��Ϊ%d\n", e);
    system("pause");
    return 0;
}