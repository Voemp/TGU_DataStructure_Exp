#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree CreateBiTree(BiTree T) {
    //�������������������н���ֵ��һ���ַ������ո��ַ���ʾ������
    //������������ʾ������T
    ElemType ch;
    scanf("%c", &ch);
    if (ch == ' ') T = NULL;
    else {
        T = (BiTree) calloc(1, sizeof(BiTNode));
        T->data = ch;
        T->lchild = CreateBiTree(T->lchild);
        T->rchild = CreateBiTree(T->rchild);
    }
    return T;
}

BiTree InOrderTraverse(BiTree T) {
    //����������������ǵݹ�
    BiTree p = T;
    BiTree S[100];
    int top = -1;
    while (p || top != -1) {
        while (p) {
            S[++top] = p;
            p = p->lchild;
        }
        if (top != -1) {
            p = S[top--];
            printf("%c ", p->data);
            p = p->rchild;
        }
    }
    printf("\n");
    return T;
}

int main() {
    BiTree T = NULL;
    printf("�밴�����������������н���ֵ��һ���ַ������ո��ַ���ʾ����\n");
    T = CreateBiTree(T);
    printf("����������������ǵݹ�\n");
    InOrderTraverse(T);
    return 0;
}