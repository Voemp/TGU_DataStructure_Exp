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

int IsEmpty_Sq(SqStack *S) {
    //判断栈是否为空
    if (S->top == S->base) return 1;
    else return 0;
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

int Pop_Sq(SqStack *S) {
    //若栈不空，则删除S的栈顶元素，并返回其值，否则返回0
    if (S->top == S->base) return 0; //栈空
    return *--S->top;
}

void StackPrint(SqStack *S) {
    //输出栈
    ElemType *p = S->top;
    while (p != S->base) {
        printf("%d ", *--p);
    }
    printf("\n");
}

// 十进制转其他进制
void convertDecimalToBase(int decimal, int base) {
    SqStack stack;
    InitStack_Sq(&stack);

    while (decimal > 0) {
        int remainder = decimal % base;
        Push_Sq(&stack, remainder);
        decimal /= base;
    }

    printf("转换结果为：");
    while (!IsEmpty_Sq(&stack)) {
        int digit = Pop_Sq(&stack);
        if (digit < 10) {
            printf("%d", digit);
        } else {
            printf("%c", 'A' + digit - 10); // 大写字母表示十六进制的10到15
        }
    }

    printf("\n");
}

int main() {
    int decimalNumber;
    int targetBase;

    printf("输入一个十进制数: ");
    scanf("%d", &decimalNumber);
    printf("目标数制（2、8或16）: ");
    scanf("%d", &targetBase);

    if (targetBase == 2 || targetBase == 8 || targetBase == 16) {
        convertDecimalToBase(decimalNumber, targetBase);
    } else {
        printf("目标数制无效，只支持2、8和16\n");
    }

    system("pause");
    return 0;
}