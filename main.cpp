#include "tree.h"

int main()
{
    struct Node* root = nullptr;

    // root = createByUser();

    root = createByTextFile("C:/Users/rafae/OneDrive/Documentos/prog/coding_C++/A2_ED/A2_ED/tree_1.txt");

    printTree(root);
}