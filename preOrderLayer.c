#include<stdio.h>
#include<stdlib.h>

typedef char DataType;

typedef struct Node {
    DataType data;
    struct Node *Lchild;
    struct Node *Rchild;
} BiTNode, *BiTree;

BiTree CreatBiTree();//用扩展先序遍历序列创建二叉链表
void PreOrderLayer(BiTree bt, int lay);

int main() {
    BiTree root;
    root = CreatBiTree();
    PreOrderLayer(root, 1);
}

BiTree CreatBiTree()//用扩展先序遍历序列创建二叉链表
{
    BiTree bt;
    char ch;
    ch = getchar();
    if (ch == '^')
        return NULL;
    bt = (BiTree) malloc(sizeof(BiTNode));
    bt->data = ch;
    bt->Lchild = CreatBiTree();
    bt->Rchild = CreatBiTree();
    return bt;
}


/* 请在这里填写答案 */
void PreOrderLayer(BiTree bt, int lay) {
    if (bt == NULL) {
        return;
    }
    printf("(%c,%d)", bt->data, lay);
    PreOrderLayer(bt->Lchild, lay + 1);
    PreOrderLayer(bt->Rchild, lay + 1);
}
//test
//ABD^^E^^CF^^G^^
//(A,1)(B,2)(D,3)(E,3)(C,2)(F,3)(G,3)
