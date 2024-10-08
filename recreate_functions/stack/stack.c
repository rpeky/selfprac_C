#include <stdio.h>


void push(){

}

void pop(){

}

void peek(int type, void *top){
    switch (type){
        //int 
        case 1:
            printf("{%d}\n",*(int *)top);
            break;
        //char
        case 2:
            printf("{%c}\n",*(char *)top);
            break;
        //float
        case 3:
            printf("{%f}\n",*(float *)top);
            break;

        case 4:

            break;
    }

}

int main(int argc, char **argv){
    int a = 5;
    char b = 'a';
    float c = 1.1;
    //int d[5] = {1,2,3,4,5};
    void (*arr[3]) = {&a,&b,&c};
    peek(1,arr[0]);
    return 0;
}
