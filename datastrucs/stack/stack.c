#include <stdio.h>
#include <stdlib.h>

typedef struct intstack{
	int *stack;
	unsigned size;
	unsigned maxstack;
} intstack;

void int_initstack(mystack *a, unsigned initialsz){
	a->stack= (int*)malloc(initialsz*sizeof(int));
	if (a->stack==NULL){
		printf("malloc failed\n");
		exit(-1);
	}
	a->size=0;
	a->maxstack=initialsz;
}

enum types{
	TYPE_INT,
	TYPE_LONG,
	TYPE_FLOAT,
	TYPE_DOUBLE,
	TYPE_CHAR,
	TYPE_STR,
	TYPE_PTR,
	TYPE_STRUCT
}

typedef struct omnistack{
	intstack *typetrack_stack;
	void *stack;
	unsigned size;
	unsigned maxstack;
} omnistack;

void initomnistack(omnistack *s, unsigned initialsz){

}
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
	omnistack stack1;
	initomnistack(&stack1);

	int a = 5;
	char b = 'a';
	float c = 1.1;
	
	
	return 0;
}
