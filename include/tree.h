#ifndef TREE_H
#define TREE_H

#include <string>
#include <fstream>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

// em alguns casos temos de lidar com linked lists, entao precisamos de um novo tipo de Node
struct NodeLinkedList
{
    int iPayload;
    struct NodeLinkedList* ptrNext;
};

#include "../include/helper.h"

Node* newNode(int iData);
Node* insertNode(struct Node* node, int iData);
Node* createByUser();
Node* createByTextFile(string strFileName);
void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
void printTree(Node* root);
void BFS(Node* root);
int calcAltura(struct Node* node);
Node* deleteNode(struct Node* node, int iData);
Node* searchNode(struct Node* node, int iData);
bool isPerfect(Node* head);
bool isComplete(Node* head);
void BubbleSort(Node* root);
void insertionSort(NodeLinkedList** head);
void selectionSort(Node* root);
void shellSort(NodeLinkedList** head);
void BubbleSortRepresentation(Node* root);
void insertionSortRepresentation(Node* root);
void selectionSortRepresentation(Node* root);
void ShellSortRepresentation(Node* root);

#endif 
