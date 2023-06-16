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

Node* newNode(int iData);
Node* insertNode(struct Node* node, int iData);
Node* createByUser();
Node* createByTextFile(string strFileName);
void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft);
void printTree(Node* root);

#endif  // TREE_H
