#include <stdio.h>

#include <stdio.h>
#include <stdlib.h>

typedef int DataType;
typedef struct node {
    DataType data;
    struct node *next;
} LNode, *LinkList;

LinkList CreatLinkList();  //创建无头结点单链表,并返回头指针。
void PrintLinkList(LinkList H);//依次输出无头结点单链表H中各个元素结点，若为空表则输出NONE。
void MoveLaToLb(LinkList *pa, int i, int len, LinkList *pb, int j);

int main() {
    LinkList la, lb;
    int i, j, len;
    la = CreatLinkList();
    lb = CreatLinkList();
    scanf("%d %d %d", &i, &j, &len);
    MoveLaToLb(&la, i, len, &lb, j);
    PrintLinkList(la);
    PrintLinkList(lb);
}

LinkList CreatLinkList() {
    int n, i;
    LNode *nw, *rear = NULL, *head = NULL;
    scanf("%d", &n);//接收结点总数
    for (i = 0; i < n; i++) {
        nw = (LNode *) malloc(sizeof(LNode));
        scanf("%d", &nw->data);
        if (rear == NULL)
            rear = head = nw;
        else {
            rear->next = nw;
            rear = nw;
        }
    }
    if (rear)
        rear->next = NULL;
    return head;
}

void PrintLinkList(LinkList H) {
    LNode *p;
    if (!H) {
        printf("NONE\n");
        return;
    }
    for (p = H; p; p = p->next)
        printf("%d ", p->data);
    printf("\n");
}


/* 请在这里填写答案 */
void MoveLaToLb(LinkList *pa, int i, int len, LinkList *pb, int j) {
    LNode *h_pa = malloc(sizeof(LNode));
    h_pa->next = *pa;
    LNode *h_pb = malloc(sizeof(LNode));
    h_pb->next = *pb;
    LNode *cur_pa = h_pa->next;
    LNode *pre_pa = h_pa;
    LNode *cur_pb = h_pb->next;
    int k;
    for (k = 1; cur_pa && k < i; k++) {
        pre_pa = cur_pa;
        cur_pa = cur_pa->next;
    }
    if (!cur_pa) {
        free(h_pa);
        free(h_pb);
        return;
    }
    LNode *end_pa = cur_pa;
    for (k = 1; end_pa && k < len; k++) {
        end_pa = end_pa->next;
    }
    if (!end_pa) {
        free(h_pa);
        free(h_pb);
        return;
    }
    for (k = 0; cur_pb && k < j; k++) {
        cur_pb = cur_pb->next;
    }
    if (!cur_pb) {
        free(h_pa);
        free(h_pb);
        return;
    }
    pre_pa->next = end_pa->next;
    end_pa->next = cur_pb->next;
    cur_pb->next = cur_pa;
    *pa = h_pa->next;
    *pb = h_pb->next;
    free(h_pa);
    free(h_pb);
}