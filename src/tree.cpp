#include "../include/tree.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;
/**
 * Cria um novo nó a partir de um int determinado.
 *
 * @param iData Inteiro que o novo nó vai armazenar.
 * @return Ponteiro para o novo nó criado.
 */
Node* newNode(int iData)
{
    struct Node* newNode = new Node;
    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
};

/**
 * Insere um nó com o valor de um inteiro em uma árvore.
 *
 * @param node Ponteiro para a root da árvore.
 * @param iData Inteiro que o novo nó vai armazenar.
 * @return Ponteiro para o nó inicial.
 */
Node* insertNode(struct Node* node, int iData)
{
    if(node == nullptr) return newNode(iData);
    
    if(iData < node -> iPayload) node -> ptrLeft = insertNode(node -> ptrLeft, iData);
    
    else node -> ptrRight = insertNode(node -> ptrRight, iData);
    
    return node;
}

/**
 * Cria uma árvore a partir de números digitados pelo usuário.
 *
 * @param None
 * @return Ponteiro para o root da árvore gerada.
 */
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

/**
 * Cria uma árvore a partir de um arquivo de texto.
 *
 * @param strFileName Arquivo de texto usado para criar a árvore.
 * @return Ponteiro para o root da árvore gerada.
 */
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

/**
 * Faz a vizualização de uma árvore.
 *
 * @param root Ponteiro para a root da árvore a ser vizualizada.
 */
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

/**
 * Informa qual a altura de uma determinada árvore.
 *
 * @param node Ponteiro para a root da árvore a ser utilizada.
 * @return Inteiro que informa a altura da árvore.
 */
int calcAltura(struct Node* node)
{
  int iAltura = 0;
  if(node != nullptr)
  {
    int iAlturaL = calcAltura(node -> ptrLeft);
    int iAlturaR = calcAltura(node -> ptrRight);
    int iMaxAltura = max(iAlturaL, iAlturaR);
    iAltura = iMaxAltura + 1;
  }
  return iAltura;
}

/**
 * Deleta um determinado nó de uma determinada árvore.
 *
 * @param node Ponteiro para a root da árvore a ser utilizada.
 * @param iData Inteiro correspondente ao nó a ser deletado.
 * @return Ponteiro para o root dessa árvore com o nó deletado.
 */
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

/**
 * Encontra um nó em uma determinada árvore.
 *
 * @param node Ponteiro para a root da árvore a ser utilizada.
 * @param iData Inteiro correspondente ao nó a ser procurado.
 * @return Ponteiro para o nó na árvore.
 */
Node* searchNode(struct Node* node, int iData)
{
    if(node == nullptr) return nullptr;
    else if(iData == node -> iPayload) return node;
    else if(iData < node -> iPayload) return searchNode(node -> ptrLeft, iData);
    else return searchNode(node -> ptrRight, iData);

}

/**
 * Avalia se uma determinada árvore é perfeita.
 *
 * @param head Ponteiro para a root da árvore a ser avaliada.
 * @return Booleano informando se a árvore é perfeita.
 */
bool isPerfect(Node* head)
{
    NodeLinkedList* headLL = ConvertTreeToList(head);
    int iNumNos = lenght(headLL);
    int iAltura = calcAltura(head);
    if (iNumNos == pow(2, iAltura) - 1)
        return true;
    return false;
}

/**
 * Avalia se uma determinada árvore é completa.
 *
 * @param head Ponteiro para a root da árvore a ser avaliada.
 * @return Booleano informando se a árvore é completa.
 */
bool isComplete(Node* head)
{
    NodeLinkedList* headLL = ConvertTreeToList(head);
    int iNumNos = lenght(headLL);
    int iAltura = calcAltura(head);
    if (iNumNos >= pow(2, iAltura -1) and iNumNos <= pow(2, iAltura) - 1)
        return true;
    return false;    
}

/**
 * Ordena uma árvore convertida para lista encadeada usando o algoritmo Bubble Sort.
 *
 * @param root Ponteiro para a root da árvore.
 */
