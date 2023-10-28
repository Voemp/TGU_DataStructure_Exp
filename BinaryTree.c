#include <stdio.h>
#include <stdlib.h>

typedef char ElemType;

typedef struct BiTNode {
    ElemType data;
    struct BiTNode *lchild, *rchild;
} BiTNode, *BiTree;

BiTree CreateBiTree(BiTree T) {
    //按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树，
    //构造二叉链表表示二叉树T
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
    //中序遍历二叉树，非递归
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
    printf("请按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树\n");
    T = CreateBiTree(T);
    printf("中序遍历二叉树，非递归\n");
    InOrderTraverse(T);
    return 0;
}