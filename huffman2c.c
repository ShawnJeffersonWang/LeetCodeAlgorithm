#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 54

typedef struct node {
    char ch;
    int fre;
    struct node *lchild, *rchild;
} Node;

int charToInt(char c) {
    if (c == ' ') return 0;
    if (c == '.') return 1;
    if (c <= 'Z') return (int) c - 63;
    return (int) c - 69;
}

char intToChar(int i) {
    if (i == 0) return ' ';
    if (i == 1) return '.';
    if (i <= 27) return (char) (i + 63);
    return (char) (i + 69);
}

Node *getNode(char ch, int fre) {
    Node *node = (Node *) malloc(sizeof(Node));
    node->ch = ch;
    node->fre = fre;
    node->lchild = NULL;
    node->rchild = NULL;
    return node;
}

void getFrequence(char *s, int *w) {
    for (int i = 0; s[i] != '\0'; i++) {
        w[charToInt(s[i])]++;
    }
}

void __build_tree(Node **tree, int *w) {
    int treeIndex = 0;
    for (int i = 0; i < N; i++) {
        if (w[i] == 0) continue;
        tree[treeIndex++] = getNode(intToChar(i), w[i]);
    }
}

int getMinFreqNode(char c, Node **tree, int size) {
    int pos = 0;
    if (tree[pos]->ch == c) pos++;
    for (int i = 1; i <= size; i++) {
        if (tree[i]->ch == c) continue;
        if (tree[pos]->fre > tree[i]->fre) pos = i;
    }
    return pos;
}

void build_tree(Node **tree, int *w) {
    __build_tree(tree, w);
    int n = 0;
    while (tree[n] != NULL) {
        n++;
    }
    for (int i = 1; i < n; i++) {
        int pos1 = getMinFreqNode('=', tree, n - i);
        int pos2 = getMinFreqNode(tree[pos1]->ch, tree, n - i);
        Node *node = getNode(tree[pos1]->ch, tree[pos1]->fre + tree[pos2]->fre);
        node->lchild = tree[pos1];
        node->rchild = tree[pos2];
        for (int j = min(pos1, pos2); j < max(pos1, pos2) - 1; j++) {
            tree[j] = tree[j + 1];
        }
        for (int j = max(pos1, pos2); j < n - i; j++) {
            tree[j - 1] = tree[j + 1];
        }
        tree[n - i - 1] = node;
    }
}

void getEncode(Node *node, char *str, char **encode, char **m) {
    if (node->lchild == NULL && node->rchild == NULL) {
        strcpy(encode[charToInt(node->ch)], str);
        strcpy(m[str], &(node->ch));
    }
    if (node->lchild != NULL) {
        char str0[100];
        strcpy(str0, str);
        strcat(str0, "0");
        getEncode(node->lchild, str0, encode, m);
    }
    if (node->rchild != NULL) {
        char str1[100];
        strcpy(str1, str);
        strcat(str1, "1");
        getEncode(node->rchild, str1, encode, m);
    }
}

char *stringToEncode(char *s, char **encode) {
    char *ans = (char *) malloc(strlen(s) * sizeof(char) * 10);
    int index = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        int charIndex = charToInt(s[i]);
        strcat(ans, encode[charIndex]);
    }
    return ans;
}

char *encodeToString(char *s, char **m) {
    char *str = (char *) malloc(strlen(s) * sizeof(char));
    char *ans = (char *) malloc(strlen(s) * sizeof(char));
    int index = 0;
    for (int i = 0; s[i] != '\0'; i++) {
        str[index++] = s[i];
        str[index] = '\0';
        if (strcmp(m[str], "") == 0) continue;
        strcat(ans, m[str]);
        index = 0;
    }
    return ans;
}

double getAverageEncodeSize(char **encode, int *w) {
    double sum = 0, ans = 0;
    for (int i = 0; i < N; i++) sum += w[i];
    for (int i = 0; i < N; i++) {
        if (!w[i]) continue;
        ans += 1.0 * w[i] / sum * strlen(encode[i]);
    }
    return ans;
}

int main() {
    char s[1000];
    int w[N] = {0};
    Node *tree[N];
    char *encode[N];
    char *m[100];
    for (int i = 0; i < 100; i++) {
        m[i] = (char *) malloc(sizeof(char));
        strcpy(m[i], "");
    }
    fgets(s, sizeof(s), stdin);
    s[strlen(s) - 1] = '\0';
    getFrequence(s, w);
    build_tree(tree, w);
    getEncode(tree[0], "", encode, m);
    printf("%s\n", stringToEncode(s, encode));
    scanf("%s", s);
    printf("%s\n", encodeToString(s, m));
    printf("%.2lf\n", getAverageEncodeSize(encode, w));
    return 0;
}