#include "../include/helper.h"

// auxilia na função print
void TreeWriter(Node* root, ofstream& outputFile, string prefix, bool isLeft)
{
    if (root == nullptr)
        return;

    outputFile << prefix;

    if (isLeft)
        outputFile << "├── ";
    else
        outputFile << "└── ";

    outputFile << root->iPayload << endl;

    TreeWriter(root->ptrLeft, outputFile, prefix + (isLeft ? "│   " : "    "), true);
    TreeWriter(root->ptrRight, outputFile, prefix + (isLeft ? "│   " : "    "), false);
}

//retorna o ponteiro para o nó folha de menor valor em uma árvore binária de busca
struct Node* lesserLeaf(struct Node* node)
{
    struct Node* ptrCurrent = node;
    
    while(ptrCurrent && ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;
    
    return ptrCurrent;
}

// retorna o tamanho de uma linked list. Usado para fazer o bubble sort da Link List
int lenght(NodeLinkedList* head)
{
    int cont = 1;
    NodeLinkedList* temp = head;
    while (temp -> ptrNext != nullptr)
    {
        temp = temp-> ptrNext;
        cont ++;
    }
    return cont;
}