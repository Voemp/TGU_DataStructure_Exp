#include <stdio.h>
#include <stdlib.h>

typedef int ElemType;

typedef struct LNode {
    ElemType data;
    struct LNode *next;
} LNode, *LinkStack;

void InitStack_L(LinkStack top) {
    //构造一个空栈S
    top->next = NULL;
}

void Push_L(LinkStack top, ElemType e) {
    //插入元素e为新的栈顶元素
    LNode *s = (LNode *) calloc(1, sizeof(LinkStack));
    s->data = e;
    s->next = top->next;
    top->next = s;
}

ElemType Pop_L(LinkStack top) {
    //若栈不空，则删除S的栈顶元素，用e返回其值，否则返回0
    if (top->next == NULL) return 0; //栈空
    LinkStack p = top->next;
    ElemType e = p->data;
    top->next = p->next;
    free(p);
    return e;
}

void StackPrint(LinkStack top) {
    //输出栈
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
    //读取
    printf("请输入5个数\n");
    for (i = 1; i <= 5; ++i) {
        scanf("%d", &e);
        Push_L(top, e);
    }
    StackPrint(top);
    //压入
    printf("请输入要压入栈的数\n");
    scanf("%d", &e);
    Push_L(top, e);
    StackPrint(top);
    //弹出
    printf("按任意键弹出栈顶元素\n");
    getchar();
    getchar();
    e = Pop_L(top);
    printf("弹出的元素为%d\n", e);
    system("pause");
    return 0;
}