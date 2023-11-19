#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 54

typedef struct node {
    char ch;
    int fre;
    struct node *lchild;
    struct node *rchild;
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

void init_tree(Node **tree, int *w, int *treeSize) {
    for (int i = 0; i < N; i++) {
        if (w[i] == 0) continue;
        tree[*treeSize] = getNode(intToChar(i), w[i]);
        (*treeSize)++;
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

void build_tree(Node **tree, int *w, int *treeSize) {
    init_tree(tree, w, treeSize);
    int n = *treeSize;
    for (int i = 1; i < n; i++) {
        int pos1 = getMinFreqNode('=', tree, n - i);
        int pos2 = getMinFreqNode(tree[pos1]->ch, tree, n - i);
        Node *node = getNode(tree[pos1]->ch, tree[pos1]->fre + tree[pos2]->fre);
        node->lchild = tree[pos1];
        node->rchild = tree[pos2];
        for (int j = pos1 < pos2 ? pos1 : pos2; j < (pos1 < pos2 ? pos2 - 1 : pos1 - 1); j++) {
            tree[j] = tree[j + 1];
        }
        for (int j = (pos1 < pos2 ? pos2 : pos1); j < n - i; j++) {
            tree[j - 1] = tree[j + 1];
        }
        tree[n - i - 1] = node;
    }
}

void getEncode(Node *node, char *str, char **encode, char **keys, char *values, int *encodeSize, int *mSize) {
    if (node->lchild == NULL && node->rchild == NULL) {
        int index = charToInt(node->ch);
        encode[index] = (char *) malloc((*encodeSize + 1) * sizeof(char));
        strcpy(encode[index], str);
        keys[*mSize] = (char *) malloc((*encodeSize + 1) * sizeof(char));
        strcpy(keys[*mSize], str);
        values[*mSize] = node->ch;
        (*encodeSize)++;
        (*mSize)++;
    }
    if (node->lchild != NULL) {
        char *newStr = (char *) malloc((*encodeSize + 2) * sizeof(char));
        strcpy(newStr, str);
        newStr[*encodeSize] = '0';
        newStr[*encodeSize + 1] = '\0';
        getEncode(node->lchild, newStr, encode, keys, values, encodeSize, mSize);
        free(newStr);
    }
    if (node->rchild != NULL) {
        char *newStr = (char *) malloc((*encodeSize + 2) * sizeof(char));
        strcpy(newStr, str);
        newStr[*encodeSize] = '1';
        newStr[*encodeSize + 1] = '\0';
        getEncode(node->rchild, newStr, encode, keys, values, encodeSize, mSize);
        free(newStr);
    }
}

char *stringToEncode(Node *node, char *s, char **encode) {
    int len = strlen(s);
    char *ans = (char *) malloc(len * N * sizeof(char));
    int index = 0;
    for (int i = 0; i < len; i++) {
        int ch = charToInt(s[i]);
        char *code = encode[ch];
        int codeLen = strlen(code);
        for (int j = 0; j < codeLen; j++) {
            ans[index++] = code[j];
        }
    }
    ans[index] = '\0';
    return ans;
}

char *encodeToString(char *s, char **keys, char *values, int mSize) {
    int len = strlen(s);
    char *ans = (char *) malloc(len * sizeof(char));
    int index = 0;
    char *str = (char *) malloc((len + 1) * sizeof(char));
    int strIndex = 0;
    for (int i = 0; i < len; i++) {
        str[strIndex++] = s[i];
        str[strIndex] = '\0';
        int found = 0;
        for (int j = 0; j < mSize; j++) {
            if (strcmp(keys[j], str) == 0) {
                ans[index++] = values[j];
                strIndex = 0;
                found = 1;
                break;
            }
        }
        if (!found) {
            continue;
        }
    }
    ans[index] = '\0';
    free(str);
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
    int treeSize = 0;
    char *encode[N];
    char *keys[N];
    char values[N];
    int encodeSize = 0;
    int mSize = 0;
    fgets(s, sizeof(s), stdin);
    s[strcspn(s, "\n")] = '\0';
    getFrequence(s, w);
    build_tree(tree, w, &treeSize);
    getEncode(tree[0], "", encode, keys, values, &encodeSize, &mSize);
    char *encodedString = stringToEncode(tree[0], s, encode);
    printf("%s\n", encodedString);
    scanf("%s", s);
    char *decodedString = encodeToString(s, keys, values, mSize);
    printf("%s\n", decodedString);
    printf("%.2lf\n", getAverageEncodeSize(encode, w));

    // Free allocated memory
    for (int i = 0; i < encodeSize; i++) {
        free(encode[i]);
    }
    for (int i = 0; i < mSize; i++) {
        free(keys[i]);
    }
    free(encodedString);
    free(decodedString);

    return 0;
}