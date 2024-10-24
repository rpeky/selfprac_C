#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct intstack{
	int *stack;
	unsigned size;
	unsigned maxstack;
} intstack;

void int_initstack(intstack *a, unsigned initialsz){
	a->stack= (int*)malloc(initialsz*sizeof(int));
	if (a->stack==NULL){
		printf("malloc failed for intstack\n");
		exit(-1);
	}
	a->size=0;
	a->maxstack=initialsz;
}

void intpush(intstack *a, int x){
	//check for overflows if pushing to stack
	if(a->maxstack > UINT_MAX/2){
		printf("stack size overflow\n");
		exit(-1);
	}
	if(a->size==a->maxstack){	
		int *tempstack=realloc(a->stack, a->maxstack*2*sizeof(int));
        if(tempstack==NULL){
            printf("realloc failed\n");
            exit(-1);
        }
        a->stack=tempstack;
        a->maxstack*=2;
	}
	a->stack[a->size]=x;
	a->size+=1;
}

int intpop(intstack *a){
	if(a->size==0){
		printf("empty stack, unable to pop\n");
		return -1;
	}
	a->size-=1;
	return a->stack[a->size];
}

void freeintstack(intstack *a){
	free(a->stack);
	a->stack=NULL;
	a->size=0;
	a->maxstack=0;
}

typedef enum {
	TYPE_INT,
	TYPE_LONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_CHAR,
	TYPE_STR,
	TYPE_PTR,
	TYPE_STRUCT,
    TYPE_NONE
}types;

typedef struct omnistack{
	intstack *typetrack_stack;
	void **stack;
	unsigned size;
	unsigned maxstack;
} omnistack;

void initomnistack(omnistack *s, unsigned initialsz){
    //initialise tracking stack
    s->typetrack_stack = (intstack*)malloc(sizeof(intstack));
    int_initstack(s->typetrack_stack,2);

    s->stack=(void*)malloc(initialsz*sizeof(void*));
    if(s->stack==NULL){
        printf("malloc failed for omnistack\n");
        exit(-1);
    }

    s->size=0;
    s->maxstack=initialsz;

}

void push(omnistack *s, void *dataref, types datatype){
    if(s->maxstack > UINT_MAX/2){
        printf("stack size overflow\n");
        exit(-1);
    }

    if(s->size==s->maxstack){
        
        void **tempstack=realloc(s->stack, s->maxstack*2*sizeof(void*));

        if(tempstack==NULL){
            printf("stack realloc failed\n");
            exit(-1);
        }
        s->stack=tempstack;
        s->maxstack*=2;
    }

    intpush(s->typetrack_stack, datatype);

    s->stack[s->size]=dataref;
    s->size+=1;
}

typedef struct popval{
    types valtype;
    void *valaddr;
}popval;

popval pop(omnistack *s){
    popval sol;
    sol.valtype = TYPE_NONE;
    sol.valaddr = NULL;

    if(s->size>0){
        s->size-=1;
        sol.valtype = intpop(s->typetrack_stack);
        sol.valaddr = s->stack[s->size];
        return sol;
    }

    printf("empty stack\n");
    
    return sol;
}

void freeomnistack(omnistack *s){
        free(s->stack);
        s->stack = NULL;

        freeintstack(s->typetrack_stack);
        s->typetrack_stack=NULL;
        
        s->size=0;
        s->maxstack=0;
}

typedef struct omnique{
    omnistack *left_stack;
    omnistack *right_stack;
}omnique;

void initqueue(omnique *q){
    q->left_stack = (omnistack*)malloc(sizeof(omnistack));
    q->right_stack = (omnistack*)malloc(sizeof(omnistack));
    initomnistack(q->left_stack, 2);
    initomnistack(q->right_stack, 2);
}

void enqueue(omnique *q, void *val, types datatype){
    push(q->left_stack, val, datatype);
}

popval dequeue(omnique *q){
    popval sol;

    if(q->right_stack->size==0){
        while(q->left_stack->size>0){
            popval temp = pop(q->left_stack);
            push(q->right_stack, temp.valaddr, temp.valtype);
        }
    }

    if(q->right_stack->size==0){
        printf("empty queue\n");
        sol.valtype = TYPE_NONE;
        sol.valaddr = NULL;
        return sol;
    }

    sol = pop(q->right_stack);
    return sol; 
}

