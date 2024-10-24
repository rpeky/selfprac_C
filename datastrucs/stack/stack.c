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
        s->maxstack*=2;
        s->stack=realloc(s->stack, s->maxstack*sizeof(void*));

        if(s->stack==NULL){
            printf("stack realloc failed\n");
            exit(-1);
        }
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
    if(s->size>0){
        s->size-=1;
        sol.valtype = intpop(s->typetrack_stack);
        sol.valaddr = s->stack[s->size];
        return sol;
    }

    printf("empty stack\n");
    sol.valtype = TYPE_NONE;
    sol.valaddr = NULL;
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
    }

}

void freeomnistack(omnistack *s){
        free(s->stack);
        s->stack = NULL;

        freeintstack(s->typetrack_stack);
        s->typetrack_stack=NULL;
        
        s->size=0;
        s->maxstack=0;
}

int main(int argc, char **argv){
	omnistack stack1;
	initomnistack(&stack1, 2);

	int a = 5;
	char b = 'a';
	float c = 1.1;
    push(&stack1, &a, TYPE_INT);
    push(&stack1, &b, TYPE_CHAR);
    push(&stack1, &c, TYPE_FLOAT);

                // Pop values and display them
    popval val = pop(&stack1);
    peek(val.valtype, val.valaddr);
    val = pop(&stack1);
    peek(val.valtype, val.valaddr);
    val = pop(&stack1);
    peek(val.valtype, val.valaddr);
    freeomnistack(&stack1);
	
	return 0;
}
