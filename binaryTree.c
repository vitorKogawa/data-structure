#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int value;
    struct node *left;
    struct node *right;
} Node;

//protótipos
Node *initialize();
Node *insert(Node *root, int value);
Node *search(Node *root, int value);
Node *smallerNode(Node *root);
Node *biggerNode(Node *root);
Node *delete(Node *root, int value);

int heightTree(Node *root);
int numberOfNodes(Node *root);
int numberOfSheets(Node *root);
void displayInOrder(Node *root);
void displayPreOrder(Node *root);
void displayPosOrder(Node *root);
int bigger(int a, int b);
void freeTree(Node *node);

int main() {
    //inicializando a árvore
    Node *root = initialize();

    //inserindo os valores
    root = insert(root, 10); 
    root = insert(root, 15);
    root = insert(root, 20);
    root = insert(root, 12);
    root = insert(root, 5);
    
    printf("Antes da remoção \n");
    
    printf("Em ordem: ");
    displayInOrder(root);
    printf("\nPos ordem: ");
    displayPosOrder(root);
    printf("\nPre ordem: ");
    displayPreOrder(root);
    
    printf("\n");
    root = delete(root, 10);
    printf("Depois da remoção \n");
    printf("Em ordem: ");
    displayInOrder(root);
    printf("\nPos ordem: ");
    displayPosOrder(root);
    printf("\nPre ordem: ");
    displayPreOrder(root);
    
    printf("\n");
    //desalocando a árvore da memória (apagando)
    freeTree(root);
    
    return 0;
}

Node *initialize()
{
    return NULL;
}

Node *insert(Node *root, int value)
{
    if(root == NULL)
    {
        Node *aux = (Node*)malloc(sizeof(Node));
        aux->value = value;
        aux->left = NULL;
        aux->right = NULL;

        return aux;
    }
    else
    {
        if(value > root->value)
        {
            root->right = insert(root->right, value);
        }  
        else if(value < root->value)
        {
            root->left = insert(root->left, value);
        }
    }

    return root;
}

Node *search(Node *root, int value)
{
    if(root != NULL){
        if(value == root->value)
        {
            return root;
        }
        else
        {
            if(value > root->value)
            {   
                return search(root->right, value);
            }
            else if(value < root->value)
            {
                return search(root->left, value);
            }
        }
        
    }
    return NULL;
}

Node *smallerNode(Node *root)
{
    if(root != NULL)
    {
        Node *aux = root;
        while(aux->left != NULL)
        {
            aux = aux->left;
        }
        return aux;        
    }
    return NULL;
}

Node *biggerNode(Node *root)
{   
    if(root != NULL)
    {
        Node *aux = root;
        while(root->right != NULL)
        {
            aux = aux->right;
        }
        return aux;
    }
    return NULL;
}

Node *delete(Node *root, int value)
{   
    if(root != NULL)
    {
        if(value > root->value)
        {
            root->right = delete(root->right, value);
        }
        else if(value < root->value)
        {
            root->left = delete(root->left, value);
        }
        else
        {
            //caso n tenha nenhum filho a diretia e nem a esquerda
            if(root->right == NULL && root->left == NULL)
            {
                free(root);
                return NULL;
            }
            //caso tenha um filho a esquerda
            else if(root->right == NULL && root->left !=NULL)
            {
                //antes de eliminar o nó é necessário armazenar uma referência ao filho da esquerda para retornar ao nó supeior mais próximo.
                Node *aux = root->left;
                free(root);
                return aux;
            }
            //caso tenha um filho a direita
            else if(root->right != NULL && root->left == NULL)
            {
                //antes de eliminar o nó é necessário armazenar uma referência ao filho da direita para retornar ao nó supeior mais próximo.
                Node *aux = root->right;
                free(root);
                return aux;
            }
            //caso tenha filho tanto a direita quanto a esquerda
            else
            {
                Node *aux = smallerNode(root->right);//pegando o menor node do subárvore a direita
                int itemAux = aux->value; //armazenando o valor do menor node na variável itemAux
                root = delete(root, itemAux); //removendo o menor node
                root->value = itemAux;//colocando o valor do menor node  na raiz da árvore.
                return root;
            }
            
        }
        return root;
        
    }
    return NULL;
}

//número de nós da árvore
int numberOfNodes(Node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    else
    {
        return 1 + numberOfNodes(root->left) + numberOfNodes(root->right);
    }
    
}

//número de folhas da árvore
int numberOfSheets(Node *root)
{
    if(root == NULL)
    {
        return 0;
    }
    if(root->left == NULL && root->right == NULL)
    {
        return 1;
    }
    return numberOfSheets(root->left) + numberOfSheets(root->right);
}

int bigger(int a, int b)
{
    if(a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

//altura da árvore;
int heightTree(Node *root)
{
    if((root == NULL) || ((root->left) == NULL && (root->right) == NULL))
    {
        return 0;
    }
    else
    {
        return 1 + bigger(heightTree(root->left), heightTree(root->right));
    }
}

//funções de exibição
void displayInOrder(Node *root)
{
    if(root != NULL)
    {
        displayInOrder(root->left);
        printf("\n%i", root->value);
        displayInOrder(root->right);
    }
}

void displayPreOrder(Node *root)
{
    if(root != NULL)
    {
        printf("\n%i", root->value);
        displayPreOrder(root->left);
        displayPreOrder(root->right);
    }
}

void displayPosOrder(Node *root)
{
    if(root != NULL)
    {
        displayPosOrder(root->left);
        displayPosOrder(root->right);
        printf("\n%i", root->value);
    }
}

void freeTree(Node *node)
{
    if(node != NULL)
    {   
        freeTree(node->left);
        freeTree(node->right);
        free(node);
    }
}