/**
 * Troca os nós que contêm os valores 'x' e 'y' em uma lista encadeada.
 * (Função para auxiliar o Selection Sort)
 *
 * @param head_ref Ponteiro para o ponteiro do início da lista encadeada.
 * @param x Valor do primeiro nó a ser trocado.
 * @param y Valor do segundo nó a ser trocado.
 */
void swapNodes(struct Node** head_ref, int x, int y)
{
    if (x == y) return; //Se os números forem iguais, não fará diferença trocá-los.
    
    struct Node* prevX = nullptr;
    struct Node* currX = *head_ref; //Começo a partir do início da lista para procurar o nó com o 'x' em data.
    while (currX && currX -> data != x)
    {
        prevX = currX;
        currX = currX->next;
    }
 
    struct Node* prevY = currX; 
    struct Node* currY = currX->next; //Começo a partir do currX->next para procurar o nó com o 'y' em data, pois já garanti que todos antes do currX são menores que ele.
    while (currY && currY->data != y) {
        prevY = currY;
        currY = currY->next;
    }

    if (prevX != NULL) prevX->next = currY; //Se o nó com 'x' não for o head
    
    else *head_ref = currY; //Se o nó com 'x' for o head
 
    if (prevY != NULL) prevY->next = currX; //Se o nó com 'y' não for o head
    
    else *head_ref = currX; //Se o nó com 'y' for o head
 
    struct Node* temp = currY->next;
    currY->next = currX->next;
    currX->next = temp;
}

/**
 * Ordena uma lista encadeada usando o algoritmo Selection Sort.
 *
 * @param root Ponteiro para a root da árvore.
 */
Node* selectionSort(Node** head)
{
    struct Node* temp = *head;
  
    while (temp != nullptr) //Passo por todos os nós da lista
    {
        struct Node* min = temp;
        struct Node* r = temp -> next;
        
        while (r != nullptr) //Verifico qual o mínimo a partir do nó que estou olhando
        {
            if (min -> data > r -> data) min = r;
            r = r -> next;
        }
        swapNodes(head, temp->data, min->data); //Chamo a troca de nós entre o nó que estou e o mínimo encontrado
        temp = min->next; //Redireciono o nó que vou olhar
    }
    return *head;
}
