/*
 * binary tree.c
 *
 *  Created on: 2020. 5. 28.
 *      Author: user
 */

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>



typedef struct node {
	int key;
	struct node* left;
	struct node* right;
} Node;

/* for stack */
#define MAX_STACK_SIZE		20
Node* stack[MAX_STACK_SIZE];
int top = -1;

Node* pop();
void push(Node* aNode);

/* for queue */
#define MAX_QUEUE_SIZE		20
Node* queue[MAX_QUEUE_SIZE];
int front = -1;
int rear = -1;

Node* deQueue();
void enQueue(Node* aNode);


int initializeBST(Node** h);

/* functions that you have to implement */
void recursiveInorder(Node* ptr);	  /* recursive inorder traversal */
void iterativeInorder(Node* ptr);     /* iterative inorder traversal */
void levelOrder(Node* ptr);	          /* level order traversal */
int insert(Node* head, int key);      /* insert a node to the tree */
int deleteNode(Node* head, int key);  /* delete the node for the key */
int freeBST(Node* head); /* free all memories allocated to the tree */

/* you may add your own defined functions if necessary */
Node* searchIt(Node* ptr, int key);

int isFull();
int isEmpty();

//void printStack();



int main()
{
	char command;
	int key;
	Node* head = NULL;

	printf("sunyilin software 2016039102");
	do {
		printf("\n\n");
		printf("----------------------------------------------------------------\n");
		printf("                   Binary Search Tree #2                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize BST       = z                                       \n");
		printf(" Insert Node          = i      Delete Node                  = d \n");
		printf(" Recursive Inorder    = r      Iterative Inorder (Stack)    = t \n");
		printf(" Level Order (Queue)  = l      Quit                         = q \n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch (command) {
		case 'z': case 'Z':
			initializeBST(&head);
			break;
		case 'q': case 'Q':
			freeBST(head);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insert(head, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(head, key);
			break;

		case 'r': case 'R':
			recursiveInorder(head->left);
			break;
		case 't': case 'T':
			iterativeInorder(head->left);
			break;

		case 'l': case 'L':
			levelOrder(head->left);
			break;

//		case 'p': case 'P':
//			printStack();
//			break;

		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	} while (command != 'q' && command != 'Q');

	return 1;
}

int initializeBST(Node** h) {

	/* if the tree is not empty, then remove all allocated nodes from the tree*/
	if (*h != NULL)
		freeBST(*h);

	/* create a head node */
	*h = (Node*)malloc(sizeof(Node));
	(*h)->left = NULL;	/* root */
	(*h)->right = *h;
	(*h)->key = -9999;

	top = -1;

	front = rear = -1;

	return 1;
}



void recursiveInorder(Node* ptr)
{
	if (ptr) {
		recursiveInorder(ptr->left);
		printf(" [%d] ", ptr->key);
		recursiveInorder(ptr->right);
	}
}

/**
 * textbook: p 224
 */
void iterativeInorder(Node* node)
{
	for (;;) {
		for (; node; node = node->left)
			push(node);

		node = pop();
		if (!node)break;
		printf("[%d]   ", node->key);
		node = node->right;
	}
}


	/* textbook: p 225
	*/

 void levelOrder(Node* ptr) {
	if (!ptr) return;
	enQueue(ptr);
	for (;;) {
		ptr = deQueue(ptr);
		if (ptr) {
			printf("[%d]  ", ptr->key);
			if (ptr->left)
				enQueue(ptr->left);
			if (ptr->right)
				enQueue(ptr->right);
		}
		else break;
	}
}



int insert(Node* head, int key)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->key = key;
	newNode->left = NULL;
	newNode->right = NULL;

	if (head->left == NULL) {
		head->left = newNode;
		return 1;
	}

	/* head->left is the root */
	Node* ptr = head->left;

	Node* parentNode = NULL;
	while (ptr != NULL) {

		/* if there is a node for the key, then just return */
		if (ptr->key == key) return 1;

		/* we have to move onto children nodes,
		* keep tracking the parent using parentNode */
		parentNode = ptr;

		/* key comparison, if current node's key is greater than input key
		* then the new node has to be inserted into the right subtree;
		* otherwise the left subtree.
		*/
		if (ptr->key < key)
			ptr = ptr->right;
		else
			ptr = ptr->left;
	}

	/* linking the new node to the parent */
	if (parentNode->key > key)
		parentNode->left = newNode;
	else
		parentNode->right = newNode;
	return 1;
}


int deleteNode(Node* head, int key)
{
	int a=0;
	int b=0;
	Node* ptr = NULL;
	Node* ptr1 = NULL;
	Node* ptr2 = NULL;
	head=head->left;
	if (head->key == key) {
		printf("\n Cannot find the node [%d]\n", key);
		return 0;
	}
	while(key!=head->key&&head!=NULL){

		if(key<head->key){
			a=0;//찾은 것이 left에 있다
			ptr=head;
			head=head->left;
		}
		else if(key>head->key){
			a=1;//찾은 것이 right에 있다
			ptr=head;
			head=head->right;

		}
	}

	if (head->left == NULL && head->right == NULL) {//양쪽 다 없다
		if(a==0){
			ptr->left=NULL;
			free(head);
			head=NULL;
		}
		else{
			ptr->right=NULL;
			free(head);
			head=NULL;
		}

	}
	else if (head->left == NULL && head->right != NULL) {//right child 있음
		head->key = head->right->key;
		free(head->right);
		head->right = NULL;
	}
	else if (head->right == NULL && head->left != NULL) {//left child 있음
		head->key = head->left->key;
		free(head->left);
		head->left = NULL;
	}
	else{//양쪽다있음
		ptr2=head;//삭제 할 것
		head=head->left;
		while(head->right){
			b=1;
			ptr1=head;
			head=head->right;
		}
		ptr2->key=head->key;
		if(b==1){
			ptr1->right=NULL;
			free(head);
			head=NULL;
		}
		else{
			ptr2->left=NULL;
			free(head);
			head=NULL;
		}
	}
	return 0;
}



void freeNode(Node* ptr)
{
	if (ptr) {
		freeNode(ptr->left);
		freeNode(ptr->right);
		free(ptr);
	}
}

int freeBST(Node* head)
{

	if (head->left == head)
	{
		free(head);
		return 1;
	}

	Node* p = head->left;

	freeNode(p);

	free(head);
	return 1;
}



Node* pop()
{
	Node* a = stack[top];
	top--;
	return a;

}

void push(Node* aNode)
{
	top++;
	stack[top] = aNode;
}



Node* deQueue()
{
//	if (isEmpty())
//		printf("Circular Queue is Empty");
	Node* a = queue[front];
	front = (front + 1) % MAX_QUEUE_SIZE;//front++
	return a;
}

void enQueue(Node* aNode)
{
	if(isFull()) printf("queue is full");
	else queue[rear++]=aNode;
}

int isEmpty()
{
	if (front == rear) {//cQ==공queue

		return 1;
	}
	return 0;
}

int isFull()
{
	if ((rear - front + MAX_QUEUE_SIZE) % MAX_QUEUE_SIZE == MAX_QUEUE_SIZE - 1)//queue의원소수==max크기
	{
		return 1;
	}
	return 0;
}