void BubbleSort(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;
    
    int iLen = lenght((*head)) + 1; // +1 pois estamos acrescentando um nó no inicio
    NodeLinkedList* novoHead = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    novoHead -> ptrNext = (*head);
    for (int i = iLen-2; i > 0; i--) // o for para no antepenultimo nó
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
 * @param head Ponteiro para o primeiro item da lista encadeada
 */
void insertionSort(NodeLinkedList** head)
{
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
}

/**
 * Ordena uma lista encadeada usando o algoritmo Selection Sort.
 *
 * @param root Ponteiro para a root da árvore.
 */
void selectionSort(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;

    struct NodeLinkedList* temp = *head;
  
    while (temp != nullptr) //Passo por todos os nós da lista
    {
        struct NodeLinkedList* min = temp;
        struct NodeLinkedList* r = temp -> ptrNext;
        
        while (r != nullptr) //Verifico qual o mínimo a partir do nó que estou olhando
        {
            if (min -> iPayload > r -> iPayload) min = r;
            r = r -> ptrNext;
        }
        swapNodes(head, temp->iPayload, min->iPayload); //Chamo a troca de nós entre o nó que estou e o mínimo encontrado
        temp = min->ptrNext; //Redireciono o nó que vou olhar
    }
    cout << "A árvore foi convertida em lista encadeada e organizada com Selection sort: \n";
    PrintLinkedList((*head));
}

/**
 * Ordena uma lista encadeada usando o algoritmo Shell Sort.
 *
 * @param head Ponteiro para o primeiro item da lista encadeada
 */
void shellSort(NodeLinkedList** head) 
{
    int iSize = lenght(*head);
    int iGap = iSize / 2;

    while (iGap > 0) {
        for (int i = 0; i < iGap; i++) {
            NodeLinkedList* sublistHead = nullptr;
            NodeLinkedList* current = *head;
            int iSublistIndex = 0;

            while (current != nullptr) {
                if (iSublistIndex % iGap == i) {
                    insertAtBeginning(sublistHead, current->iPayload);
                }
                current = current->ptrNext;
                iSublistIndex++;
            }

            insertionSort(&sublistHead);

            current = *head;
            iSublistIndex = 0;
            while (current != nullptr) {
                if (iSublistIndex % iGap == i) {
                    current->iPayload = sublistHead->iPayload;
                    sublistHead = sublistHead->ptrNext;
                }
                current = current->ptrNext;
                iSublistIndex++;
            }

            while (sublistHead != nullptr) {
                NodeLinkedList* temp = sublistHead;
                sublistHead = sublistHead->ptrNext;
                delete temp;
            }
        }
        iGap /= 2;
    }
    cout << "A árvore foi convertida em lista encadeada e organizada com shell sort: \n";
    PrintLinkedList((*head));
}

/**
 * Ordena uma árvore convertida para lista encadeada usando o algoritmo Bubble Sort.
 *
 * @param root Ponteiro para a root da árvore.
 */
void BubbleSortRepresentation(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;
    
    int iLen = lenght((*head)) + 1; // +1 pois estamos acrescentando um nó no inicio
    NodeLinkedList* novoHead = (NodeLinkedList*)malloc(sizeof(NodeLinkedList));
    novoHead -> ptrNext = (*head);
    for (int i = iLen-2; i > 0; i--) // o for para no antepenultimo nó
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
                system("cls");
                system("cls");  // Limpa a tela do console (funciona no Windows)
                cout <<"Bubble Sort: " << endl;
                displaySort(novoHead->ptrNext);
                this_thread::sleep_for(chrono::milliseconds(500));  // Atraso em milissegundos
            }
        current = current -> ptrNext;
        }
    }
    *head = novoHead-> ptrNext;
    free(novoHead);
}

void insertionSortRepresentation(Node* root) 
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList* head = aux;

    NodeLinkedList* sorted = nullptr;
    NodeLinkedList* current = head;

    while (current != nullptr) {
        NodeLinkedList* nextNode = current->ptrNext;

        if (sorted == nullptr || current->iPayload < sorted->iPayload) 
        {
            current->ptrNext = sorted;
            sorted = current;
        } 
        else 
        {
            NodeLinkedList* temp = sorted;
            while (temp->ptrNext != nullptr && temp->ptrNext->iPayload < current->iPayload) 
            {
                temp = temp->ptrNext;
            }
            current->ptrNext = temp->ptrNext;
            temp->ptrNext = current;
        }

        current = nextNode;

        system("cls");
        system("cls");  // Limpa a tela do console (funciona no Windows)
        cout << "Insertion Sort: " << endl;
        cout << "Antiga Lista: " << endl;
        displaySort(current);
        cout << endl;
        cout << "Lista organizada: " << endl;
        displaySort(sorted);
        this_thread::sleep_for(chrono::milliseconds(500));  // Atraso em milissegundos
    }

    head = sorted;
}

void selectionSortRepresentation(Node* root)
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;

    struct NodeLinkedList* temp = *head;
  
    while (temp != nullptr) //Passo por todos os nós da lista
    {
        struct NodeLinkedList* min = temp;
        struct NodeLinkedList* r = temp -> ptrNext;
        
        while (r != nullptr) //Verifico qual o mínimo a partir do nó que estou olhando
        {
            if (min -> iPayload > r -> iPayload) min = r;
            r = r -> ptrNext;
        }
        swapNodes(head, temp->iPayload, min->iPayload); //Chamo a troca de nós entre o nó que estou e o mínimo encontrado
        temp = min->ptrNext; //Redireciono o nó que vou olhar
        system("cls");
        system("cls");  // Limpa a tela do console (funciona no Windows)
        cout << "Selection Sort: " << endl;
        displaySort(*head);
        this_thread::sleep_for(chrono::milliseconds(500));  // Atraso em milissegundos
    }
}

void ShellSortRepresentation(Node* root) 
{
    NodeLinkedList* aux = ConvertTreeToList(root);
    NodeLinkedList** head = &aux;
    
    int iLen = 0;
    NodeLinkedList* current = *head;
    while (current != nullptr) {
        iLen++;
        current = current->ptrNext;
    }
    iLen++; // +1 pois estamos acrescentando um nó no início

    NodeLinkedList* novoHead = new NodeLinkedList();
    novoHead->ptrNext = *head;

    for (int gap = iLen / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < iLen; i++) {
            NodeLinkedList* current = novoHead;
            for (int j = 0; j < i; j++) {
                current = current->ptrNext;
            }
            NodeLinkedList* temp = current->ptrNext;
            while (temp != nullptr && temp->ptrNext != nullptr && temp->iPayload > temp->ptrNext->iPayload) {
                NodeLinkedList* aux = temp->ptrNext;
                temp->ptrNext = aux->ptrNext;
                aux->ptrNext = temp;
                current->ptrNext = aux;

                system("cls");
                system("cls");  // Limpa a tela do console (funciona no Windows)
                cout << "Shell Sort: " << endl;
                displaySort(novoHead->ptrNext);
                cout << endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(500));  // Atraso em milissegundos

                temp = current->ptrNext;
                current = current->ptrNext;
            }
        }
    }

    *head = novoHead->ptrNext;
    delete novoHead;
}