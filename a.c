#include <string.h>
#include <malloc.h>

void swap(int *a,int *b){
    int t;
    t=*a;
    *a=*b;
    *b=t;
}

int main() {
    int a=3;
    int b=5;
    swap(&a,&b);
    printf("%d %d\n",a,b);
}