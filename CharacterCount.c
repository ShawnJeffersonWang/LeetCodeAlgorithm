#include <stdio.h>

void printCharacterCount(const char *str) {
    int count[256] = {0};
    int i = 0;
    while (str[i] != '\0') {
        count[str[i]]++;
        i++;
    }
    for (int j = 0; j < 256; j++) {
        if (count[j] > 0) {
            printf("%c: %d\n", j, count[j]);
        }
    }
}

int main() {
    char str[100];
    fgets(str,sizeof(str),stdin);
    printCharacterCount(str);
    return 0;
}