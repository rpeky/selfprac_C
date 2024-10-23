#include <stdio.h>
#include <stdlib.h>

typedef struct intstack{
	int *stack;
	unsigned size;
	unsigned maxstack;
} intstack;

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
		printf("stack size overflow\n");
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

typedef struct intqueue{
	intstack left_stack;
	intstack right_stack;
} intqueue;

void initqueue(intqueue *a){
	initstack(a->&left_stack, 2);
	initstack(a->&right_stack, 2);
}

void enqueue(intqueue *a, int x){
	a->left_stack.push(x);
}

int dequeue(intqueue *a){
	if(a->right_stack->size > 0){
		return ;
	}
}

int main(int argc, char** argv){
	printf("test\n");
	return 0;
}
