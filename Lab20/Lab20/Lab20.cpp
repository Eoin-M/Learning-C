// Lab20.cpp : Linked List

#include "stdafx.h"
#include "stdio.h"
#include "stdlib.h"

struct node {
	int ID;
	char name[81];
	struct node *nextNode;
} *startNode = NULL;
struct node *currentNode;

void insertNode();
void deleteNode();
void displayNodes();
void searchNode();
void freeMemory();

void main()
{
	int choice;

	while (1)
	{
		puts("Please choose one of the following options: ");
		puts("1. Insert node at the end of the list");
		puts("2. Delete a node by it's ID");
		puts("3. Display all nodes");
		puts("4. Search for a node by it's ID");
		puts("0. Quit");
		scanf("%d", &choice);

		switch (choice){
		case 1: insertNode(); break;
		case 2: deleteNode(); break;
		case 3: displayNodes(); break;
		case 4: searchNode(); break;
		default: freeMemory(); return;
		}
	}
}

void insertNode()
{
	struct node *newNode;

	newNode = (struct node *)malloc(sizeof(struct node)); //allocate memory for the newly entered node

	printf("Enter node ID: ");
	scanf("%d", &newNode->ID);
	printf("Enter node name: ");
	scanf("%s", newNode->name);
	newNode->nextNode = NULL; //next pointer points to null when entering new node

	if (startNode != NULL)
	{
		currentNode = startNode;
		while (currentNode->nextNode != NULL) currentNode = currentNode->nextNode;
	}

	if (startNode == NULL)
	{
		startNode = newNode;
		currentNode = newNode;
	}
	else
	{
		currentNode->nextNode = newNode;
		currentNode = newNode;
	}
	puts("Node created.\n");
}

void deleteNode()
{
	int tempID;
	struct node *previousNode = NULL;

	currentNode = startNode;

	printf("Enter node ID: ");
	scanf("%d", &tempID);

	while (currentNode != NULL)
	{
		if (tempID == currentNode->ID) break;
		previousNode = currentNode;
		currentNode = currentNode->nextNode;
	}
	if (currentNode == NULL) puts("No node found!\n");

	else
	{
		puts("Node found!\n");
		printf("ID:\t%d\nName:\t%s\n", currentNode->ID, currentNode->name);
		puts("\nNode has been deleted.\n");
		if (previousNode == NULL) startNode = currentNode->nextNode;
		else previousNode->nextNode = currentNode->nextNode;
		free(currentNode);
	}
}

void displayNodes()
{
	if (startNode == NULL) { puts("No nodes in list!\n"); return; }

	currentNode = startNode;

	puts("\nID\tName\n--\t----");
	while (currentNode != NULL)
	{
		printf("%d\t%s\n", currentNode->ID, currentNode->name);
		currentNode = currentNode->nextNode;
	}
	printf("\n");
}

void searchNode()
{
	int tempID;

	currentNode = startNode;

	printf("Enter node ID: ");
	scanf("%d", &tempID);

	while (currentNode != NULL)
	{
		if (tempID == currentNode->ID) break;
		currentNode = currentNode->nextNode;
	}
	if (currentNode == NULL) puts("No node found!\n");

	else
	{
		puts("Node found!\n");
		printf("ID:\t%d\nName:\t%s\n\n", currentNode->ID, currentNode->name);
	}
}

void freeMemory()
{
	while (startNode != NULL) //free up all memory
	{
		currentNode = startNode;
		startNode = currentNode->nextNode;
		free(currentNode);
	}
}