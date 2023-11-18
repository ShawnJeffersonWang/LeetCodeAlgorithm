#include<stdio.h>
#include<stdlib.h>
typedef char DataType;
typedef struct Node
{
    DataType data;
    struct Node * Lchild;
    struct Node * Rchild;
}BiTNode,*BiTree;

BiTree CreatBiTree(); //用扩展先序遍历序列创建二叉链表
void SwapLR(BiTree bt);
void PrintTree(BiTree bt,int h); //按树状打印二叉树（课本P168算法6-16

int main()
{
    BiTree root;
    root=CreatBiTree();
    SwapLR(root);
    PrintTree(root,0);
}

BiTree CreatBiTree()//用扩展先序遍历序列创建二叉链表
{
    BiTree bt;
    char ch;
    ch=getchar();
    if(ch=='^')
        return NULL;
    bt=(BiTree )malloc(sizeof(BiTNode));
    bt->data=ch;
    bt->Lchild = CreatBiTree();
    bt->Rchild = CreatBiTree();
    return bt;
}

void PrintTree(BiTree bt,int h)
{
    if(bt == NULL)
        return ;
    PrintTree(bt->Rchild,h+1);
    for(int i=0;i<h;i++)
        printf("  ");
    printf("%c\n",bt->data);
    PrintTree(bt->Lchild,h+1);
}

/* 请在这里填写答案 */
// bug 可能是深浅拷贝的问题
void swap(BiTNode* a,BiTNode* b){
    BiTNode temp=*a;
    *a=*b;
    *b=temp;
}

void SwapLR(BiTree bt){
    if(bt==NULL){
        return;
    }
    swap(bt->Lchild,bt->Rchild);
    SwapLR(bt->Lchild);
    SwapLR(bt->Rchild);
}