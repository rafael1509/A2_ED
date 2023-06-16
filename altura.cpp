#include <iostream>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int iData)
{
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
};

struct Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr) return newNode(iData);
    
    if(iData < node -> iPayload) node -> ptrLeft = insertNode(node -> ptrLeft, iData);
    
    else node -> ptrRight = insertNode(node -> ptrRight, iData);
    
    return node;
}

int altura(struct Node* node)
{
  int iAltura = 0;
  if(node != nullptr)
  {
    int iAlturaL = altura(node -> ptrLeft);
    int iAlturaR = altura(node -> ptrRight);
    int iMaxAltura = max(iAlturaL, iAlturaR);
    iAltura = iMaxAltura + 1;
  }
  return iAltura;
}

int main()
{
    Node* root = nullptr;
    root = insertNode(root, 42);
    root = insertNode(root, 7);
    root = insertNode(root, 666);
    root = insertNode(root, 1);
    root = insertNode(root, 13);
    root = insertNode(root, 111);
    root = insertNode(root, 110);
    root = insertNode(root, 90);
    
    cout << altura(root);
    
    return 0;
}