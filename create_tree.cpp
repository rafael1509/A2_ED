#include <iostream>
#include <fstream>
#include <exception>

using namespace std;

struct Node
{
    int iPayload;
    struct Node* ptrLeft;
    struct Node* ptrRight;
};

struct Node* newNode(int iData)
{
     struct Node* newNode = new Node;
    newNode -> iPayload = iData;
    newNode -> ptrLeft = nullptr;
    newNode -> ptrRight = nullptr;

    return newNode;
};

struct Node* insertNode(struct Node* node, int iData)
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

int rec[1000006];
void printTree(struct Node* curr,int depth)
{
    int i;
    if(curr == nullptr)
        return;
    
    printf("\t");
    for(i = 0; i < depth; i++)
        if(i == depth - 1)
            printf("%s---", rec[depth - 1] ? "| " : "");
        else
            printf("%s   ", rec[i] ? "| " : " ");
    printf("%d\n", curr->iPayload);
    rec[depth] = 1;
    printTree(curr->ptrLeft, depth + 1);
    rec[depth] = 0;
    printTree(curr->ptrRight, depth + 1);
}



int main()
{
    struct Node* root = nullptr;

    //root = createByUser();

    root = createByTextFile("C:/Users/rafae/OneDrive/Documentos/prog/coding_C++/A2_ED/tree_1.txt");

    printTree(root, 1);
}
