#ifndef HELPER_H
#define HELPER_H

#include "../include/tree.h"

void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
Node* lesserLeaf(struct Node* node);
NodeLinkedList* ConvertTreeToList(Node* root);
int lenght(NodeLinkedList* head);
void PrintLinkedList(NodeLinkedList* head);
void insertAtBeginning(NodeLinkedList*& head, int data);
void displaySort(NodeLinkedList* head);
void displaySortShell(NodeLinkedList* head);
void swapNodes(struct NodeLinkedList** head, int x, int y);

#endif 
