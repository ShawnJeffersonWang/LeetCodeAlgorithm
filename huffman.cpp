#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

#define N 54
using namespace std;

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
    Node *node = new Node();
    node->ch = ch;
    node->fre = fre;
    node->lchild = nullptr;
    node->rchild = nullptr;
    return node;
}

void getFrequence(string &s, int *w) {
    for (char x: s) {
        w[charToInt(x)]++;
    }
}

void init_tree(vector<Node *> &tree, int *w) {
    for (int i = 0; i < N; i++) {
        if (w[i] == 0) continue;
        tree.push_back(getNode(intToChar(i), w[i]));
    }
}

int getMinFreqNode(char c, vector<Node *> &tree, int size) {
    int pos = 0;
    if (tree[pos]->ch == c) pos++;
    for (int i = 1; i <= size; i++) {
        if (tree[i]->ch == c) continue;
        if (tree[pos]->fre > tree[i]->fre) pos = i;
    }
    return pos;
}

void build_tree(vector<Node *> &tree, int *w) {
    init_tree(tree, w);
    int n = tree.size();
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

void getEncode(Node *node, string str, string *encode, unordered_map<string, char> &m) {
    if (node->lchild == nullptr && node->rchild == nullptr) {
        encode[charToInt(node->ch)] = str;
        m[str] = node->ch;
    }
    if (node->lchild != nullptr) getEncode(node->lchild, str + '0', encode, m);
    if (node->rchild != nullptr) getEncode(node->rchild, str + '1', encode, m);
}

string stringToEncode(string s, string *encode) {
    string ans;
    for (int i = 0; i < s.size(); i++) {
        ans += encode[charToInt(s[i])];
    }
    return ans;
}

string encodeToString(string s, unordered_map<string, char> &m) {
    string str;
    string ans;
    for (int i = 0; i < s.size(); i++) {
        str += s[i];
        if (!m.count(str)) continue;
        ans += m[str];
        str.clear();
    }
    return ans;
}

double getAverageEncodeSize(string *encode, const int *w) {
    double sum = 0, ans = 0;
    for (int i = 0; i < N; i++) sum += w[i];
    for (int i = 0; i < N; i++) {
        if (!w[i]) continue;
        ans += 1.0 * w[i] / sum * encode[i].size();
    }
    return ans;
}

int main() {
    string s;
    int w[N] = {0};
    vector<Node *> tree;
    string encode[N];
    unordered_map<string, char> m;
    getline(cin, s);
    s.erase(s.end() - 1);
    getFrequence(s, w);
    build_tree(tree, w);
    getEncode(tree[0], "", encode, m);
    cout << stringToEncode(s, encode) << endl;;
    cin >> s;
    cout << encodeToString(s, m) << endl;
    printf("%.2lf", getAverageEncodeSize(encode, w));
    return 0;
}