#include <iostream>
#include <fstream>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

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

    //Pegar arquivos por espaços (A versão antiga separava por linhas)
    int number;
    while (arquivo >> number)
    {
        root = insertNode(root, number);
    }

    arquivo.close();
    return root;
}

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
    cout << "Visualização salva em: 'tree_visualization.txt'" << endl;
}

int main()
{
    struct Node* root = nullptr;

    // root = createByUser();

    root = createByTextFile("./tree_1.txt");

    printTree(root);
}