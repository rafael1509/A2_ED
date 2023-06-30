#include "include/tree.h"
#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    struct Node* root = nullptr;
    int iInput = 0;

    while (iInput != -1)
    {
        cout << "\n\nExplorador de árvores" <<endl;
        cout << "Opções:" << endl << "[0] construção de uma árvore binária de busca a partir de um arquivo de texto" << endl;
        cout << "[1] construção de uma árvore binária de busca a partir de dados digitados pelo usuário" <<endl;
        cout << "[2] informar a altura da árvore" <<endl;
        cout << "[3] inserção de um elemento fornecido pelo usuário" <<endl;
        cout << "[4] remoção de um elemento fornecido pelo usuário" <<endl;
        cout << "[5] busca do endereço de memória de um elemento fornecido pelo usuário" <<endl;
        cout << "[6] representação gráfica da ordenação" << endl;
        cout << "[7] verifica se a árvore é perfeita" << endl;
        cout << "[8] verifica se a árvore é completa" << endl;
        cout << "[9] converte a árvore em uma lista e ordena com bubble sort" << endl;
        cout << "[10] converte a árvore em uma lista e ordena com insertion sort" << endl;
        cout << "[11] converte a árvore em uma lista e ordena com shell sort" << endl;
        cout << "[12] Representação gráfica da ordenação com Bubble sort" << endl;

        cout << "[-1] sair" << endl;
        cin >> iInput;
        cout << "";

        clock_t start = clock();

        if (iInput == 0)
        {
            string strFileName = "";
            cout << "Informe o file path: ";
            cin >> strFileName;
            root = createByTextFile(strFileName);  // "C:/Users/rafae/OneDrive/Documentos/prog/coding_C++/A2_ED/tree_1.txt" 
        }    

        else if (iInput == 1)
            root = createByUser();

        else if (iInput == 2)
        {
            cout << "Altura da árvore: " << altura(root) << endl;
        }

        else if (iInput == 3)
        {
            int iValor = 0;
            cout << "Informe um valor para adicionar na árvore: ";
            cin >> iValor;
            insertNode(root, iValor);
        }
        
        else if (iInput == 4)
        {
            int iValor = 0;
            cout << "Informe um valor para remover da árvore: ";
            cin >> iValor;
            deleteNode(root, iValor);
        }

        else if (iInput == 5)
        {
            int iValor = 0;
            cout << "Informe um valor para buscar seu endereço de memória na árvore: ";
            cin >> iValor;
            cout << "Posição de " << iValor << ": " << searchNode(root, iValor);
        }
        
        else if (iInput == 6)
        {
            printTree(root);
        }

        else if (iInput == 7)
        {
            if (isPerfect(root))
                cout << "A árvore é perfeita" << endl;
            else
                cout << "A árvore não é perfeita" << endl;
        }

        else if (iInput == 8)
        {
            if (isComplete(root))
                cout << "A árvore é completa" << endl;
            else
                cout << "A árvore não é completa" << endl;
        }

        else if(iInput == 9)
        {
            BubbleSort(root);
        }

        else if(iInput == 10)
        {
            NodeLinkedList* aux = ConvertTreeToList(root);
            NodeLinkedList** head = &aux;
            insertionSort(head);
            cout << "A árvore foi convertida em lista encadeada e organizada com insertion sort: \n";
            PrintLinkedList((*head));
        }

        else if(iInput == 11)
        {
            shellSort(root);
        }

        else if(iInput == 12)
        {
            BubbleSortRepresentation(root);
        }

        clock_t end = clock();
        double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
        cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
    }
    cout << "programa finalizado com sucesso";
}