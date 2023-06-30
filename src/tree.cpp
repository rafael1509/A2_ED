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

bool isPerfect(Node* head)
{
    NodeLinkedList* headLL = ConvertTreeToList(head);
    int iNumNos = lenght(headLL);
    int iAltura = altura(head);
    if (iNumNos == pow(2, iAltura) - 1)
        return true;
    return false;
}

bool isComplete(Node* head)
{
    NodeLinkedList* headLL = ConvertTreeToList(head);
    int iNumNos = lenght(headLL);
    int iAltura = altura(head);
    if (iNumNos >= pow(2, iAltura -1) and iNumNos <= pow(2, iAltura) - 1)
        return true;
    return false;    
}

// converte a árvore em uma lista e ordena com bubble sort
void BubbleSort(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;
    
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

    cout << "A árvore foi convertida em lista encadeada e organizada com bubble sort: \n";
    PrintLinkedList((*head));
}

/**
 * Ordena uma lista encadeada usando o algoritmo Insertion Sort.
 *
 * @param root Ponteiro para a root da árvore.
 */
void insertionSort(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;

    NodeLinkedList* sorted = nullptr;
    NodeLinkedList* current = *head;

    while (current != nullptr) 
    {
        NodeLinkedList* next = current->ptrNext; // Armazena o próximo nó da lista original

        //Usaremos uma nova linked list sorted
        //Caso o valor atual seja menor que o valor inicial da lista sorted
        //Ou caso a lista esteja vazia sorted
        if (sorted == nullptr || current->iPayload < sorted->iPayload) 
        {
            // O nó atual é o primeiro nó da lista ordenada
            current->ptrNext = sorted;
            sorted = current;
        } 
        else 
        {
            NodeLinkedList* ptr = sorted;
            //Verifica se há algum valor maior que o current na lista sorted para fazer a ordenação
            while (ptr->ptrNext != nullptr && ptr->ptrNext->iPayload < current->iPayload)
                ptr = ptr->ptrNext;
            // Insere o nó atual na posição correta da lista sorted
            current->ptrNext = ptr->ptrNext;
            ptr->ptrNext = current;
        }

        current = next; // Atualiza o ponteiro da cabeça para apontar para a lista ordenada
    }

    *head = sorted; //atualiza a head lista original como a head da sorted list
    cout << "A árvore foi convertida em lista encadeada e organizada com insertion sort: \n";
    PrintLinkedList((*head));
}

void shellSort(Node* root) 
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;
    
    int n = 0;
    NodeLinkedList* current = *head;

    //Computaremos o tamanho da lista (n) encadeada e usaremos para determinar o tamanho do primeiro gap
    while (current != nullptr) 
    {
        current = current->ptrNext;
        n++;
    }

    //Usaremos gaps de tamanho inicial n/2 (tamanho da lista/2) e vamos diminuir o gap pela metade até 1
    for (int gap = n / 2; gap > 0; gap /= 2) 
    {
        // Percorre a lista a partir do gap até o final
        for (int i = gap; i < n; i++) {
            int temp = 0;

            // Encontra o elemento na posição i
            NodeLinkedList* ptr = *head;

            for (int j = 0; j < i; j++) 
            {
                ptr = ptr->ptrNext;
            }
            temp = ptr->iPayload;

            // Encontra o elemento anterior ao elemento na posição i - gap
            NodeLinkedList* prev = nullptr;
            NodeLinkedList* current = *head;
            for (int j = 0; j < i - gap; j++) 
            {
                prev = current;
                current = current->ptrNext;
            }

            // Realiza a inserção por comparação até que o elemento atual seja menor que o elemento temporário
            while (prev != nullptr && current->iPayload > temp) 
            {
                prev->ptrNext = current->ptrNext;
                current->ptrNext = ptr->ptrNext;
                ptr->ptrNext = current;

                current = prev->ptrNext;
                prev = prev->ptrNext;
            }
        }
    }
    cout << "A árvore foi convertida em lista encadeada e organizada com shell sort: \n";
    PrintLinkedList((*head));
}
