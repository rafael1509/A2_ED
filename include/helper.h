#ifndef HELPER_H
#define HELPER_H

#include "../include/tree.h"

void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
Node* lesserLeaf(struct Node* node);
NodeLinkedList* ConvertTreeToList(Node* root);
int lenght(NodeLinkedList* head);
void PrintLinkedList(NodeLinkedList* head);
void displaySort(NodeLinkedList* head);

#endif 
