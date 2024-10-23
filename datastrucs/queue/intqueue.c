#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct intstack{
	int *stack;
	unsigned size;
	unsigned maxstack;
} intstack;

void initstack(intstack *a, unsigned initialsz){
	a->stack= (int*)malloc(initialsz*sizeof(int));
	if (a->stack==NULL){
		printf("malloc failed\n");
		exit(-1);
	}
	a->size=0;
	a->maxstack=initialsz;
}

void push(intstack *a, int x){
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

int pop(intstack *a){
	if(a->size==0){
		printf("empty stack, unable to pop\n");
		return -1;
	}
	a->size-=1;
	return a->stack[a->size];
}

int peek(intstack *a) {
    if (a->size == 0) {
        printf("Empty stack\n");
        return -1;
    }
    return a->stack[a->size - 1];
}


typedef struct intqueue{
	intstack left_stack;
	intstack right_stack;
} intqueue;

void initqueue(intqueue *a){
	initstack(&a->left_stack, 2);
	initstack(&a->right_stack, 2);
}

void enqueue(intqueue *a, int x){
	push(&a->left_stack,x);
}

int dequeue(intqueue *a){
	//flush left to right stack if there is nothing in right
	if(a->right_stack.size == 0){
		while(a->left_stack.size>0)
			push(&a->right_stack, pop(&a->left_stack));
	}

	//right stack is still empty
	if(a->right_stack.size==0){
		printf("Queue empty\n");
		return -1;
	}

	//return dequeued item
	return pop(&a->right_stack);

}

int peek_queue(intqueue *a){
	if (a->right_stack.size == 0){
		while (a->left_stack.size > 0) {
			push(&a->right_stack, pop(&a->left_stack));
        }
    }

    if (a->right_stack.size == 0) {
        printf("Empty queue\n");
        return -1;
    }

    return peek(&a->right_stack);  // Use the stack peek function
}

int main(int argc, char** argv){
	intqueue newq;
	initqueue(&newq);
	enqueue(&newq, 1);
	enqueue(&newq, 2);
	enqueue(&newq, 3);

	printf("Peeking1: %d\n",peek_queue(&newq));
	printf("Dequeue1: %d\n",dequeue(&newq));
	printf("Peeking2: %d\n",peek_queue(&newq));
	printf("Dequeue2: %d\n",dequeue(&newq));
	printf("Peeking3: %d\n",peek_queue(&newq));
	printf("Dequeue3: %d\n",dequeue(&newq));
	printf("Dequeue-1: %d\n",dequeue(&newq));

	return 0;
}
