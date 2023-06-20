#include "../include/tree.h"
#include "helper.cpp"
#include <iostream>
#include <fstream>

using namespace std;

Node* newNode(int iData)
{
    struct Node* newNode = new Node;
    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
};

Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr) return newNode(iData);
    
    if(iData < node -> iPayload) node -> ptrLeft = insertNode(node -> ptrLeft, iData);
    
    else node -> ptrRight = insertNode(node -> ptrRight, iData);
    
    return node;
}

Node* createByUser()
{
    struct Node* root = nullptr;
    int iNum = 0;

    while (true)
    {
        cout << "Digite um valor para adicionar na árvore: (-1 para parar)";
        cin >> iNum;

        if (iNum == -1)
            break;

        root = insertNode(root, iNum);
    }
    return root;
}

Node* createByTextFile(string strFileName)
{
    ifstream arquivo(strFileName);

    struct Node* root = nullptr;

    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        return root;
    }

    string linha =  "";
    while (getline(arquivo, linha))
    {
        try
        {
            root = insertNode(root, stoi(linha));
        }
        catch(const exception& e)
        {
            cerr << "Termo inválido para ser adicionado na árvore" << e.what() << endl;
            break;
        }
    }

    arquivo.close();
    return root;
}

void printTree(Node* root)
{
    ofstream outputFile("output/tree_visualization.txt");

    if (!outputFile.is_open())
    {
        cout << "Erro ao abrir o arquivo" << endl;
        return;
    }

    TreeWriter(root, outputFile, "", true);

    outputFile.close();
    cout << "Visualização salva em: 'output/tree_visualization.txt'" << endl;
}

int height(struct Node* node)
{
  int iHeight = 0;
  if(node != nullptr)
  {
    int iHeightL = height(node -> ptrLeft);
    int iHeightR = height(node -> ptrRight);
    int iMaxHeight = max(iHeightL, iHeightR);
    iHeight = iMaxHeight + 1;
  }
  return iHeight;
}

Node* deleteNode(struct Node* node, int iData)
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

Node* searchNode(struct Node* node, int iData)
{
    if(node == nullptr) return nullptr;
    else if(iData == node -> iPayload) return node;
    else if(iData < node -> iPayload) return searchNode(node -> ptrLeft, iData);
    else return searchNode(node -> ptrRight, iData);
}

bool isCompleteUtil(Node* root, int level, int height) 
{
    if (root == nullptr)
        return true;

    if (level == height - 1) {
        if (root->ptrLeft == nullptr && root->ptrRight != nullptr)
            return false;
        else if (root->ptrLeft != nullptr && root->ptrRight == nullptr)
            return true;
        else if (root->ptrLeft == nullptr && root->ptrRight == nullptr)
            return true;
    }

    if (level < height - 1) {
        bool leftSubtree = isCompleteUtil(root->ptrLeft, level + 1, height);
        bool rightSubtree = isCompleteUtil(root->ptrRight, level + 1, height);

        return leftSubtree && rightSubtree;
    }
    
    return false;
}

bool isCompleteTree(Node* root) 
{
    int treeHeight = height(root);
    return isCompleteUtil(root, 0, treeHeight);
}
