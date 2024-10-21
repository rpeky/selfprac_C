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
	//check for overflows if pushing to stack
	if(a->maxstack > UINT_MAX/2){
		printf("stack size overflow");
		exit(-1);
	}
	if(a->size==a->maxstack){
		a->maxstack*=2;
		a->stack=realloc(a->stack, a->maxstack*sizeof(int));
		
		if(a->stack==NULL){
			printf("realloc failed\n");
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
	if(a->size==0){
		printf("empty stack\n");
		return -1;
	}
	return a->stack[a->size-1];
}

int isEmpty(mystack *a){
	return a->size==0;
}

unsigned stacksize(mystack *a){
	return a->size;
}

void printsize(mystack *a){
	printf("stack size %u\n",a->size);
}

void printstack(mystack *a){
	printf("printing stack\n");
	for(int i=0;i<a->size;++i){
		printf("%d\n",a->stack[i]);
	}
}

void freestack(mystack *a){
	free(a->stack);
	a->stack=NULL;
	a->size=0;
	a->maxstack=0;
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
    printstack(&stack1);
    printf("peeking top value: %d\n",peek(&stack1));
    printf("popped %d\n",pop(&stack1));
    printf("peeking top value: %d\n",peek(&stack1));
    printstack(&stack1);

    freestack(&stack1);
    
    return 0;
}
