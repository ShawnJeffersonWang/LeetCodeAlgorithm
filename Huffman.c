#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#define N 30
#define M 2 * N - 1

typedef struct {
    int Weight;
    int Parent, Lchild, Rchild;
} HTNode, HuffmanTree[M + 1];

typedef char *HuffmanCode[N + 1];

void sel(HuffmanTree ht, int n, int *s1, int *s2) {
    int min1 = INT_MAX;
    int min2 = INT_MAX;
    *s1 = 0;
    *s2 = 0;

    for (int i = 1; i <= n; i++) {
        if (ht[i].Parent == 0) {
            if (ht[i].Weight < min1) {
                min2 = min1;
                *s2 = *s1;

                min1 = ht[i].Weight;
                *s1 = i;
            } else if (ht[i].Weight < min2) {
                min2 = ht[i].Weight;
                *s2 = i;
            }
        }
    }
}

void CrtHuffmanTree(HuffmanTree ht, int w[], int n) {
    int m = 2 * n - 1;
    int s1, s2;
    for (int i = 1; i <= n; i++) {
        ht[i].Weight = w[i];
        ht[i].Parent = 0;
        ht[i].Lchild = 0;
        ht[i].Rchild = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        ht[i].Weight = 0;
        ht[i].Parent = 0;
        ht[i].Lchild = 0;
        ht[i].Rchild = 0;
    }
    for (int i = n + 1; i <= m; i++) {
        sel(ht, i - 1, &s1, &s2);
        ht[i].Weight = ht[s1].Weight + ht[s2].Weight;
        ht[i].Lchild = s1;
        ht[i].Rchild = s2;
        ht[s1].Parent = i;
        ht[s2].Parent = i;
    }
}

void CrtHuffmanCode(HuffmanTree ht, HuffmanCode hc, int n) {
    int c, p;
    char *cd;
    int start;
    cd = (char *) malloc(n * sizeof(char));
    cd[n - 1] = '\0';
    for (int i = 0; i <= n; i++) {
        start = n - 1;
        c = i;
        p = ht[i].Parent;
        while (p != 0) {
            --start;
            if (ht[p].Lchild == c) cd[start] = '0';
            else cd[start] = '1';
            c = p;
            p = ht[p].Parent;
        }
        hc[i] = (char *) malloc((n - start) * sizeof(char));
        strcpy(hc[i], &cd[start]);
    }
    free(cd);
}

void Decode(HuffmanTree ht, HuffmanCode hc, char *input) {
    int p = M;
    int ch;
    int index = 0;
    while ((ch = input[index]) != '\0') {
        if (ch == '0') {
            p = ht[p].Lchild;
        } else if (ch == '1') {
            p = ht[p].Rchild;
        }

        if (ht[p].Lchild == 0 && ht[p].Rchild == 0) {
            printf("%c", p - 1 + 'A');
            p = M;
        }

        index++;
    }
}

int main() {
    int n = 5;
    int weights[] = {5, 9, 12, 13, 16};

    HuffmanTree ht;
    HuffmanCode hc;

    CrtHuffmanTree(ht, weights, n);
    CrtHuffmanCode(ht, hc, n);

    char input[100];
    printf("Enter the encoded string: ");
    fgets(input, 100, stdin);
    input[strcspn(input, "\n")] = '\0';

    printf("Decoded string: ");
    Decode(ht, hc, input);

    return 0;
}