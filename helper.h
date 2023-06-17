#ifndef HELPER_H
#define HELPER_H

#include "tree.h"

void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
struct Node* lesserLeaf(struct Node* node);

#endif 
