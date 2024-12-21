#include <stdio.h>
int main(int argc, char **argv){
    int x=-1;
    x=x>=0?x:-1*x;
    printf("%d\n",x);
    return x;
}
