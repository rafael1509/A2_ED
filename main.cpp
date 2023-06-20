#include "include/tree.h"
#include "src/tree.cpp"
#include <iostream>

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
        cout << "[7] Informar se árvore é completa" << endl;
        cout << "[-1] sair" << endl;
        cin >> iInput;

        if (iInput == 0)
        {
            string strFileName = "";
            cout << "Informe o file path: ";
            cin >> strFileName;
            root = createByTextFile(strFileName);  // "C:/Users/rafae/OneDrive/Documentos/prog/coding_C++/A2_ED/A2_ED/tree_1.txt" 
        }    

        else if (iInput == 1)
            root = createByUser();

        else if (iInput == 2)
        {
            cout << "Altura da árvore: " << height(root);
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
            int iValor = 0;
            bool complete = isCompleteTree(root);
            if (complete == true)
            {
                cout << "A árvore é completa.";
            }
            else if (complete == false)
            {
                cout << "A árvore não é completa.";
            }
        }
    }
    cout << "programa finalizado com sucesso";
}