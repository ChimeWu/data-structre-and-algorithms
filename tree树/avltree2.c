//用非递归算法实现一个平衡二叉树

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
    int data;
    int height;
    struct node *left;
    struct node *right;
} Node;

typedef struct tree
{
    Node *root;
    int size;
} Tree;

void init(Tree *tree)
{
    tree->root = NULL;
    tree->size = 0;
}

int max(int a, int b)
{
    return a > b ? a : b;
}

int height(Node *node)
{
    if (node == NULL)
    {
        return 0;
    }
    return node->height;
}

Node *leftRotate(Node *node)
{
    Node *temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

Node *rightRotate(Node *node)
{
    Node *temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = max(height(node->left), height(node->right)) + 1;
    temp->height = max(height(temp->left), height(temp->right)) + 1;
    return temp;
}

Node *insertNode(Node *node, int data)
{
    if (node == NULL)
    {
        Node *temp = (Node *)malloc(sizeof(Node));
        temp->data = data;
        temp->height = 1;
        temp->left = NULL;
        temp->right = NULL;
        return temp;
    }
    if (data < node->data)
    {
        node->left = insertNode(node->left, data);
    }
    else if (data > node->data)
    {
        node->right = insertNode(node->right, data);
    }
    else
    {
        return node;
    }
    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = height(node->left) - height(node->right);
    if (balance > 1 && data < node->left->data)
    {
        return rightRotate(node);
    }
    if (balance < -1 && data > node->right->data)
    {
        return leftRotate(node);
    }
    if (balance > 1 && data > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && data < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

void insert(Tree *tree, int data)
{
    tree->root = insertNode(tree->root, data);
    tree->size++;
}

void inOrder(Node *node)
{
    if (node == NULL)
    {
        return;
    }
    inOrder(node->left);
    printf("%d ", node->data);
    inOrder(node->right);
}

void print(Tree *tree)
{
    inOrder(tree->root);
    printf("\n");
}

