/*****************

Root: Nó inicial de uma árvore
Child Node: Nó filho de outro nó
Parent: Nó pai de outro nó
Sibling: Nós com mesmo pai
Leaf Node: Nó sem filho
Ancestor Node: Qualquer nó atrás

******************/

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

void traversePreOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        cout << " " << ptrStartingNode -> iPayload;
        traversePreOrder(ptrStartingNode -> ptrLeft);
        traversePreOrder(ptrStartingNode -> ptrRight);
    }
}

void traverseInOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traverseInOrder(ptrStartingNode -> ptrLeft);
        cout << " " << ptrStartingNode -> iPayload;
        traverseInOrder(ptrStartingNode -> ptrRight);
    }
}

void traversePostOrder(struct Node* ptrStartingNode)
{
    if(ptrStartingNode != nullptr)
    {
        traversePostOrder(ptrStartingNode -> ptrLeft);
        traversePostOrder(ptrStartingNode -> ptrRight);
        cout << " " << ptrStartingNode -> iPayload;
    }
}

struct Node* searchNode(struct Node* node, int iData)
{
    if(node == nullptr) return nullptr;
    else if(iData == node -> iPayload) return node;
    else if(iData < node -> iPayload) return searchNode(node -> ptrLeft, iData);
    else return searchNode(node -> ptrRight, iData);

}

struct Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr) return newNode(iData);
    
    if(iData < node -> iPayload) node -> ptrLeft = insertNode(node -> ptrLeft, iData);
    
    else node -> ptrRight = insertNode(node -> ptrRight, iData);
    
    return node;
}

struct Node* lesserLeaf(struct Node* node)
{
    struct Node* ptrCurrent = node;
    
    while(ptrCurrent && ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;
    
    return ptrCurrent;
}

struct Node* deleteNode(struct Node* node, int iData)
{
    if(node == nullptr) return node;
    
    if(iData < node -> iPayload) node -> ptrLeft = deleteNode(node -> ptrLeft, iData);
    
    else if(iData > node -> iPayload) node -> ptrRight = deleteNode(node -> ptrRight, iData);
    
    else
    {
        struct Node* ptrTemp = nullptr;
        
        if(node->ptrLeft == nullptr)
        {
            ptrTemp = node->ptrRight;
            free(node);
            
            return ptrTemp;
        }
        
        else if(node->ptrRight == nullptr)
        {
            ptrTemp = node->ptrLeft;
            free(node);
            
            return ptrTemp;
        }
        
        else
        {
            ptrTemp = lesserLeaf(node -> ptrRight);
            
            struct Node* leftTemp = node -> ptrLeft;
            node -> ptrLeft = nullptr;
            
            struct Node* rightTemp = node -> ptrRight;
            node -> ptrRight = nullptr;
            
            insertNode(node, ptrTemp -> iPayload);
            
            struct Node* newTree = deleteNode(node, iData);
            
            newTree -> ptrRight = deleteNode(rightTemp, ptrTemp -> iPayload);
            newTree -> ptrLeft = leftTemp;
            
            return newTree;
        }
    }
    
    return node;
}

int main()
{
    struct Node* root = newNode(42);
    root -> ptrLeft = newNode(7);
    root -> ptrRight = newNode(666);
    root -> ptrLeft -> ptrLeft = newNode(1);
    root -> ptrLeft -> ptrRight = newNode(13);

    cout << "Atravessando a árvore - PreOrder:";
    traversePreOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - InOrder:";
    traverseInOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - PostOrder:";
    traversePostOrder(root);
    cout << endl;

    string resultado;

    resultado = (nullptr == searchNode(nullptr, 42))? "OK":"Deu ruim";
    cout << "Busca nullptr: " << resultado << endl;

    resultado = (root == searchNode(root, 57))? "OK":"Deu ruim";
    cout << "Busca 42: " << resultado << endl;

    resultado = (root -> ptrLeft == searchNode(root, 7))? "OK":"Deu ruim";
    cout << "Busca 7: " << resultado << endl;

    resultado = (root -> ptrLeft -> ptrLeft == searchNode(root, 1))? "OK":"Deu ruim";
    cout << "Busca 1: " << resultado << endl;

    resultado = (nullptr == searchNode(root, 10))? "OK":"Deu ruim";
    cout << "Busca Não-Existente: " << resultado << endl;
    
    //aula
    root = nullptr;
    root = insertNode(root, 42);
    root = insertNode(root, 7);
    root = insertNode(root, 666);
    root = insertNode(root, 1);
    root = insertNode(root, 13);
    root = insertNode(root, 111);
    root = insertNode(root, 110);
    root = insertNode(root, 90);

    cout << "Atravessando a árvore - PreOrder:";
    traversePreOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - InOrder:";
    traverseInOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - PostOrder:";
    traversePostOrder(root);
    cout << endl;
    
    //Deletar Nós
    
    root = deleteNode(root, 42);
    
    cout << "Atravessando a árvore - PreOrder:";
    traversePreOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - InOrder:";
    traverseInOrder(root);
    cout << endl;

    cout << "Atravessando a árvore - PostOrder:";
    traversePostOrder(root);
    cout << endl;
    
    return 0;
}




