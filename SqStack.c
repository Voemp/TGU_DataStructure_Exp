#include <stdio.h>
#include <stdlib.h>

#define STACK_INIT_SIZE 100   //存储空间初始分配量
#define STACKINCREMENT 10   //存储空间分配增量
typedef int ElemType;

typedef struct {
    ElemType *base; //在栈构造之前和销毁之后，base的值为NULL
    ElemType *top;  //栈顶指针
    int stacksize;  //当前已分配的存储空间，以元素为单位
} SqStack;

int InitStack_Sq(SqStack *S) {
    //构造一个空栈S
    S->base = (ElemType *) calloc(STACK_INIT_SIZE, sizeof(ElemType));
    if (!S->base) exit(-2); //存储分配失败
    S->top = S->base;
    S->stacksize = STACK_INIT_SIZE;
    return 1;
}

int Push_Sq(SqStack *S, ElemType e) {
    //插入元素e为新的栈顶元素
    if (S->top - S->base >= S->stacksize) { //栈满，追加存储空间
        S->base = (ElemType *) realloc(S->base, (S->stacksize + STACKINCREMENT) * sizeof(ElemType));
        if (!S->base) exit(-2); //存储分配失败
        S->top = S->base + S->stacksize;
        S->stacksize += STACKINCREMENT;
    }
    *S->top++ = e;
    return 1;
}

int Pop_Sq(SqStack *S, ElemType *e) {
    //若栈不空，则删除S的栈顶元素，用e返回其值，并返回1，否则返回0
    if (S->top == S->base) return 0; //栈空
    *e = *--S->top;
    return 1;
}

void StackPrint(SqStack *S) {
    //输出栈
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
    //读取
    printf("请输入5个数\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        Push_Sq(S, e);
    }
    StackPrint(S);
    //压入
    printf("请输入要压入栈的数\n");
    scanf("%d", &e);
    Push_Sq(S, e);
    StackPrint(S);
    //弹出
    printf("按任意键弹出栈顶元素\n");
    getchar();
    getchar();
    Pop_Sq(S, &e);
    printf("弹出的元素为%d\n", e);
    printf("\n");
    system("pause");
    return 0;
}