#include "include/tree.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    struct Node* root = nullptr;
    int iInput = -2;

    while (iInput != -1)
    {
        if (iInput == -2)
        {
            cout << "=====================================================" << endl;
            cout << "Explorador de árvores" <<endl;
            cout << "Opções:" << endl;
            cout << "[0] construção de uma árvore binária de busca a partir de um arquivo de texto" << endl;
            cout << "[1] construção de uma árvore binária de busca a partir de dados digitados pelo usuário" <<endl;
            cout << "[-1] sair" << endl;
            cout << "=====================================================" << endl;
            cin >> iInput;
        }

        else if (iInput == 0)
        {
            string strFileName = "";
            cout << "Informe o file path: ";
            cin >> strFileName;
            root = createByTextFile(strFileName);
            iInput = -3;
        }

        else if (iInput == 1)
        {
            root = createByUser();
            iInput = -3;
        }

        else if (iInput == -3)
        {
            cout << "=====================================================" << endl;
            cout << "Opções de Ações para sua árvore" <<endl;
            cout << "[2] informar a altura da árvore" <<endl;
            cout << "[3] inserção de um elemento fornecido pelo usuário" <<endl;
            cout << "[4] remoção de um elemento fornecido pelo usuário" <<endl;
            cout << "[5] busca do endereço de memória de um elemento fornecido pelo usuário" <<endl;
            cout << "[6] representação gráfica da ordenação" << endl;
            cout << "[7] verifica se a árvore é perfeita" << endl;
            cout << "[8] verifica se a árvore é completa" << endl;
            cout << "[9] converte a árvore em uma lista e ordena com bubble sort" << endl;
            cout << "[10] converte a árvore em uma lista e ordena com insertion sort" << endl;
            cout << "[11] converte a árvore em uma lista e ordena com selection sort" << endl;
            cout << "[12] converte a árvore em uma lista e ordena com shell sort" << endl;
            cout << "[13] Representação gráfica da ordenação com Bubble sort" << endl;
            cout << "[14] Representação gráfica da ordenação com Insertion sort" << endl;
            cout << "[15] Representação gráfica da ordenação com Selection sort" << endl;
            cout << "[16] Representação gráfica da ordenação com Shell sort" << endl;

            cout << "[-1] sair" << endl;
            cout << "[-2] Voltar ao menu inicial e criar uma nova árvore" << endl;
            cout << "=====================================================" << endl;
            cin >> iInput;
        }

        else if (iInput == 2)
        {
            clock_t start = clock();
            cout << "Altura da árvore: " << calcAltura(root) << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 3)
        {
            clock_t start = clock();
            int iValor = 0;
            cout << "Informe um valor para adicionar na árvore: ";
            cin >> iValor;
            insertNode(root, iValor);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }
        
        else if (iInput == 4)
        {
            clock_t start = clock();
            int iValor = 0;
            cout << "Informe um valor para remover da árvore: ";
            cin >> iValor;
            deleteNode(root, iValor);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 5)
        {
            clock_t start = clock();
            int iValor = 0;
            cout << "Informe um valor para buscar seu endereço de memória na árvore: ";
            cin >> iValor;
            cout << "Posição de " << iValor << ": " << searchNode(root, iValor);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }
        
        else if (iInput == 6)
        {
            clock_t start = clock();
            printTree(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 7)
        {
            clock_t start = clock();
            if (isPerfect(root))
                cout << "A árvore é perfeita" << endl;
            else
                cout << "A árvore não é perfeita" << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 8)
        {
            clock_t start = clock();
            if (isComplete(root))
                cout << "A árvore é completa" << endl;
            else
                cout << "A árvore não é completa" << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 9)
        {
            clock_t start = clock();
            BubbleSort(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;

        }

        else if(iInput == 10)
        {
            clock_t start = clock();
            NodeLinkedList* aux = ConvertTreeToList(root);
            NodeLinkedList** head = &aux;
            insertionSort(head);
            cout << "A árvore foi convertida em lista encadeada e organizada com Insertion sort: \n";
            PrintLinkedList((*head));
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 11)
        {
            clock_t start = clock();
            selectionSort(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 12)
        {
            clock_t start = clock();
            NodeLinkedList* aux = ConvertTreeToList(root);
            NodeLinkedList** head = &aux;
            shellSort(head);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 13)
        {
            BubbleSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 14)
        {
            insertionSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 15)
        {
            selectionSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 16)
        {
            ShellSortRepresentation(root);
            iInput = -3;
        }
    }
    cout << "programa finalizado com sucesso";
}