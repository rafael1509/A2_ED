#include "../include/helper.h"
#include <iostream>

/**
 * Escreve uma representação visual da árvore no arquivo de saída.
 *
 * @param root Ponteiro para o nó raiz da árvore.
 * @param outputFile Arquivo de saída onde a representação da árvore será escrita.
 * @param prefix Prefixo usado para a formatação visual da árvore.
 * @param isLeft Indica se o nó atual é filho esquerdo de seu pai.
 */
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

/**
 * Encontra a menor folha de uma determinada árvore.
 *
 * @param node Ponteiro para a root da árvore a ser feita a busca.
 * @return Ponteiro para a menor folha encontrada.
 */
struct Node* lesserLeaf(struct Node* node)
{
    struct Node* ptrCurrent = node;
    
    while(ptrCurrent && ptrCurrent -> ptrLeft != nullptr) ptrCurrent = ptrCurrent -> ptrLeft;
    
    return ptrCurrent;
}

/**
 * Converte uma árvore em uma lista encadeada.
 *
 * @param root Ponteiro para a root da árvore a ser convertida.
 * @return Ponteiro para a lista encadeada resultante da conversão.
 */
NodeLinkedList* ConvertTreeToList(Node* root) 
{
    if (root == nullptr) {
        return nullptr;
    }

    NodeLinkedList* head = new NodeLinkedList();
    head-> iPayload = root-> iPayload;
    head-> ptrNext = nullptr;

    NodeLinkedList* ptrTail = head;

    NodeLinkedList* leftList = ConvertTreeToList(root -> ptrLeft);
    if (leftList != nullptr) {
        ptrTail -> ptrNext = leftList;
        while (ptrTail-> ptrNext != nullptr) {
            ptrTail = ptrTail -> ptrNext;
        }
    }

    NodeLinkedList* rightList = ConvertTreeToList(root-> ptrRight);
    if (rightList != nullptr) {
        ptrTail->ptrNext = rightList;
    }

    return head;
}

/**
 * Informa o tamanho de uma determinada lista encadeada.
 *
 * @param head Ponteiro para a head da lista encadeada.
 * @return count O tamanho dessa lista encadeada.
 */
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

/**
 * Printa todos os elementos de uma determinada lista encadeada.
 *
 * @param head Ponteiro para a head da lista encadeada.
 */
void PrintLinkedList(NodeLinkedList* head) 
{
    NodeLinkedList* current = head;
    while (current != nullptr) {
        cout << current->iPayload << " ";
        current = current->ptrNext;
    }
    cout << endl;
}

