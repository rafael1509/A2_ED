#include <iostream>

    using namespace std;

struct sNode {
    int nValue;
    sNode* pLeft;
    sNode* pRight;
};


struct sListNode {
    int nValue;
    sListNode* pNext;
};


sListNode* ConvertTreeToList(sNode* pRoot) {
    if (pRoot == nullptr) {
        return nullptr;
    }

    sListNode* pHead = new sListNode();
    pHead->nValue = pRoot->nValue;
    pHead->pNext = nullptr;

    sListNode* pTail = pHead;

    sListNode* pLeftList = ConvertTreeToList(pRoot->pLeft);
    if (pLeftList != nullptr) {
        pTail->pNext = pLeftList;
        while (pTail->pNext != nullptr) {
            pTail = pTail->pNext;
        }
    }

    sListNode* pRightList = ConvertTreeToList(pRoot->pRight);
    if (pRightList != nullptr) {
        pTail->pNext = pRightList;
    }

    return pHead;
}

void PrintLinkedList(sListNode* pHead) {
    sListNode* pCurrent = pHead;
    while (pCurrent != nullptr) {
        cout << pCurrent->nValue << " ";
        pCurrent = pCurrent->pNext;
    }
    cout << endl;
}

int main() {

    sNode* pRoot = new sNode();
    pRoot->nValue = 1;

    sNode* pNode1 = new sNode();
    pNode1->nValue = 2;

    sNode* pNode2 = new sNode();
    pNode2->nValue = 3;

    pRoot->pLeft = pNode1;
    pRoot->pRight = pNode2;

    sNode* pNode3 = new sNode();
    pNode3->nValue = 4;

    sNode* pNode4 = new sNode();
    pNode4->nValue = 5;

    pNode1->pLeft = pNode3;
    pNode1->pRight = pNode4;


    sListNode* pLinkedList = ConvertTreeToList(pRoot);


    PrintLinkedList(pLinkedList);


    delete pNode4;
    delete pNode3;
    delete pNode2;
    delete pNode1;
    delete pRoot;


    sListNode* pCurrent = pLinkedList;
    while (pCurrent != nullptr) {
        sListNode* pTemp = pCurrent;
        pCurrent = pCurrent->pNext;
        delete pTemp;
    }

    return 0;
}

