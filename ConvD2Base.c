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

int IsEmpty_Sq(SqStack *S) {
    //�ж�ջ�Ƿ�Ϊ��
    if (S->top == S->base) return 1;
    else return 0;
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

int Pop_Sq(SqStack *S) {
    //��ջ���գ���ɾ��S��ջ��Ԫ�أ���������ֵ�����򷵻�0
    if (S->top == S->base) return 0; //ջ��
    return *--S->top;
}

void StackPrint(SqStack *S) {
    //���ջ
    ElemType *p = S->top;
    while (p != S->base) {
        printf("%d ", *--p);
    }
    printf("\n");
}

// ʮ����ת��������
void convertDecimalToBase(int decimal, int base) {
    SqStack stack;
    InitStack_Sq(&stack);

    while (decimal > 0) {
        int remainder = decimal % base;
        Push_Sq(&stack, remainder);
        decimal /= base;
    }

    printf("ת�����Ϊ��");
    while (!IsEmpty_Sq(&stack)) {
        int digit = Pop_Sq(&stack);
        if (digit < 10) {
            printf("%d", digit);
        } else {
            printf("%c", 'A' + digit - 10); // ��д��ĸ��ʾʮ�����Ƶ�10��15
        }
    }

    printf("\n");
}

int main() {
    int decimalNumber;
    int targetBase;

    printf("����һ��ʮ������: ");
    scanf("%d", &decimalNumber);
    printf("Ŀ�����ƣ�2��8��16��: ");
    scanf("%d", &targetBase);

    if (targetBase == 2 || targetBase == 8 || targetBase == 16) {
        convertDecimalToBase(decimalNumber, targetBase);
    } else {
        printf("Ŀ��������Ч��ֻ֧��2��8��16\n");
    }

    system("pause");
    return 0;
}