#ifndef HELPER_H
#define HELPER_H

#include "../include/tree.h"

void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
Node* lesserLeaf(struct Node* node);
int lenght(NodeLinkedList* head);

#endif 
