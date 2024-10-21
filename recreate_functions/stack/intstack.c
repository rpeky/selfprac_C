#include <stdio.h>
#include <stdlib.h>

typedef struct mystack{
    int *stack;
    unsigned size;
    unsigned maxstack;
} mystack;

void initstack(mystack *a, unsigned initialsz){
    a->stack= (int*)malloc(initialsz*sizeof(int));
    if (a->stack==NULL){
        printf("malloc failed\n");
        exit(-1);
    }
    a->size=0;
    a->maxstack=initialsz;
}

void push(mystack *a, int x){
    if(a->size==a->maxstack){
        a->maxstack*=2;
        a->stack=realloc(a->stack, a->maxstack*sizeof(int));

        if(a->stack==NULL){
            printf("malloc failed\n");
            exit(-1);
        }
    }
    a->stack[a->size]=x;
    a->size+=1;
}

int pop(mystack *a){
    if(a->size==0){
        printf("empty stack, unable to pop\n");
        return -1;
    }
    a->size-=1;
    return a->stack[a->size];
}

int peek(mystack *a){
    return a->stack[a->size];
}

int isEmpty_elsesize(mystack *a){
    if (a->size==0){
        printf("stack is empty\n");
        return 0;
    }
    printf("not empty, size of stack is %d\n",a->size);
    return a->size;
}

void printstack(mystack *a){
    printf("printing stack\n");
    for(int i=0;i<a->size;++i){
        printf("%d\n",a->stack[i]);
    }
}

int main(int argc, char **argv){
    //create and initialise stack
    mystack stack1;
    initstack(&stack1, 2);

    push(&stack1, 1);
    push(&stack1, 2); 
    push(&stack1, 3);
    push(&stack1, 4);
    push(&stack1, 5); 
    push(&stack1, 6);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);
    pop(&stack1);

    printstack(&stack1);
    return 0;
}
