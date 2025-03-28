#include <stdio.h>
#include <stdlib.h>

// CLRSv4 10.2 unsorted and doubly linked list

typedef struct dll_node{
	int val;
	struct dll_node *prev;
	struct dll_node *next;
}dll_node;

dll_node *create_node(int value){
	dll_node *new_node = (dll_node*)malloc(sizeof(dll_node));
	if(new_node==NULL){
		fprintf(stderr,"Failed malloc\n");
		exit(EXIT_FAILURE);
	}
	new_node->val = value;
	new_node->prev = NULL;
	new_node->next = NULL;
	return new_node;
}

void insert_head(dll_node **head, int value){
	//create a new node
	dll_node *new_node = create_node(value);

	// insert to head if list is empty
	if(*head==NULL){
		*head = new_node;
		return;
	}
	// point new node to head location (replaces head)
	// address of head is still the old head
	// both nodes are in the same position next to the head 
	// makes the new node next point to the old head node
	// new_node | next -> old head
	new_node->next = *head;
	// since address is still the old head,
	// we can set the previous head to
	// point at the new node
	// shifts the old head node away from *head*
	// new node <- prev | old head
	(*head)->prev = new_node;
	// now we change the address of head to location of new node
	// detach the old head, now its head -> new_node -> old head
	*head = new_node;
}

void insert_tail(dll_node **tail, int value){
	dll_node *new_node = create_node(value);
	// if llist is empty set as the content
	if(*tail==NULL){
		*tail = new_node;
		return;
	}
	// initialise temp to travel to the end
	// taking the next node until the end will travel away from head
	dll_node *temp = *tail;
	while(temp->next!=NULL){
		temp = temp->next;
	}
	// now that we reached the end of the link list
	// assign the last node to point to the new node
	// new node is now the last node in list
	temp->next = new_node;
	// have prev pointer for new node point to the old end
	// old_end <- prev | new_node
	// connects the linked list
	new_node->prev = temp;
}

void print_llist(dll_node *head){
	dll_node *temp = head;
	if(temp==NULL){
		printf("Empty doubly linked list\n");
		return;
	}
	while(temp!=NULL){
		printf("%d ",temp->val);
		temp = temp->next;
	}
	printf("\n");
}



int main(int argc, char **argv){
	printf("test\n");
	dll_node *Node = NULL;
	insert_head(&Node, 5);
	insert_head(&Node, 4);
	insert_head(&Node, 3);
	insert_head(&Node, 2);
	insert_head(&Node, 1);
	print_llist(Node);
	return 0;
}
