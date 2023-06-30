#include "../include/tree.h"
#include <iostream>
#include <fstream>
#include <cmath>

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

NodeLinkedList* treeToLinkedList(Node* head)
{
    NodeLinkedList* headLL  = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    NodeLinkedList* headLL2  = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    NodeLinkedList* headLL3  = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    headLL -> iPayload = 2;
    headLL2 -> iPayload = 1;
    headLL3 -> iPayload = 3;
    headLL -> ptrNext = headLL2;
    headLL2 -> ptrNext = headLL3;
    headLL3 -> ptrNext = nullptr;
}

bool isPerfect(Node* head)
{
    NodeLinkedList* headLL = treeToLinkedList(head);
    int iNumNos = lenght(headLL);
    int iAltura = altura(head);
    cout << "altura: " << iAltura <<endl;
    cout << "nos: " << iNumNos <<endl;
    if (iNumNos == pow(2, iAltura) - 1)
        return true;
    return false;
}

bool isComplete(Node* head)
{
    NodeLinkedList* headLL = treeToLinkedList(head);
    int iNumNos = lenght(headLL);
    int iAltura = altura(head);
    if (iNumNos >= pow(2, iAltura -1) and iNumNos <= pow(2, iAltura) - 1)
        return true;
    return false;    
}

// ordena linked lists
void BubbleSort(NodeLinkedList** head)
{
    int len = lenght((*head)) + 1; // +1 pois estamos acrescentando um nó no inicio
    NodeLinkedList* novoHead = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    novoHead -> ptrNext = (*head);
    for (int i = len-2; i > 0; i--) // o for para no antepenultimo nó
    {
        NodeLinkedList* current = novoHead;
        for (int j = 0; j<i; j++)
        {
            if (current -> ptrNext-> iPayload > current -> ptrNext -> ptrNext -> iPayload) // temos o no 1 3 2 4, e queremos deixar 1 3 2 4. current é o 1
            {
                NodeLinkedList* aux = current -> ptrNext; //aux guarda o 3
                current -> ptrNext = aux -> ptrNext; // 1 -> 2
                NodeLinkedList* aux2 = current -> ptrNext -> ptrNext; // guarda o 4
                current -> ptrNext -> ptrNext = aux; // 2 -> 3
                aux -> ptrNext = aux2;
            }
        current = current -> ptrNext;
        }
    }
    *head = novoHead-> ptrNext;
    free(novoHead);
}