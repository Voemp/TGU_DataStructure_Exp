#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100   //�洢�ռ��ʼ������
#define STACKINCREMENT 10   //�洢�ռ��������
typedef int ElemType;

typedef struct {
    ElemType *base; //��ջ����֮ǰ������֮��base��ֵΪNULL
    ElemType *top;  //ջ��ָ��
    int stacksize;  //��ǰ�ѷ���Ĵ洢�ռ䣬��Ԫ��Ϊ��λ
} SqStack;

int InitStack_Sq(SqStack *S) {
    //����һ����ջS
    S->base = (ElemType *) calloc(STACK_INIT_SIZE, sizeof(ElemType));
    if (!S->base) exit(-2); //�洢����ʧ��
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push_Sq(SqStack *S, ElemType e) {
    //����Ԫ��eΪ�µ�ջ��Ԫ��
    if (S->top - S->base >= S->stacksize) { //ջ����׷�Ӵ洢�ռ�
        S->base = (ElemType *) realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(ElemType));
        if (!S->base) exit(-2); //�洢����ʧ��
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return 1;
}

int Pop_Sq(SqStack *S, ElemType *e) {
    //��ջ���գ���ɾ��S��ջ��Ԫ�أ���e������ֵ��������1�����򷵻�0
    if (S->top == S->base) return 0; //ջ��
    *e = *--S->top;
    return 1;
}

void StackPrint(SqStack *S) {
    //���ջ
    ElemType *p = S->top;
    while (p != S->base) {
        printf("%d ", *--p);
    }
    printf("\n");
}

int main() {
    SqStack *S = calloc(1, sizeof(SqStack));
    InitStack_Sq(S);
    int i;
    ElemType e;
    //��ȡ
    printf("������5����\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        Push_Sq(S, e);
    }
    StackPrint(S);
    //ѹ��
    printf("������Ҫѹ��ջ����\n");
    scanf("%d", &e);
    Push_Sq(S, e);
    StackPrint(S);
    //����
    printf("�����������ջ��Ԫ��\n");
    getchar();
    getchar();
    Pop_Sq(S, &e);
    printf("������Ԫ��Ϊ%d\n", e);
    printf("\n");
    system("pause");
    return 0;
}