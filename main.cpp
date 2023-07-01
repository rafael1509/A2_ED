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
            cout << "EXPLORADOR DE ARVORES" << endl;
            cout << "OPCOES:" << endl;
            cout << "[0] CONSTRUCAO DE UMA ARVORE BINARIA DE BUSCA A PARTIR DE UM ARQUIVO DE TEXTO" << endl;
            cout << "[1] CONSTRUCAO DE UMA ARVORE BINARIA DE BUSCA A PARTIR DE DADOS DIGITADOS PELO USUARIO" << endl;
            cout << "[-1] SAIR" << endl;
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
            cout << "OPCOES DE ACOES PARA SUA ARVORE" << endl;
            cout << "[2] INFORMAR A ALTURA DA ARVORE" << endl;
            cout << "[3] INSERCAO DE UM ELEMENTO FORNECIDO PELO USUARIO" << endl;
            cout << "[4] REMOCAO DE UM ELEMENTO FORNECIDO PELO USUARIO" << endl;
            cout << "[5] BUSCA DO ENDERECO DE MEMORIA DE UM ELEMENTO FORNECIDO PELO USUARIO" << endl;
            cout << "[6] REPRESENTACAO GRAFICA DA ARVORE" << endl;
            cout << "[7] EXIBICAO DA ARVORE UTILIZANDO BFS" << endl;
            cout << "[8] VERIFICA SE A ARVORE E PERFEITA" << endl;
            cout << "[9] VERIFICA SE A ARVORE E COMPLETA" << endl;
            cout << "[10] CONVERTE A ARVORE EM UMA LISTA E ORDENA COM BUBBLE SORT" << endl;
            cout << "[11] CONVERTE A ARVORE EM UMA LISTA E ORDENA COM INSERTION SORT" << endl;
            cout << "[12] CONVERTE A ARVORE EM UMA LISTA E ORDENA COM SELECTION SORT" << endl;
            cout << "[13] CONVERTE A ARVORE EM UMA LISTA E ORDENA COM SHELL SORT" << endl;
            cout << "[14] REPRESENTACAO GRAFICA DA ORDENACAO COM BUBBLE SORT" << endl;
            cout << "[15] REPRESENTACAO GRAFICA DA ORDENACAO COM INSERTION SORT" << endl;
            cout << "[16] REPRESENTACAO GRAFICA DA ORDENACAO COM SELECTION SORT" << endl;
            cout << "[17] REPRESENTACAO GRAFICA DA ORDENACAO COM SHELL SORT" << endl;

            cout << "[-1] SAIR" << endl;
            cout << "[-2] VOLTAR AO MENU INICIAL E CRIAR UMA NOVA ARVORE" << endl;
            cout << "=====================================================" << endl;

            cin >> iInput;
        }

        else if (iInput == 2)
        {
            clock_t start = clock();
            cout << "Altura da arvore: " << calcAltura(root) << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 3)
        {
            clock_t start = clock();
            int iValor = 0;
            cout << "Informe um valor para adicionar na arvore: ";
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
            cout << "Informe um valor para remover da arvore: ";
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
            cout << "Informe um valor para buscar seu endereco de memória na arvore: ";
            cin >> iValor;
            cout << "Posicao de " << iValor << ": " << searchNode(root, iValor) << endl;
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
            cout << "\nBFS:" << endl;
            BFS(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 8)
        {
            clock_t start = clock();
            if (isPerfect(root))
                cout << "A arvore e perfeita" << endl;
            else
                cout << "A arvore nao e perfeita" << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if (iInput == 9)
        {
            clock_t start = clock();
            if (isComplete(root))
                cout << "A arvore e completa" << endl;
            else
                cout << "A arvore nao e completa" << endl;
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 10)
        {
            clock_t start = clock();
            BubbleSort(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;

        }

        else if(iInput == 11)
        {
            clock_t start = clock();
            NodeLinkedList* aux = ConvertTreeToList(root);
            NodeLinkedList** head = &aux;
            insertionSort(head);
            cout << "A arvore foi convertida em lista encadeada e organizada com Insertion sort: \n";
            PrintLinkedList((*head));
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 12)
        {
            clock_t start = clock();
            selectionSort(root);
            clock_t end = clock();
            double elapsed_secs = double(end - start) / CLOCKS_PER_SEC;
            cout << "Tempo de processamento: " << elapsed_secs << " segundos" << endl;
            iInput = -3;
        }

        else if(iInput == 13)
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

        else if(iInput == 14)
        {
            BubbleSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 15)
        {
            insertionSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 16)
        {
            selectionSortRepresentation(root);
            iInput = -3;
        }

        else if(iInput == 17)
        {
            ShellSortRepresentation(root);
            iInput = -3;
        }
    }
    cout << "programa finalizado com sucesso";
}