void peek(int type, void *top){

    switch (type){
        //int 
        case TYPE_INT:
            printf("%d\n",*(int *)top);
            break;

        //long
        case TYPE_LONG:
            printf("%ld\n",*(long *)top);
            break;

        //double, 3dp modify if need more
        case TYPE_DOUBLE:
            printf("%.3f\n",*(double *)top);
            break;

        //float is promoted to double
        case TYPE_FLOAT:
            printf("%.3f\n",*(float *)top);
            break;

        //string
        case TYPE_STR:
            printf("%s\n",(char *)top);
            break;

        //char
        case TYPE_CHAR:
            printf("%c\n",*(char *)top);
            break; 

        //print pointer location
        case TYPE_PTR:
            printf("%p\n",(void *)top);
            break;

        case TYPE_STRUCT:
            printf("Item is a struct, unable to print whole struct\n");
            break;

        default:
            printf("Unknown type, unable to peek\n");
            break;
    }

}

void freeomniqueue(omnique *q){
    freeomnistack(q->left_stack);
    freeomnistack(q->right_stack);
    free(q->left_stack);
    free(q->right_stack);
}

void test_omnistack() {
    omnistack mystack;
    initomnistack(&mystack, 2);

    // Test pushing integers
    int a = 5, b = 10;
    push(&mystack, &a, TYPE_INT);
    push(&mystack, &b, TYPE_INT);

    popval val = pop(&mystack);
    printf("Popped value (int): ");
    peek(val.valtype, val.valaddr); // Expected: 10

    val = pop(&mystack);
    printf("Popped value (int): ");
    peek(val.valtype, val.valaddr); // Expected: 5

    freeomnistack(&mystack);
}

void test_omnique() {
    omnique myqueue;
    initqueue(&myqueue);

    int x = 1, y = 2;
    double d = 3.1415;
    char a= 'a';
    char *st = "testingabc";

    // Test enqueuing different types
    enqueue(&myqueue, &x, TYPE_INT);
    enqueue(&myqueue, &d, TYPE_DOUBLE);
    enqueue(&myqueue, &y, TYPE_INT);
    enqueue(&myqueue, &a, TYPE_CHAR);
    enqueue(&myqueue, st, TYPE_STR);

    // Test dequeuing values
    popval val = dequeue(&myqueue);
    printf("Dequeued value: ");
    peek(val.valtype, val.valaddr); // Expected: 1 (int)

    val = dequeue(&myqueue);
    printf("Dequeued value: ");
    peek(val.valtype, val.valaddr); // Expected: 3.1415 (double)

    val = dequeue(&myqueue);
    printf("Dequeued value: ");
    peek(val.valtype, val.valaddr); // Expected: 2 (int)

    val = dequeue(&myqueue);
    printf("Dequeued value: ");
    peek(val.valtype, val.valaddr); // Expected: 'a' (char)

    val = dequeue(&myqueue);
    printf("Dequeued value: ");
    peek(val.valtype, val.valaddr); // Expected: 'a' (char)


    freeomnistack(myqueue.left_stack);
    freeomnistack(myqueue.right_stack);
}

void test_empty_stack_queue() {
    omnistack mystack;
    initomnistack(&mystack, 2);
    
    // Attempt to pop from an empty stack
    popval val = pop(&mystack);
    printf("Popped from empty stack: ");
    if (val.valtype == TYPE_NONE) {
        printf("Empty stack detected successfully\n");
    }

    omnique myqueue;
    initqueue(&myqueue);

    // Attempt to dequeue from an empty queue
    val = dequeue(&myqueue);
    printf("Dequeued from empty queue: ");
    if (val.valtype == TYPE_NONE) {
        printf("Empty queue detected successfully\n");
    }

    freeomnistack(&mystack);
    freeomnistack(myqueue.left_stack);
    freeomnistack(myqueue.right_stack);
}

void test_mixed_data_types() {
    omnistack mystack;
    initomnistack(&mystack, 2);

    int a = 10;
    float b = 3.14f;
    char c = 'A';

    push(&mystack, &a, TYPE_INT);
    push(&mystack, &b, TYPE_FLOAT);
    push(&mystack, &c, TYPE_CHAR);

    popval val = pop(&mystack);
    printf("Popped value (char): ");
    peek(val.valtype, val.valaddr); // Expected: 'A'

    val = pop(&mystack);
    printf("Popped value (float): ");
    peek(val.valtype, val.valaddr); // Expected: 3.14

    val = pop(&mystack);
    printf("Popped value (int): ");
    peek(val.valtype, val.valaddr); // Expected: 10

    freeomnistack(&mystack);
}

int main(int argc, char **argv) {
    printf("Testing omnistack:\n");
    test_omnistack();

    printf("\nTesting omnique (queue):\n");
    test_omnique();

    printf("\nTesting empty stack and queue:\n");
    test_empty_stack_queue();

    printf("\nTesting mixed data types in omnistack:\n");
    test_mixed_data_types();

    return 0;
}
